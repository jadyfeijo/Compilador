# START ASM GEN
	.section	.rodata

# string
.meuString: 
    .string "%d\n"
    .text

# BEGIN FUN
	.globl	main 
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	
# PRINT
	movl	$5, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

# END FUN
	popq	%rbp
	ret
	.cfi_endproc

# FIXED
    .size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
