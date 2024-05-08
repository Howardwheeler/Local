;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 4, ex 1
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

LEA R2, ARRAY

LD R1, SUB_FILL_ARRAY_3200
JSRR R1

LDR R0 R2 #0
OUT


HALT

ARRAY .blkw #10
SUB_FILL_ARRAY_3200  .fill x3200

.end

;------------------------------------------------------------------------
; Subroutine: SUB_FILL_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: The array has values from 0 through 9.
; Return Value (None)
;-------------------------------------------------------------------------
.orig x3200

AND R3, R3, #0
LD R4, ARRAY_SIZE

LOOP_START
STR R3, R2, #0 ;R3 <- 0, storing value 0 into array R2
ADD R2, R2, #1 ;R2 the array , sets new R2 offset by 1

ADD R3, R3, #1 ;add hard code 0 +1

ADD R4, R4, #1 ;iterates loop
BRn LOOP_START

RET

DEC_VALUE .fill #0
ARRAY_SIZE .fill #-10

.end