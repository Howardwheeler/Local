;--------------------------
;Wheeler, Howard
;Login: hwhee004
;Section: 001
;TA: Karan and Cody
;Lab 01
;--------------------------

.ORIG x3000

    LD R1, DEC_0
    LD R2, DEC_12
    LD R3, DEC_6
    
    DO_WHILE_LOOP
        ADD R1, R1, R2
        ADD R3, R3, #-1
        BRp DO_WHILE_LOOP
    End_DO_WHILE_LOOP
    
    HALT

;Local Data
    
    DEC_0       .FILL   #0
    DEC_12      .FILL   #12
    DEC_6       .FILL   #6

.END