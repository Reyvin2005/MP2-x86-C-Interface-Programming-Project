; Group 9, LBYARCH S12A 
; Siongco, Raine Margaux A. 
; Tan, Reyvin Matthew T.

section .data
section .text
bits 64
default rel

global saxpy_simd

; saxpy_simd(float A, float* X, float* Y, float* Z, int n)

saxpy_simd:
    push   rsi                      ; rsi register (non-volatile)
    push   rbp                      ; old base pointer
    mov    rbp, rsp                 ; Set up new base pointer = current stack pointer
    add    rbp, 16                  ; Adjust rbp to account for 2 pushes (8 bytes each)
    add    rbp, 8                   ; Additional adjustment for stack alignment
    
    mov    rsi, [rbp + 32]          ; Load n (loop counter) from stack into rsi
    movss  xmm1, xmm0               ; Copy A (scalar multiplier) from xmm0 to xmm1 for backup
    
loop:
    cmp     rsi, 0                  ; Compare loop counter (n) with 0
    je      end                     ; Jump to end if n == 0 (no more elements)

    mulss   xmm0, [rdx]             ; Multiply A (in xmm0) by X[i] (pointed to by rdx)
    addss   xmm0, [r8]              ; Add Y[i] (pointed to by r8) to the result
    movss   [r9], xmm0              ; Store result Z[i] to memory (pointed to by r9)

    add     rdx, 4                  ; Move X pointer to next float (4 bytes forward)
    add     r8, 4                   ; Move Y pointer to next float (4 bytes forward)
    add     r9, 4                   ; Move Z pointer to next float (4 bytes forward)
    
    dec     rsi                     ; Decrement loop counter (n--)
    movss   xmm0, xmm1              ; Restore original A value from backup
    jmp     loop                    ; Jump back to start of loop

end:
    pop    rbp                     
    pop    rsi                      
    ret                            