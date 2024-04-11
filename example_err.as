;this file will include errors
;undefined label
MAIN add #2, r4
;undefined operation
Sub r4 , r2
;consecutive commas
mov X[r12] ,        , , r4
;missing commas
lea X          r1
;illegal appearance of comma before the first operand
jsr , Y
;illegal appearance of comma after the last parameter
prn     #4         ,
  ;wrong addressing method for dec 
           dec #4
;data instruction with illegal appearance of characters (not an int)
Z: .data 4  ,  7  ,6.5,3,r,7
;wrong addressing method for mov
   mov r2,  #-99
;illegal appearance of comma before the first operand + missing commas
cmp ,#2       X
;illegal appearance of comma before the first operand + consecutive commas
sub ,#2 ,  ,,r4
.extern X
Y: .string "getgeb gt"
;wrong register for index addressing method
cmp Y[r12]  ,X[r2]