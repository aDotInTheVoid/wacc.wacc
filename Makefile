py_src = $(shell find py/ -name '*.py')
go_src = $(shell find test/ -type f -name '*.go')
wacc_src = $(shell find src/ gen/ -type f -name '*.wacc.in')
bs2_src = bs2/README bs2/codegen bs2/codegen/x64 bs2/codegen/x64/x64.cc bs2/codegen/x64/x64.hh bs2/codegen/xml bs2/codegen/xml/xml.cc bs2/codegen/xml/xml.hh bs2/codegen.cc bs2/codegen.hh bs2/lex.cc bs2/lex.hh bs2/lexbuf.cc bs2/lexbuf.hh bs2/main.cc bs2/meson.build bs2/op.cc bs2/op.hh bs2/parser.cc bs2/parser.hh bs2/subprojects bs2/subprojects/.gitignore bs2/subprojects/fmt.wrap bs2/type.cc bs2/type.hh bs2/util.cc bs2/util.hh

objdir = _build
timestamp = $(objdir)/.timestamp
tooldir = $(objdir)/tool
bs2 = bs2/_build/default/bs2

kgt = $(tooldir)/kgt
tp = $(tooldir)/tp
test = $(tooldir)/test

wacc_wacc = $(objdir)/wacc.wacc
wacc_tp_c = $(objdir)/wacc_tp.c
wacc_tp = $(objdir)/wacc-tp
wacc_bs2 = $(objdir)/wacc-bs2
wacc_bs2_s = $(objdir)/wacc-bs2.s 
wacc_bs2_o = $(objdir)/wacc-bs2.o
rt_obj = $(objdir)/rt.o

all: $(wacc_tp) $(wacc_bs2)

gen/%.wacc.in: $(py_src)
	python3.10 py/gen.py

# No default nonsense
.SUFFIXES:

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

$(wacc_wacc): $(wacc_src)
	cpp -undef -nostdinc src/wacc.wacc.in -o $@
$(wacc_tp_c): $(wacc_wacc) $(tp)  
	$(tp) $< $@
$(wacc_tp): $(wacc_tp_c)
	clang $< -o $@ -Wno-parentheses-equality -fsanitize=address
$(wacc_bs2_s): $(wacc_wacc) $(bs2)
	$(bs2) asm $< > $@
$(wacc_bs2_o): $(wacc_bs2_s)
	gcc -c $< -o $@
$(rt_obj): rt.c
	gcc -Wall -c $< -o $@
$(wacc_bs2): $(wacc_bs2_o) $(rt_obj)
	gcc $^ -o $@

tools: $(kgt) $(tp) $(test)

$(bs2): $(bs2_src)
	ninja -C bs2/_build/default
bs2: $(bs2)

_build/bs2/%: %.wacc $(bs2) $(rt_obj)
	@mkdir -p $(@D)
	$(bs2) asm $< > $@.s
	gcc $@.s $(rt_obj) -o $@

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
	rm -rf $(wacc_wacc) $(wacc_tp_c) $(wacc_tp) $(wacc_bs2) $(wacc_bs2_s) $(wacc_bs2_o) $(rt_obj) $(test)

.PHONY: clean-all
clean-all:
	rm -rf $(objdir)

.PHONY: test
test: $(test)
	$(test)

.PHONY: bless
bless:
	$(MAKE) test WACC_UPDATE=1