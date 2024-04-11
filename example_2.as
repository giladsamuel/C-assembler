; file exampel_1
.entry LIST
.extern W
.define sz = 2
MAIN: add r3, LIST
LOOP: prn #48
      mcr m1
        inc r6
        move r3,W
      endmcr
lea STR, r6
inc r6
mov r3, W
sub r1, r4
      mcr m2
        inc r2
        sub r2,r6
        sub r1,r7
      endmcr
bne END
cmp val1, #-6
bne W
dec K

.entry MAIN   
sub LOOP[10] ,sz 
END: hlt
STR: .string "abcd"
LIST: .data 6, -9
.data -100
.entry K
K: .data 31
.extern val1

