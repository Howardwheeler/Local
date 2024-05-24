; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 21
; TA: Karan and Sahar
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================

;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
ld r6, stack_addr

; call main subroutine
lea r5, main
jsrr r5

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------
main
; get a string from the user
LEA R0, user_prompt                     ;sends initial prompt
PUTS

LEA R4, user_string                     ;initializes an array at address user_string
LD R5, get_user_string_addr             ;calls the subroutine for getting the string
JSRR R5
; find size of input string
LEA R4, user_string                     ;loads back the first index of array
LD R5, strlen_addr                      ;calls the subroutine for getting the string length
JSRR R5
; call palindrome method
ADD R1, R1, #-1
ADD R3, R4, R1                          ;initializes R3 as the last index of the string (size-1)

LD R5, palindrome_addr                  ;calls the subroutine for checking palindrome
JSRR R5
; print the result to the screen
LEA R0, result_string                   ;prints out beginning of final output
PUTS
; determine of stirng is a palindrome
ADD R1, R1, #0                          ;checks for flag to determine if its palindrome or not, then branch
BRp IS_PALINDROME
BR NOT_PALINDROME
; decide whether or not to print "not"
NOT_PALINDROME                          ;if flag condition is met, it will print "not"
    LEA R0, not_string
    PUTS
IS_PALINDROME
LEA R0, final_string                    ;then prints end of final output, then HALT
PUTS


HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
stack_addr           .FILL    xFE00

; Addresses of subroutines, other than main
get_user_string_addr .FILL    x3200
strlen_addr          .FILL    x3300
palindrome_addr      .FILL	  x3400


; Reserve memory for strings in the progrtam
user_prompt          .STRINGZ "Enter a string: "
result_string        .STRINGZ "The string is "
not_string           .STRINGZ "not "
final_string         .STRINGZ	"a palindrome\n"

; Reserve memory for user input string
user_string          .BLKW	  100

.END
;=================================================
; Subroutine: get_user_string
; Parameter: R4, the string array's address
; Postcondition: stores a string of characters into array
; Return Value: R4, the complete string of array
;=================================================
.ORIG x3200
ADD R6, R6, #-1                             ;stores register values
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0

LD R1, ASCII_ENTER                          ;loads enter value to R1
LD R2, ASCII_BACKSPACE                      ;loads backspace value to R2

STRING_LOOP
    GETC                                    ;gets character from console
    OUT

    ADD R3, R0, R1                          ;check if enter is pressed, if so end loop
    BRz ENTER_PRESSED
    
    ADD R3, R0, R2                          ;check if backspace is pressed, if so back up array's pointer
    BRz BACKSPACE_PRESSED
    BR NVM
    
    BACKSPACE_PRESSED                       ;backs up array so that backspace does what its supposed to do
        ADD R4, R4, #-1
    BR STRING_LOOP
    NVM

    STR R0, R4, #0                          ;stores the input character into the array
    ADD R4, R4 #1                           ;offsets array by 1 to iterate, loop this until enter pressed
BR STRING_LOOP

ENTER_PRESSED

LDR R2, R6, #0                              ;restore register values
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
ASCII_ENTER             .fill #-10          ;fill values for enter and backspace
ASCII_BACKSPACE         .fill #-8
.END
;=================================================
; Subroutine: strlen
; Parameter: R4, the string array's address
; Postcondition: counts the amount of characters stored in the array
; Return Value: R1, the size of the array
;=================================================
.ORIG x3300
ADD R6, R6, #-1                             ;stores register values
STR R7, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0

AND R1, R1, #0                              ;resets R1's values to 0

LENGTH_LOOP
    LDR R0, R4, #0                          ;Loops for the amount of characters in the array
    ADD R0, R0, #0                          ;checks if the array value is 0, then stop loop
    BRz STOP_COUNT
    ADD R1, R1, #1                          ;adds #1 to R1 to count the characters
    ADD R4, R4, #1                          ;iterates through the array
BR LENGTH_LOOP

STOP_COUNT

LDR R4, R6, #0                              ;reloads register values
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END
;=================================================
; Subroutine: palindrome
; Parameter: R4, the array's first index address & R3, the last index address
; Postcondition: recursively checks each letter to see if the string is a palindrome
; Return Value: R1, the flag to see if its a palindrome or not
;=================================================
.ORIG x3400
ADD R6, R6, #-1                             ;store register values
STR R7, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0



NOT R0, R4                                  ;doing 2's complement subtraction to see if the first and last index address pass eachother
ADD R0, R0, #1                              ;this is base case for the recursion, to see if the function checked through each character
ADD R0, R0, R3
BRnz PALINDROME_DONE

LDR R1, R4, #0                              ;loads first index character into R1
LDR R2, R3, #0                              ;loads last index character into R2

NOT R1, R1                                  ;does 2's complement subtraction to compare if the values are equal to eachother
ADD R1, R1 #1
ADD R0, R1, R2
BRnp NOT_PALINDROME_SUB

ADD R4, R4, #1                              ;if it is equal to eachother, increment first index by 1
ADD R3, R3, #-1                             ;if it is equal to eachother, decrement last index by 1

JSRR R5                                     ;jump back into the subroutine
BR DONE

NOT_PALINDROME_SUB                          ;if its not equal to eachother, set flag to 0
AND R1, R1, #0
BR DONE

PALINDROME_DONE                             ;if it is a palindrome and checked every character, set flag to 1
AND R1, R1, #0
ADD R1, R1, #1

DONE

LDR R5, R6, #0                              ;reload register values
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END