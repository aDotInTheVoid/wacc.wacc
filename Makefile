py_src := $(shell find py/ -name '*.py')
go_src := $(shell find test/ -type f -name '*.go')
wacc_src := $(shell find src/ gen/ -type f -name '*.wacc.in')

objdir := _build
timestamp := $(objdir)/.timestamp
tooldir := $(objdir)/tool

kgt := $(tooldir)/kgt
tp := $(tooldir)/tp
test := $(tooldir)/test

gen/%.wacc.in: $(py_src)
	python3.10 py/gen.py

all: $(objdir)/wacc


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

$(objdir)/wacc.wacc: $(wacc_src)
	cpp -undef -nostdinc src/wacc.wacc.in -o $@
$(objdir)/wacc.c: $(tp) $(objdir)/wacc.wacc
#	CGEN_LINE_CONTROL=1
	$(tp) $(objdir)/wacc.wacc $@
$(objdir)/wacc: $(objdir)/wacc.c
	clang -g -o $@ $< -fsanitize=address -Wno-parentheses-equality
tools: $(kgt) $(tp) $(test)

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