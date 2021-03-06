
RM  := rm
DASM := ./dasm

DISK_IMAGE_FILES := monitor.idi test1.idi test2.idi test3.idi

all: ${DISK_IMAGE_FILES}

%.bin: %.dasm macros.dasm.inc io_functions.dasm.inc
	$(DASM) $< $@

# Switch endianess to the correct
%.idi: %.bin
	objcopy -I binary -O binary --reverse-bytes=2 $^ $@

.PHONY: clean

clean:
	${RM} -f *.idi
	${RM} -f *.bin

# Do a Hexadecimla dump of output file
%_hex: %.idi
	hexdump  $^ -e '" 0x%04_ax\t" 16/1 "0x%02X " "\n"'
