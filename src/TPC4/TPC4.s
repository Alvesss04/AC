.globl allocate # void *allocate( heap *h, unsigned long long int size );
.globl deallocate # void deallocate( void * p );
.equ HEADER_SIZE, 16  #size of space for memory region header
.equ HDR_SIZE_OFFSET, 8  #Location of the size field in the header
.equ HDR_AVAIL_OFFSET, 0 #Location of the "available" flag in the header
.equ UNAVAILABLE, 0 #space that has been given out
.equ AVAILABLE, 1   #space that has been returned
.equ HEAP_LIMIT, 16             #Location of end address in the heap descriptor
.equ HEAP_TOP_OFFSET, 8         #Location of the heap top address field in the heap descriptor
.equ HEAP_BASE_OFFSET, 0        #Location of the heap base address field in the heap descript
.equ NULL, 0
.section .note.GNU-stack,"",@progbits
.text
allocate: # void *allocate( heap *h, unsigned long long int size );
#                              rdi             rsi
    movq HEAP_BASE_OFFSET(%rdi), %rax
    movq $AVAILABLE, %r10
    movq $UNAVAILABLE,%r9
cicle:
    cmpq %rax, HEAP_LIMIT(%rdi)
    jbe failed
    cmpq %rax, HEAP_TOP_OFFSET(%rdi)
    jbe checkFinalAvailableSize
    cmpq (%rax), %r10
    je checkAvailableSize
stepNextBlock:
    # "jump" to next block
    movq %rax , %rcx
    addq $HDR_SIZE_OFFSET, %rcx
    addq (%rcx), %rax
    addq $HEADER_SIZE, %rax
    jmp cicle
checkAvailableSize:
    #bloco esta disponivel mas nao sabemos seu tamanho
    movq %rax , %rcx
    addq $HDR_SIZE_OFFSET, %rcx

    cmpq (%rcx), %rsi
    jbe allocated

    jmp stepNextBlock
checkFinalAvailableSize:
    # chegamos no topo e temos que checar se ha espaco na memoria total
    movq %rax, %rcx
    addq %rsi, %rcx
    addq $HEADER_SIZE, %rcx

    cmpq %rcx, HEAP_LIMIT(%rdi)
    jb failed
    # colocar o size no HDR_SIZE_OFFSET
    # atualizar o top

    movq %rcx, HEAP_TOP_OFFSET(%rdi)
    movq %rax, %rdx
    addq $HDR_SIZE_OFFSET, %rdx
    movq %rsi, (%rdx)
    jmp allocated
allocated:
    #somar o offset do HEADER_SIZE ao %rax isso da a primeira posicao do
    #vetor que foi allocate
    #devolver > rax + 16
    #COLOCAR UNAVAILABLE

    movq %r9, (%rax)
    addq $HEADER_SIZE, %rax
    jmp end
failed:
    #coloca o valor de rax a NULL (0), como pedido no enunciado
    movq $NULL, %rax
    jmp end
end:
    retq
deallocate: # void deallocate( void * p );
#                                 rdi
    subq $HEADER_SIZE, %rdi
    movq $AVAILABLE, (%rdi)
    retq
