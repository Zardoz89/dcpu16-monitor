; Io functions wrapping BBOS calls

;    Prints a 7 bit ascii char and update cursor. Wraps screen
;    Params :
;        B -> 7 bit ASCII char
putc:
        and b, 0x007F    ; Clearing attribute color (use default color on BBOS)
        set push, b
        set push, 1      ; Autoincrement cursor
        BBOS_PRINTCHAR
        BBOS_GETCURSOR
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

; vim: set ts=4 sw=4 tw=0 et :
