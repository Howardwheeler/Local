;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 3, ex 2
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

LEA R1, array

LD R2, loop_checker

loop_start
GETC
OUT

STR R0, R1, #0
ADD R1, R1, #1

ADD R2, R2 #1
BRnp loop_start



HALT
array .blkw #10
loop_checker .fill #-10

.end