;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 4, ex 3
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

LEA R2, ARRAY

LD R1, SUB_FILL_ARRAY_3200
JSRR R1

LEA R2, ARRAY

LD R1, SUB_CONVERT_ARRAY_3400
JSRR R1

LEA R2, ARRAY

LD R1, SUB_PRINT_ARRAY_3600
JSRR R1

HALT

ARRAY .blkw #10
SUB_FILL_ARRAY_3200  .fill x3200
SUB_CONVERT_ARRAY_3400 .fill x3400
SUB_PRINT_ARRAY_3600 .fill x3600

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

;------------------------------------------------------------------------
; Subroutine: SUB_CONVERT_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (number) in the array should be represented as a character. E.g. 0 -> ‘0’
; Return Value (None)
;-------------------------------------------------------------------------
.orig x3400

LD R4, ARRAY_SIZE_CONV
LD R3, DEC_48

CONV_LOOP_START
LDR R5, R2, #0
ADD R5, R5, R3

STR R5, R2, #0
ADD R2, R2, #1

ADD R4, R4, #1
BRn CONV_LOOP_START

RET

ARRAY_SIZE_CONV .fill #-10
DEC_48 .fill #48

.end

;------------------------------------------------------------------------
; Subroutine: SUB_PRINT_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (character) in the array is printed out to the console.
; Return Value (None)
;-------------------------------------------------------------------------
.orig x3600

LD R4, ARRAY_SIZE_PRINT

PRINT_LOOP_START
LDR R0, R2, #0
OUT

ADD R2, R2, #1

ADD R4, R4, #1
BRn PRINT_LOOP_START

RET

ARRAY_SIZE_PRINT .fill #-10

.end