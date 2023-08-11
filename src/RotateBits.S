;;.extern timer0_overflow
.section .data
my:  .word	0x0123456789ABCDEF
.section .text
.global rotate_bits
rotate_bits:
    ;st Z,R24
    ror ZL
ret                     ; Return
.end
;;.org $016
       ;; rjmp timer0_overflow