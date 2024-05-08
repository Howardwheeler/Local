;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Assignment name: Assignment 3
; Lab section: 1
; TA: Karan and Cody
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
ADD R2, R2, #15 ;--------SETS ITERATOR TO 15(RUNS 16 TIMES)-----------
LD R3, HEX_FFFF ;----------SETS 1111 1111 1111 1111 TO USE FOR AND OPERAND---
ADD R4, R4, #4 ;----------SET BINARY SPACE CHECKER TO 4------------------

BR LOOP_START ;-----------PASSES SPACE LOOP INITIALLY-------
SPACE_START ;----------SPACE PRINT LOOP START-----
ADD R2, R2, #-4 ;-------PRINTED OUT 4 BIT BINARY----------
BRn FINISH_LOOP ;---------ITERATED SPACE 3 TIMES, NO MORE SPACE NEEDED! DONE CODE------

ADD R4, R4, #4 ;-------RESETS R4, PRINTS SPACE, GOES BACK TO LOOP--------
LD R0, SPACE
OUT
BR SPACE_FINISH ;-------FINISHES PRINTINT SPACE---------

LOOP_START ;--------BINARY PRINT LOOP START ------

AND R1, R1, R3 ;---------AND OPERAND TO CHECK MSB--------
BRn PRINT_ONE ;---------IF AND OPERAND RETURN POSITIVE (0000), PRINT 1-------
BR PRINT_ZERO ;---------IF AND OPERAND RETURN NEGATIVE(1000), PRINT 0------
LOOP_BACK ;-------PRINTS DIGIT AND COMES BACK TO WHERE IT LEFT OFF---------

ADD R4, R4, #-1 ;-------ITERATE THROUGH BINARY SPACE CHECKER----------
BRz SPACE_START ;-------IF BINARY SPACE CHECKER IS 0, ADD SPACE
SPACE_FINISH ;-----------AFTER ADDING SPACE, COME BACK TO WHERE IT LEFT OFF------

ADD R1, R1, R1 ;-------SHIFTING TO LEFT THE GIVEN VALUE-----------

BR LOOP_START ;--------ITERATES THROUGH BINARY LOOP


PRINT_ONE ;---------PRINTS 1 TO CONSOLE----------
LD R0, DEC_1
OUT
BR LOOP_BACK

PRINT_ZERO ;----------PRINTS 0 TO CONSOLE-----------
LD R0, DEC_0
OUT
BR LOOP_BACK

FINISH_LOOP ;-------------FINISH! NEW LINE PRINT--------
LD R0, newline
OUT

HALT
;---------------	
;Data
;---------------
Value_ptr	.FILL xCA01	; The address where value to be displayed is stored
DEC_1 .fill #49
DEC_0 .fill #48
HEX_FFFF .fill xFFFF
SPACE .fill #32
newline .fill x0A

.END

.ORIG xCA01					; Remote data
Value .FILL xABCD			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------	
;END of PROGRAM
;---------------	
.END