; file

.entry LIST
.extern W
.define sz = 2

MAIN:   mov r3, LIST[sz]
LOOP:   jmp W
        mcr m_mcr
                cmp K, #sz
        bne W
        endmcr
        prn #-5
        mov STR[5], STR[2]
        sub r1, r4
        m_mcr
L1:     inc L3
.entry LOOP
        bne LOOP
END:    hlt
.define len = 4
STR:    .string "abcdef"
LIST:   .data 6, -9, len
K:      .data 22
.extern L3