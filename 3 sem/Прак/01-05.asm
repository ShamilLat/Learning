.section .text
.global exchange

exchange:
    pushl %ebx
    pushl %esi
    pushl %edi
    
    xorl %ecx, %ecx
    decl %edx
    leal (%eax, %edx, 4), %edi
    
    .for:
    cmpl %eax, %edi
    jbe .next
    movl (%eax), %ebx
    movl (%edi), %esi
    cmpl %esi, %ebx
    jbe .ok
    incl %ecx
    movl %ebx, (%edi)
    movl %esi, (%eax)
    .ok:
    subl $4, %edi
    addl $4, %eax
    jmp .for
    
    .next:
    
    popl %edi
    popl %esi
    popl %ebx
    
    ret