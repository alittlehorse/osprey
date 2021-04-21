; TinyRAM V=2.000 M=vn W=16 K=16
;;; avarage
;;; primary input: DATA_HASH
;;; aux input: DATA
;;; suppose the aux input is a array which length is 20
;;; compute the avarage of data,which hash is DATA_HASH
;;; 1. hash aux input and compare with the DATA_HASH
;;; 2. avarage the aux inpute and out the result

;;;we just complete the step2 firstly, and the hash function is hard.
store.w 0, r0                    ; 0:
mov r0, 32768                    ; 4:
read r1, 0                       ; 8: read the first word in the primary word
cjmp 28                          ; 12: if the flag is 1 ,jump 28
add r0, r0, 2                    ; 16:
store.w r0, r1                   ; 20:
jmp 8                            ; 24:this prelude can store the primary input in the momery
store.w 32768, r0                ; 28: end of prelude. put the data end index in the  32768
mov r3, 0                        ; 44:r3 is the count index of auxiliary input
mov r4, 0                        ; 48:r4 is the sum of r2
_loop:read r2, 1                 ; 36: read auxiliary input in r2 (note that pairs are processed in reverse order)
cjmp _bail                       ; 40
add r3,r3,1                      ; 52:r3 += 1
add r4, r4, r2                   ; 56:r4 = r4 + r2
jmp _loop                        ; 60
_bail: udiv r4,r4,r3             ; 64:r4 = r4/r3
load.w r1,r0
sub r4,r4,r1
answer r4