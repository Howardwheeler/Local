;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 8, ex 2
; Lab section: 21
; TA: Karan and Cody
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

; Test harness
;-------------------------------------------------
GETC
OUT

ADD R1, R0, #0

LD R5, PARITY_CHECK_3600
JSRR R5

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
PARITY_CHECK_3600 .fill x3600
.end

;=================================================
; Subroutine: PARITY_CHECK_3600
; Parameter: // Fixme
; Postcondition: // Fixme
; Return Value (R3): // Fixme
;=================================================

.orig x3600

; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0
; Code
AND R3, R3, #0
ADD R2, R2, #1
LD R7, COUNT

LOOP
    AND R4, R1, R2
    BRz SKIP
    ADD R3, R3, #1
    SKIP
    ADD R2, R2, R2
    ADD R7, R7, #-1
    BRz DONE
    BR LOOP
DONE

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1
RET
COUNT .fill #16
.end