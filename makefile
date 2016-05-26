
DASM := ./dasm
MKFLOPPY := ./build_bootable_floppy

all: test.idi

test.idi: test.dasm
	$(DASM)  $^ $@

.PHONY:  clean hex

clean:
	rm test.idi

hex: test.idi
	hexdump  test.idi -e '" 0x%04_ax\t" 16/1 "0x%02X " "\n"'
