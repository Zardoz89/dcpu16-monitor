#
DASM := ./dasm

all: test.bin

test.bin: test.dasm
	$(DASM)  $^ $@


