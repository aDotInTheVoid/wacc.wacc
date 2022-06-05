py_src = $(shell find py/ -name '*.py')
go_src = $(shell find test/ -type f -name '*.go')
wacc_src = $(shell find src/ gen/ -type f -name '*.wacc.in')
bs2_src = bs2/README bs2/codegen bs2/codegen/x64 bs2/codegen/x64/x64.cc bs2/codegen/x64/x64.hh bs2/codegen/xml bs2/codegen/xml/xml.cc bs2/codegen/xml/xml.hh bs2/codegen.cc bs2/codegen.hh bs2/lex.cc bs2/lex.hh bs2/lexbuf.cc bs2/lexbuf.hh bs2/main.cc bs2/meson.build bs2/op.cc bs2/op.hh bs2/parser.cc bs2/parser.hh bs2/subprojects bs2/subprojects/.gitignore bs2/subprojects/fmt.wrap bs2/type.cc bs2/type.hh bs2/util.cc bs2/util.hh

objdir = _build
timestamp = $(objdir)/.timestamp
tooldir = $(objdir)/tool
bs2 = bs2/_build/test/bs2

kgt = $(tooldir)/kgt
tp = $(tooldir)/tp
test = $(tooldir)/test

wacc_lex_src = src/wacc-lex.wacc.in
wacc_asm_src = src/wacc-asm.wacc.in

wacc_lex_wacc = $(objdir)/wacc-lex.wacc
wacc_lex_tp_c = $(objdir)/wacc_lex_tp.c
wacc_lex_tp = $(objdir)/wacc-lex-tp
wacc_lex_bs2 = $(objdir)/wacc-lex-bs2
wacc_lex_bs2_s = $(objdir)/wacc-lex-bs2.s 
wacc_lex_bs2_o = $(objdir)/wacc-lex-bs2.o
wacc_asm_wacc = $(objdir)/wacc-asm.wacc
wacc_asm_tp_c = $(objdir)/wacc_asm_tp.c
wacc_asm_tp = $(objdir)/wacc-asm-tp
wacc_asm_bs2 = $(objdir)/wacc-asm-bs2
wacc_asm_bs2_s = $(objdir)/wacc-asm-bs2.s 
wacc_asm_bs2_o = $(objdir)/wacc-asm-bs2.o
rt_obj = $(objdir)/rt.o

all: wacc_lex_tp wacc_asm_tp wacc_lex_bs2 wacc_asm_bs2
wacc_lex_tp: $(wacc_lex_tp)
wacc_asm_tp: $(wacc_asm_tp)
wacc_lex_bs2: $(wacc_lex_bs2)
wacc_asm_bs2: $(wacc_asm_bs2)


gen/%.wacc.in: $(py_src)
	python3.10 py/gen.py

# No default nonsense
.SUFFIXES:

$(timestamp):
	@mkdir -p $(objdir)
	@mkdir -p $(tooldir)
	touch $(timestamp)

$(kgt): $(timestamp) ./regen-kgt.sh
	./regen-kgt.sh
$(tp): $(timestamp) ./regen-tp.sh
	./regen-tp.sh
$(test): $(timestamp) $(go_src)
	cd test && go build
	mv test/test $(test)

$(rt_obj): rt.c
	gcc -Wall -c $< -o $@

# Preprocess
$(wacc_lex_wacc): $(wacc_lex_src)
	cpp -undef -nostdinc $< -o $@
$(wacc_asm_wacc): $(wacc_asm_src)
	cpp -undef -nostdinc $< -o $@
# Transpile to c
$(wacc_lex_tp_c): $(wacc_lex_wacc) $(tp)  
	$(tp) $< $@
$(wacc_asm_tp_c): $(wacc_asm_wacc) $(tp)  
	$(tp) $< $@
# Compile C
$(wacc_lex_tp): $(wacc_lex_tp_c)
	clang $< -o $@ -Wno-parentheses-equality -fsanitize=address
$(wacc_asm_tp): $(wacc_asm_tp_c)
	clang $< -o $@ -Wno-parentheses-equality -fsanitize=address
# Assemble with bs2
$(wacc_lex_bs2_s): $(wacc_lex_wacc) $(bs2)
	$(bs2) asm $< > $@
$(wacc_asm_bs2_s): $(wacc_asm_wacc) $(bs2)
	$(bs2) asm $< > $@
# Build bs2 object files
$(wacc_lex_bs2_o): $(wacc_lex_bs2_s)
	gcc -g -c $< -o $@
$(wacc_asm_bs2_o): $(wacc_asm_bs2_s)
	gcc -g -c $< -o $@
$(wacc_lex_bs2): $(wacc_lex_bs2_o) $(rt_obj)
	gcc -g -o $@ $^
$(wacc_asm_bs2): $(wacc_asm_bs2_o) $(rt_obj)
	gcc -g -o $@ $^


tools: $(kgt) $(tp) $(test)

$(bs2): $(bs2_src)
	ninja -C $(@D)
bs2: $(bs2)

_build/bs2/%: %.wacc $(bs2) $(rt_obj)
	@mkdir -p $(@D)
	$(bs2) asm $< > $@.s
	gcc -g $@.s $(rt_obj) -o $@
_build/tp/%: %.wacc $(tp)
	@mkdir -p $(@D)
	$(tp) $< $@.c
	gcc $@.c -o $@

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
	rm -rf $(rt_obj) $(test) $(objdir)/wacc* $(objdir)/bs2 $(objdir)/tp

.PHONY: clean-all
clean-all:
	rm -rf $(objdir)
	rm -rf bs2/subprojects/fmt-8.1.1/
	rm -rf bs2/subprojects/packagecache/
	rm -rf bs2/_build

.PHONY: test
test: $(test)
	$(test)
.PHONY: testv
testv: $(test)
	$(test) -v

.PHONY: bless
bless:
	$(MAKE) test WACC_UPDATE=1