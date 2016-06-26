# Machine code monitor for DCPU-16 v0.1

The machine code monitor is a clone of the Wozniaks's Machine code monitor that
ran on the Apple I and Apple ][.

It allow to an user, to display the value of any RAM address and alter the
values stored on RAM. Also, can *run* any program that is stored on RAM if the
user knows the address where is placed.

The actual version is a working prototype that only implements the most basic
and essential functionality of a machine code monitor (ie. display & editing
values on RAM and *running* code stored on it.), and fits on a single floppy
disk sector.

## Compiling it

The monitor uses Techcompliant's DASM assembler, GNU Make (should work with any
make flavor), and objcopy (binutils package) to build a BBOS bootable floppy
disk image that works on ISICpu emulator.

Simply run ```make``` to generate a valid floppy image file "monitor.idi" and
copy it where you have ISICpu. If you would use another emulator that have a
reverse byte order endianes respect to ISICpu (big-endian), you can simply
execute ```make monitor.bin``` to get a little-endian file.

## Requisites

A compatible DCPU-16 computer with:

- BBOS v1.0 compatible ROM
- Any text/graphics card that would work with BBOS text output routines. Note
  that the monitor assumes that the screen have a size of 32x16 text cells
  (LEM1801/2 size).
- A keyboard compatible with BBOS input rutines

# Usage

Put the monitor floppy on the floppy drive, and reset/power on the DCPU-16
computer. BBOS will show his startup text and read the floppy. An ```*``` would
apper on screen, indicating that the monitor is awating any input. Note that the
actual version of the monitor not show any visible cursor.

The monitor only accepts hexadecimal digits, ```g```, ```.```, ```:```, backspace and return keys.
Backspace, would obviusly delete the last character typed by the user, and
return key would execute the typed input.

**Hexadecimal inputs are truncated to the least significant 4 hexadecimal digits**.
In other words, if you type ```12345678``` the monitor would interpret it as
the value 5678.

### Examining memory (memory dump)

You can examine the contents of a single memory location by typing a single
address followed by return.

```
*1ff
01FF: 55AA
```
NOTE: The first line represent the user input displayed on the screen. You
  musn't type '*' character.

The monitor remember the last opened address typed by the user, so if we press now
return key, would displsy again the value of the address 0x01ff.

Now, let us examine a block of memory from the last opened address to the next
specified location.

```
*.204
01FF: 55AA 01FF 0001 0011
0203: 002E 0032
```
NOTE: The last opened address would keep being 0x01ff.

We can take a look to another address block.

```
*500.503
0500: 0000 0000 0000 0000
```

And now, the last opened address is 0x0500.

We can examine several locations at once, with all address on one command line.

```
*1ff.202 203.204 300 500
01FF: 55AA 01FF 0001 0011
0203: 002E 0032
0300: 0701
0500: 0000
```
NOTE: Now, you should know that 0x0500 is the last opened address.

Be careful if you print a large block of addresses, as the program can't be
stoped (except if you reset the computer), and there isn't a way of scroll the
screen or pause it.

### Write values to the RAM

To change the value of a RAM address, we need to use ```:```

```
*500:cafe
*500
0500: CAFE
```

Note that using ```:``` wouldn't give any feedback to the user (on the actual
version).

We can write more values to the RAM.
```
*:dead beef 0001 0002
*.503
0500: DEAD BEEF 0001 0002
```

As you see, any value typed after the ```:``` would be interpreted as a value to
be put on the RAM.

### Running a program

To run a program at a specified address, simply use the ```g``` command:

```
*0g
*(Return key)
01ff: 55AA
```

Let's explain what happened here. The monitor code it's placed on the block
0x0000 to 0x01FF, so doing ```0g``` would *reset* it. And when the monitor it's
loaded sets as the initial opened address the address 0x01FF, where the value
0x55AA (the bootable floppy mark) it's placed. So, pressing the return key again
, displays the value 0x55AA. Note that this could change on future versions of
the monitor

If we dump a program on RAM, we can call it typing the initial address of it
followed by ```g``` command.

