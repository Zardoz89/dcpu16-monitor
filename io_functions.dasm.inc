; Io functions wrapping BBOS calls

;    Prints a 7 bit ascii char and update cursor. Wraps screen
;    Params :
;        A -> 7 bit ASCII char (polutes it, doing an AND 0x007F)
putc:
        and a, 0x007F    ; Clearing attribute color (use default color on BBOS)
        set push, a
        set push, 1      ; Autoincrement cursor
        BBOS_PRINTCHAR
        BBOS_GETCURSOR      ; [sp] = row , [sp+1] = col
        ife 12, pop
            set pc, reset_cursor_
        add sp, 1

        set pc, pop

reset_cursor_:
        set [sp], 0
        set push, 0
        BBOS_SETCURSOR
        add sp, 2

        set pc, pop


;   Reads a char from the keyboard. Blocks waiting
;   Return: On A -> Receibed character
getchar:
        set push, 1
        BBOS_GETCHAR
        set a, pop
        set pc, pop


;   Sets cursor to the next line
line_feed:
        set push, 0
        set push, 0
        BBOS_GETCURSOR
        add [sp], 1         ; Row++
        set [sp+1], 0       ; Col 0
        ife 12, [sp]
            set [sp], 0     ; Wraping
        BBOS_SETCURSOR
        add sp, 2           ; Clears stack

        set pc, pop


;   Prints prompt
print_prompt:
        set push, '*'
        set push, 1
        BBOS_PRINTCHAR
        add sp, 2           ; Clears stack

;   Clears a whole line conting of actual cursor position
clr_line:
        set push, x
        set push, y
        set push, z

        set push, 0
        set push, 0
        BBOS_GETCURSOR

        set x, [sp]         ; Row
        set y, [sp+1]       ; Col

        set z, y            ; Counter
        set [sp+1], 0x20
        set [sp], 1
clr_line_loop_:
        ife 32, z
            set pc, clr_line_end_ ; exit loop at end of line
        BBOS_PRINTCHAR
        add z, 1
        set pc, clr_line_loop_
clr_line_end_:
        set [sp], x
        set [sp+1], y
        BBOS_SETCURSOR      ; Resetting cursor
        add sp, 2

        set z, pop
        set y, pop
        set x, pop
        set pc, pop

; Do backspace with the cursor. Emplacin a space and getting back one cell the cursor
backspace:
        sub sp, 2
        BBOS_GETCURSOR
        ife [sp+1], 0       ; At column  0 ?
            set pc, backspace_wrap_ ; Wrap to the previus row
        sub [sp+1], 1
backspace_setcursor_:
        BBOS_SETCURSOR

        set [sp+1], 0x20
        set [sp], 0
        BBOS_PRINTCHAR      ; Print space character and not increment cursor

        add sp, 2
        set pc, pop

backspace_wrap_:    ; [sp+1] -> col [sp] -> row
        set [sp+1], 31
        sub [sp], 1
        ifg [sp], 11 ; Underflow! -> set at last line
            set [sp], 11

        set pc, backspace_setcursor_

; vim: set ts=4 sw=4 tw=0 et :
