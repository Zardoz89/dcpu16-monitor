; Macros to do inline calls to BBOS

.macro BBOS_CALL = set a, %0 %n int 0x4743

.macro BBOS_SETCURSOR =  BBOS_CALL 0x1001

.macro BBOS_GETCURSOR =  BBOS_CALL 0x1002

.macro BBOS_PRINTCHAR =  BBOS_CALL 0x1003

.macro BBOS_GETCHAR   =  BBOS_CALL 0x3001

; vim: set ts=4 sw=4 tw=0 et :
