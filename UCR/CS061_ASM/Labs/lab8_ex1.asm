;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 8, ex 1
; Lab section: 21
; TA: Karan and Cody
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

; Test harness
;-------------------------------------------------
LD R5, LOAD_FILL_VALUE_3200
JSRR R5

ADD R1, R1, #1

LD R5, OUTPUT_AS_DECIMAL_3400
JSRR R5

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
LOAD_FILL_VALUE_3200 .fill x3200
OUTPUT_AS_DECIMAL_3400 .fill x3400
.end

;=================================================
; Subroutine: LOAD_FILL_VALUE_3200
; Parameter: R7
; Postcondition: Loads in a value of x1234 into R1
; Return Value: VALUE = x1234
;=================================================

.orig x3200
; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0
; Code
LD R1, VALUE
; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1
RET
VALUE .fill x1234
.end

;=================================================
; Subroutine: OUTPUT_AS_DECIMAL_3400
; Parameter: R1, the fill value
; Postcondition: output to console the fill value
; Return Value: whatever is in fill
;=================================================

.orig x3400

; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0
; Code
LD R7, DIVIDING_VALUE
LD R2, ASCII_CONVERT

ADD R1, R1, #0
BRn NEGATIVE_NUMBER
BR NOW_LOOP

NEGATIVE_NUMBER
NOT R1, R1
ADD R1, R1, #1
AND R0, R0, #1
LEA R0, NEGATIVE
PUTS
BR NOW_LOOP

NOW_LOOP
ADD R3, R3, R1
ADD R5, R3, #0

LOOP_START
AND R4, R4, #0

DIVIDE_LOOP
    ADD R3, R3, R7
    BRn DONE_DIVIDING
    ADD R4, R4, #1
    ADD R5, R3, #0
BR DIVIDE_LOOP
DONE_DIVIDING
ADD R3, R5, #0

ADD R0, R3, #0
NOT R0, R0
ADD R0, R0, #1
ADD R0, R0, R1
BRz NOT_PRINT

ADD R0, R4, R2
OUT
NOT_PRINT

AND R4, R4, #0
ADD R4, R7, #0
AND R7, R7 #0

SET_DIVISOR
    ADD R4, R4, #10
    BRp DONE
    ADD R7, R7, #-1
BR SET_DIVISOR
DONE

ADD R3, R3 #0
BRn RESTORE
BR NVM

RESTORE
AND R3, R3, #0
ADD R3, R3, R1
NVM

ADD R7, R7, #0
BRzp LOOP_DONE
BR LOOP_START
LOOP_DONE

; Restore registers
LDR R5, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
DIVIDING_VALUE .fill #-10000
ASCII_CONVERT   .fill #48
DECIMAL_ARRAY .BLKW	#5
NEGATIVE    .STRINGZ "-"
.end