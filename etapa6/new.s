# Eduarda Trindade 274709

# START ASM GEN
    .section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:
	.long	111

	.globl	_b
	.type	_b, @object
	.size	_b, 4
_b:
	.long	88

	.globl	_c
	.type	_c, @object
	.size	_c, 4
_c:
	.long	73

# STRING
_meuString:
	.string	"%d\n"
	.text

# BEGIN FUN    
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp

# COPY
	movl	_b(%rip), %eax
	movl	%eax, _a(%rip)

# PRINT
	movl	_c(%rip), %eax
	movl	%eax, %esi
	leaq	_meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# RETURN
	movl	$99, %eax

# END FUN
	popq	%rbp
	ret
	.cfi_endproc

# FIXED
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits	

