; TinyRAM V=2.000 M=vn W=16 K=16
store.w 0, r0                    ; 0:
mov r0, 32768                    ; 4:
read r1, 0                       ; 8: read the first word in the primary word
cjmp 28                          ; 12: if the flag is 1 ,jump 28
add r0, r0, 2                    ; 16:
store.w r0, r1                   ; 20:
jmp 8                            ; 24:this prelude can store the primary input in the momery
store.w 32768, r0                ; 28: end of prelude. put the data end index in the  32768
read r2, 1                 ; 36: read auxiliary input in r2 (note that pairs are processed in reverse order)
sub r1,r1,r2
answer r1