py_src := $(shell find py/ -name '*.py')
go_src := $(shell find test/ -type f -name '*.go')
wacc_src := $(shell find src/ gen/ -type f -name '*.wacc.in')
bs2_src := bs2/README bs2/codegen bs2/codegen/x64 bs2/codegen/x64/x64.cc bs2/codegen/x64/x64.hh bs2/codegen/xml bs2/codegen/xml/xml.cc bs2/codegen/xml/xml.hh bs2/codegen.cc bs2/codegen.hh bs2/lex.cc bs2/lex.hh bs2/lexbuf.cc bs2/lexbuf.hh bs2/main.cc bs2/meson.build bs2/op.cc bs2/op.hh bs2/parser.cc bs2/parser.hh bs2/subprojects bs2/subprojects/.gitignore bs2/subprojects/fmt.wrap bs2/type.cc bs2/type.hh bs2/util.cc bs2/util.hh

objdir := _build
timestamp := $(objdir)/.timestamp
tooldir := $(objdir)/tool
bs2 := bs2/_build/default/bs2

kgt := $(tooldir)/kgt
tp := $(tooldir)/tp
test := $(tooldir)/test

gen/%.wacc.in: $(py_src)
	python3.10 py/gen.py

all: $(objdir)/wacc


$(timestamp):
	@mkdir -p $(objdir)
	@mkdir -p $(tooldir)
	@mkdir -p $(objdir)/asm-pass
	touch $(timestamp)

$(kgt): $(timestamp) ./regen-kgt.sh
	./regen-kgt.sh
$(tp): $(timestamp) ./regen-tp.sh
	./regen-tp.sh
$(test): $(timestamp) $(go_src)
	cd test && go build
	mv test/test $(test)

$(objdir)/wacc.wacc: $(wacc_src)
	cpp -undef -nostdinc src/wacc.wacc.in -o $@
$(objdir)/wacc-tp.c: $(tp) $(objdir)/wacc.wacc
#	CGEN_LINE_CONTROL=1
	$(tp) $(objdir)/wacc.wacc $@
$(objdir)/wacc: $(objdir)/wacc-tp.c #TODO: Rename
	clang -g -o $@ $< -Wno-parentheses-equality -fsanitize=address
$(objdir)/wacc-bs2.s: $(objdir)/wacc.wacc $(bs2)
	$(bs2) asm $< > $@
$(objdir)/wacc-bs2.o: $(objdir)/wacc-bs2.s
	gcc -g -c -o $@ $<
$(objdir)/wacc-bs2: $(objdir)/wacc-bs2.o $(objdir)/rt.o
	gcc -g -o $@ $^

$(objdir)/rt.o: rt.c
	gcc -g  -Wall  -c -o $@ $<
test/asm-pass/%.s: test/asm-pass/%.wacc $(bs2)
	$(bs2) asm $< > $@
$(objdir)/asm-pass/%.o: test/asm-pass/%.s
	gcc -g -c  -o $@ $<
$(objdir)/asm-pass/%: $(objdir)/asm-pass/%.o $(objdir)/rt.o
	gcc -g -o $@ $^

tools: $(kgt) $(tp) $(test)

$(bs2): $(bs2_src)
	ninja -C bs2/_build/default
bs2: $(bs2)

.PHONY: debug
debug:
	@echo "Py source"
	@echo $(py_src)
	@echo "Go source"
	@echo $(go_src)
	@echo "Wacc source"
	@echo $(wacc_src)
	@echo "kgt = " $(kgt) " tp = " $(tp) " test = " $(test)

.PHONY: clean
clean:
	rm -rf $(objdir)/wacc $(objdir)/wacc.c $(objdir)/wacc.wacc

.PHONY: clean-all
clean-all:
	rm -rf $(objdir)

.PHONY: test
test: $(test)
	$(test)

.PHONY: bless
bless:
	$(MAKE) test WACC_UPDATE=1