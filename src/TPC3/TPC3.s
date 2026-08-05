.globl updateImage  # void updateImage( buffer rdi, x rsi, y rdx, val cl, base r8)
.globl computePoint # unsigned char computePoint( double x, double y)
.section .note.GNU-stack,"",@progbits
.text

FOUR: .double 4.0

updateImage:
    imul %rdx, %r8
    addq %r8, %rdi
    leaq (%rdi,%rsi,1), %rdx
    movb %cl, (%rdx)
    retq

computePoint:
    xor %rax, %rax
    pxor %xmm2, %xmm2      #xmm2 = zr
    pxor %xmm3, %xmm3      #xmm3 = zi
ciclo:
    cmpq $255, %rax
    jae endC

    movsd %xmm2, %xmm5
    movsd %xmm3, %xmm6
    mulsd %xmm2, %xmm5     #xmm5 = zr*zr
    mulsd %xmm3, %xmm6     #xmm6 = zi*zi

    movsd %xmm5, %xmm4
    addsd %xmm6, %xmm4
    ucomisd FOUR(%rip), %xmm4   #xmm5+xmm6 < 4
    jae endC

    #nr
    movsd %xmm5, %xmm4
    subsd %xmm6, %xmm4
    addsd %xmm0, %xmm4     #xmm4 -> nr

    #ni
    movsd %xmm2, %xmm7
    mulsd %xmm3, %xmm7
    addsd %xmm7, %xmm7
    addsd %xmm1, %xmm7     #xmm7 -> ni

    movsd %xmm4, %xmm2     #zr = nr
    movsd %xmm7, %xmm3     #zi = ni
    incq %rax
    jmp ciclo               #volta pro while
endC:
    retq
