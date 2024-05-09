;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 6, ex 1
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
LD R6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE

; your code goes here
LD R4, WORD_ARRAY ;loads array
AND R3, R3, #0 ;sets size to 0

LD R5, SUB_GET_STRING ;loads subroutine x3200
JSRR R5 ;jumps to it



halt

; your local data goes here
WORD_ARRAY     .BLKW #100
SUB_GET_STRING .FILL x3200
top_stack_addr .FILL xFE00 ; DO NOT MODIFY THIS LINE OF CODE
.end

; your subroutines go below here
;------------------------------------------------------------------------
; Subroutine: SUB_GET_STRING
; Parameter (R1): The starting address of the character array
; Postcondition: The subroutine has prompted the user to input a string,
;	terminated by the [ENTER] key (the "sentinel"), and has stored 
;	the received characters in an array of characters starting at (R1).
;	the array is NULL-terminated; the sentinel character is NOT stored.
; Return Value (R5): The number of non-sentinel chars read from the user.
;	R1 contains the starting address of the array unchanged.
;-------------------------------------------------------------------------
.ORIG x3200
ADD R6, R6, #-1
STR R7, R6, #0 ;stores return location to R6
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0

LD R1, DEC_ENTER ;sets to enter

GETC
OUT


INPUT_LOOP
    STR R0, R4, #0
    ADD R4, R4, #1
    ADD R3, R3, #1

    GETC
    OUT

    AND R2, R2, #0 ;resets R3 to 0
    ADD R2, R0, R1 ;if input is enter, stops loop
BRnp INPUT_LOOP

LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1 ;loads return location from R6
RET
DEC_ENTER       .FILL #-10
.END