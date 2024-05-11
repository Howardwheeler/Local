;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 6, ex 3
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
LD R6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE

; your code goes here
LEA R4, WORD_ARRAY ;loads array
AND R3, R3, #0 ;sets size to 0

LD R5, SUB_GET_STRING ;loads subroutine x3200
JSRR R5 ;jumps to it

LEA R4, WORD_ARRAY
LD R5, SUB_IS_PALINDROME
JSRR R5

LEA R4, WORD_ARRAY
LEA R0, initial_prompt
PUTS

ITS_PRINT_LOOP_START
    LDR R0, R4, #0
    OUT
    ADD R4, R4, #1
    ADD R3, R3, #-1
BRp ITS_PRINT_LOOP_START

LD R2, PALINDROME_FLAG
LDR R7, R2, #0
BRp PRINT_ITS_PALINDROME
BR PRINT_NOT_PALINDROME

PRINT_ITS_PALINDROME
LEA R0, ITS_A_PALINDROME_PROMPT
PUTS
BR FINISH

PRINT_NOT_PALINDROME
LEA R0, NOT_A_PALINDROME_PROMPT
PUTS
BR FINISH

FINISH
halt

; your local data goes here
WORD_ARRAY                  .BLKW #100
initial_prompt              .STRINGZ	"The string \""
ITS_A_PALINDROME_PROMPT     .STRINGZ	"\" IS a palindrome"
NOT_A_PALINDROME_PROMPT     .STRINGZ	"\" IS NOT a palindrome"
PALINDROME_FLAG             .FILL xB000
SUB_GET_STRING              .FILL x3200
SUB_IS_PALINDROME           .FILL x3400
top_stack_addr              .FILL xFE00 ; DO NOT MODIFY THIS LINE OF CODE
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

    AND R2, R2, #0 ;resets R2 to 0
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

;-------------------------------------------------------------------------
; Subroutine: SUB_IS_PALINDROME
; Parameter (R1): The starting address of a null-terminated string
; Parameter (R5): The number of characters in the array.
; Postcondition: The subroutine has determined whether the string at (R1)
;		 is a palindrome or not, and returned a flag to that effect.
; Return Value: R4 {1 if the string is a palindrome, 0 otherwise}
;-------------------------------------------------------------------------
.ORIG x3400
ADD R6, R6, #-1
STR R7, R6, #0 ;stores return location to R6
ADD R6, R6, #-1
STR R5, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0

LD R5, SUB_TO_UPPER ;change to caps subroutine
AND R7, R7, #0
LDR R1, R4, #0 ;loads first index
ADD R7, R4, R3 ;offsets array by size
LDR R0, R7, #-1 ;loads last index

ADD R3, R3, #-2
BR START_PALINDROME_LOOP

PALINDROME_LOOP
    ADD R4, R4, #1
    LDR R1, R4, #0
    ADD R7, R4, R3
    LDR R0, R7, #-1
    

    ADD R3, R3, #-2 ;subtracts 2 by size
    BRnz ITS_PALINDROME

START_PALINDROME_LOOP
    JSRR R5 ;goes to subroutine to check
    
    NOT R0, R0
    ADD R0, R0, #1
    ADD R2, R0, R1
BRz PALINDROME_LOOP
BR NOT_PALINDROME

ITS_PALINDROME
    AND R7, R7, #0
    ADD R7, R7, #1
    LD R3, PALINDROME_FLAG_3400
    STR R7, R3, #0 ;flags 1 if its a palindrome
BR RETURN

NOT_PALINDROME
    AND R7, R7, #0
    LD R3, PALINDROME_FLAG_3400
    STR R7, R3, #0 ;flags 0 if its not a palindrome
BR RETURN

RETURN
LDR R3, R6, #0
ADD R6, R6, #1
LDR R5, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1 ;loads return location from R6
RET
SUB_TO_UPPER                .FILL x3600
PALINDROME_FLAG_3400        .FILL xB000
.END

;-------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R1): Starting address of a null-terminated string
; Postcondition: The subroutine has converted the string to upper-case
;     in-place i.e. the upper-case string has replaced the original string
; No return value, no output, but R1 still contains the array address, unchanged
;-------------------------------------------------------------------------
.ORIG x3600
ADD R6, R6, #-1
STR R7, R6, #0 ;stores return location to R6

LD R7, CAPS_CHECKER

AND R0, R0, R7
AND R1, R1, R7

LDR R7, R6, #0
ADD R6, R6, #1 ;loads return location from R6
RET
CAPS_CHECKER        .FILL xDF
.END

;-------------------------------------------------------------------------
.ORIG xB000
.BLKW	#1
.END
;-------------------------------------------------------------------------