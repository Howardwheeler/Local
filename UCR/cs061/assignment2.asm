;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Assignment name: Assignment 2
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

;----------------------------------------------
;output prompt
;----------------------------------------------	
LEA R0, intro			; get starting address of prompt string
PUTS			    	; Invokes BIOS routine to output string

;-------------------------------
;INSERT YOUR CODE here
;--------------------------------

;take input
GETC               ;get input from user in console, then "OUT"puts it back onto console
OUT

ADD R1, R0, #0     ;puts R0 into R1 which is the human input form console

LD R0, newline     ;takes in memory address from "newline" to make a new line
OUT

GETC
OUT 

ADD R2, R0, #0

LD R0, newline       ;repeat above
OUT

;output equation

ADD R0, R1, #0       ;Since OUT only takes R0, you copy R1's register to R0
OUT

LEA R0, minus       ;takes "minus" memory address with the string "-"
PUTS

ADD R0, R2, #0      ;does line 50 does but with R2
OUT

LEA R0, equals      ;takes "equal" memory address with the string "="
PUTS

;converting
LD R3 DEC_48        ;sets new decimal value 48 (which is 0 in ASCII) into R3

ADD R1, R1, R3      ;converts R1 and R2's values to decimal values?
ADD R2, R2, R3

;equation

NOT R2, R2          ;flips R2's values so that the ADD function works as a minus
ADD R2, R2, #1

ADD R4, R1, R2      ;"adds" R1 and R2 together
BRn IF_NEGATIVE     ;checks if the answer in R4 is negative
BRzp IF_POSITIVE    ;checks if the answer in R4 is positive or zero

IF_NEGATIVE         ;if its negative, it flips the number from negative to positive
NOT R4, R4
ADD R4, R4, #1

LEA R0, negative       ;outputs "-" and the final answer
PUTS

ADD R0, R4, R3
OUT

LD R0, newline     ;takes in memory address from "newline" to make a new line
OUT

HALT


IF_POSITIVE         ;outputs the final answer
ADD R0, R4, R3
OUT

LD R0, newline     ;takes in memory address from "newline" to make a new line
OUT

HALT





HALT				; Stop execution of program
;------	
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL x0A	; newline character - use with LD followed by OUT
minus .STRINGZ  " - "
equals .STRINGZ " = "
DEC_48 .FILL #48    ;decimal value 48
negative .STRINGZ "-"  ;for negative answer

;---------------	
;END of PROGRAM
;---------------	
.END

