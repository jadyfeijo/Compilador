	.file	"p1.c"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	111
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	88
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.long	73
	.globl	retorno
	.align 4
	.type	retorno, @object
	.size	retorno, 4
retorno:
	.long	99
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

	movl	c(%rip), %edx
	movl	b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	
	movl	a(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	retorno(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
