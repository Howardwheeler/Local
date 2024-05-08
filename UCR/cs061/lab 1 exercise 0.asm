;-----------------------
; Wheeler, Howard
; Login :hwhee001
; Section: 
; TA: Karan and Cody
; Lab 1 Exercise 0
;----------------------

.ORIG x3000

    LEA R0, MSG_TO_PRINT
    PUTS
    
    HALT


;Local Data

    MSG_TO_PRINT .STRINGZ "Hello world!!\n"

.END
