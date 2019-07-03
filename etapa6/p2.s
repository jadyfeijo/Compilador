# START ASM GEN
    .text
	.section	.rodata

# string
.meuString: 
    .string "%d\n"
    .text

# BEGIN FUN
	.globl	main
    .type	main, @function

main:
	.cfi_startproc
	pushq	%rbp

	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6

# PRINT
	movl	$5, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

# END FUN
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

# FIXED
    .size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
