;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 3, ex 4
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

LD R3, array_ptr
LD R1, stopper
AND R2, R2, #0

loop_start
GETC
OUT

STR R0, R3, #1
ADD R3, R3, #1

ADD R2, R2, #1

ADD R0, R0, R1
BRz FINISH_LOOP
BR loop_start
FINISH_LOOP

LD R3, array_ptr

LD R0, newline
OUT

print_loop_start
LDR R0, R3, #1
OUT

ADD R3, R3, #1

ADD R2, R2, #-1
BRp print_loop_start


HALT
array_ptr .fill x4000
newline .fill x0A
stopper .fill #-99

.end

.orig x4000

array .blkw #100

.end