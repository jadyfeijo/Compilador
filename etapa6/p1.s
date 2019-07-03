	.file	"p1.c"
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$111, a(%rip)
	movl	$88, b(%rip)
	movl	$73, c(%rip)
	movl	b(%rip), %eax
	movl	%eax, a(%rip)
	movl	c(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	a(%rip), %eax
	movl	%eax, c(%rip)
	movl	$99, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
