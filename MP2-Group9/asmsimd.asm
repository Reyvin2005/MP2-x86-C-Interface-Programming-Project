; Group 9, LBYARCH | S12A 
; Siongco, Raine Margaux A. 
; Tan, Reyvin Matthew T.

section .text
bits 64
default rel

global saxpy_simd

; void saxpy_simd(float A, float* X, float* Y, float* Z, int n)

saxpy_simd:
    push   rbp                      
    push   rbx                      
    mov    rbp, rsp                 ; Set up new base pointer = current stack pointer
    add    rbp, 16                  ; Adjust rbp to account for 2 pushes (8 bytes each)
    
    mov    rcx, [rbp + 40]          ; Load n (loop counter) 
    movss  xmm1, xmm0               ; Copy A (scalar multiplier) from xmm0 to xmm1 for backup
    
loop:
    test    rcx, rcx                ; Compare loop counter
    je      end                     ; Jump to end if n == 0 

    movss   xmm2, [rdx]             ; Load X[i]
    mulss   xmm2, xmm1              ; Multiply A by X[i] 
    addss   xmm2, [r8]              ; Add Y[i] 
    movss   [r9], xmm2              ; Store result Z[i] 

    add     rdx, 4                  ; Move X pointer to next float (4 bytes forward)
    add     r8, 4                   ; Move Y pointer to next float (4 bytes forward)
    add     r9, 4                   ; Move Z pointer to next float (4 bytes forward)
    
    dec     rcx                     ; Decrement loop counter (n--)
    jmp     loop                    

end:
    pop    rbx                     
    pop    rbp                      
    ret                            
