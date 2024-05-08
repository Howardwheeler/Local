;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 1
; TA: Karan & Cody
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================
.ORIG x3000		
    LD R6, STACK_ADDR

    START_FRESH ;restart
    LD R1, numberArrayPtr
    LD R2, charLimit
    AND R4, R4, #0
    LD R5, SUB_ARRAY_TO_DECIMAL
    ST R4, FLAG ;stores 0 back into flag

    ;start of code--------------------------------
    LD R0, introPromptPtr
    PUTS

    ;READ INITIAL VALUE ---------------------------
    GETC ;gets first value
    OUT

    LD R3, DEC_enter ; checks if input is enter
    ADD R3, R3, R0
    BRz TERMINATE ; goes to halt

    LD R3, DEC_plus ; checks if input is plus
    ADD R3, R3, R0
    BRz FLAG_POSITIVE ; flags positive

    LD R3, DEC_minus ; checks if input is minus
    ADD R3, R3, R0
    BRz FLAG_NEGATIVE ; flags negative

    LD R3, ASCII_CONVERT_x3000 ;checks if input is not number
    ADD R3, R3, R0
    BRn CHARACTER_DETECTED
    BRz FLAG_INITIAL_ZERO

    LD R3, DEC_9 ;checks if input is not number
    ADD R3, R3, R0
    BRp CHARACTER_DETECTED ;error, restart
    ;-------------------------------------------------

    STR R0, R1, #0 ;stores first input
    JSRR R5 ;calls decimal subroutine

    ADD R1, R1, #1 ;offset by 1
    ADD R2, R2 #-1 ;iterate charLimit

    HUMAN_INPUT_START ;human input loop
        GETC
        OUT

        ZERO_HUMAN_INPUT_START

        LD R3, DEC_enter ; checks if input is enter
        ADD R3, R3, R0
        BRz FINISH_INPUT ; finishes loop

        LD R3, ASCII_CONVERT_x3000 ;checks if ASCII of character is not 0-9
        ADD R3, R3, R0
        BRn CHARACTER_DETECTED ;if negative, ASCII is under 0

        LD R3, DEC_9 ;checks if input is not number
        ADD R3, R3, R0
        BRp CHARACTER_DETECTED ;if positive, ASCII is over 9

        STR R0, R1, #0 ;store in array
        JSRR R5 ;calls decimal subroutine

        ADD R1, R1, #1 ;offset by 1
        ADD R2, R2 #-1 ;iterate charLimit
    BRz FINISH_INPUT
    BR HUMAN_INPUT_START

    ;-----------------------------------------
    FLAG_NEGATIVE ;stores memory for negative
        ADD R3, R3, #-1
        ST R3, FLAG
    BR FLAG_INITIAL_ZERO ;goes to check if next input is 0

    FLAG_POSITIVE ;stores memory for negative
        ADD R3, R3, #1
        ST R3, FLAG
    BR FLAG_INITIAL_ZERO ;goes to check if next input is 0

    FLAG_INITIAL_ZERO
        GETC
        OUT

        LD R3, ASCII_CONVERT_x3000
        ADD R3, R3, R0
    BRz FLAG_INITIAL_ZERO
    BR ZERO_HUMAN_INPUT_START

    CHARACTER_DETECTED ;user input character, restart
        LD R0, newline ;newline
        OUT
        LD R0, errorMessagePtr
        PUTS
    BR START_FRESH

    FINISH_INPUT

    LD R3, FLAG ;loads -1 if negative, 0 or 1 if not
    BRzp TERMINATE
        NOT R4, R4
        ADD R4, R4, #1

    TERMINATE
    HALT 

    ;LOCAL DATA----------------
    DEC_enter               .FILL #-10
    DEC_plus                .FILL #-43
    DEC_minus               .FILL #-45
    DEC_9                   .FILL #-57
    ASCII_CONVERT_x3000     .FILL #-48
    charLimit               .FILL #5
    newline                 .FILL #10
    STACK_ADDR              .FILL xFE00
    introPromptPtr          .FILL xB000
    errorMessagePtr         .FILL xB200
    numberArrayPtr          .FILL xB400
    SUB_ARRAY_TO_DECIMAL    .FILL x3200
    FLAG                    .BLKW #1
.END
;====================================================================================

.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"
.END					
;====================================================================================

.ORIG xB200	 ; error message
.STRINGZ	 "ERROR: invalid input\n"
.END
;====================================================================================

.ORIG xB400  ; array placement
.BLKW	#5
.END
;====================================================================================

;====================================================================================
; Subroutine: SUB_ARRAY_TO_DECIMAL
;====================================================================================
.ORIG x3200
    ADD R6, R6, #-1
    STR R7, R6, #0 ;back up return location

    LD R3, multiplicationFactor
    LDR R0, R1, #0 ;load number from array
    LD R7, ASCII_CONVERT_x3200
    ADD R0, R0, R7 ;converts ASCII to decimal value
    ADD R7, R4, #0 ; loads factor to multiply with

    MULTIPLY_TEN
        ADD R4, R4, R7 ;multiplies R4 by 10
        ADD R3, R3, #-1
    BRp MULTIPLY_TEN

    ADD R4, R4, R0 ;then add by new value

    LDR R7, R6, #0 ;load return location
    ADD R6, R6, #1
    RET ;go back

    ;LOCAL DATA----------------
    multiplicationFactor    .FILL #9
    ASCII_CONVERT_x3200     .FILL #-48
.END
;====================================================================================

;-------------
;Instructions
;-------------

; output intro prompt
						
; Set up flags, counters, accumulators as needed

; Get first character, test for '\n', '+', '-', digit/non-digit 	
					
; is very first character = '\n'? if so, just quit (no message)!

; is it = '+'? if so, ignore it, go get digits

; is it = '-'? if so, set neg flag, go get digits
					
; is it < '0'? if so, it is not a digit	- o/p error message, start over

; is it > '9'? if so, it is not a digit	- o/p error message, start over
				
; if none of the above, first character is first numeric digit - convert it to number & store in target register!
					
; Now get remaining digits from user in a loop (max 5), testing each to see if it is a digit, and build up number in accumulator

; remember to end with a newline!

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.
