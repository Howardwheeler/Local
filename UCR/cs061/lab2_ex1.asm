;=================================================
; Name: Howard Wheeler
; Email: hwhee004@ucr.edu
; 
; Lab: lab 2. ex 1
; Lab section: 1
; TA: Karan and Cody
; 
;=================================================
.orig x3000

    LD R1, DEC_65
    LD R2, HEX_41
    
    HALT
    
    DEC_65  .FILL   #65
    HEX_41  .FILL   x41
    
.end