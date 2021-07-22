; TinyRAM V=2.000 M=vn W=16 K=16
;;;we just complete the step2 firstly, and the hash function is hard.
store.w 0, r0                    ; 0:
mov r0, 32768                    ; 4:
read r1, 0                       ; 8: read the first word in the primary word
cjmp 28                          ; 12: if the flag is 1 ,jump 28
add r0, r0, 2                    ; 16:
store.w r0, r1                   ; 20:
jmp 8                            ; 24:this prelude can store the primary input in the momery
store.w 32768, r0                ; 28: end of prelude. put the data end index in the  32768
read r2, 1                 ; 36: read auxiliary input in r2 (note that pairs are processed in reverse order)
load.w r1,r0
sub r2,r2,r1
answer r2