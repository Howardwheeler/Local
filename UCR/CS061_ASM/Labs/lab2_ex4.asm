;=================================================
; Name: Howard Wheeler 
; Email:  hwhee004@ucr.edu
; 
; Lab: lab 2, ex 4
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

    LD R0, HEX_61
    LD R1, HEX_1A
    
    DO_WHILE_LOOP
        OUT
        ADD R0, R0, #1
        ADD R1, R1, #-1
        BRp DO_WHILE_LOOP
    END_DO_WHILE_LOOP
    
    HALT
    
    HEX_61 .FILL x61
    HEX_1A .FILL x1A
    
.end
