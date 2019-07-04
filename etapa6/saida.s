# START ASM GEN
	.section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
_E:	.long	5
_I:	.long	1
_O:	.long	0

	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:	.long	0

	.globl	_b
	.data
	.type	_b, @object
	.size	_b, 4
_b:	.long	0

# STRING
.meuString:
	.string "%d\n" 
	.text

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# BEGIN FUN
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp

# NOT FINISHED TAC 1

# COPY
	movl	_b(%rip), %eax
	movl	%eax, _a(%rip)

# NOT FINISHED TAC 1

# NOT FINISHED TAC 33

# PRINT
	movl	_a(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 1

# RETURN
	movl	_O(%rip), %eax

# END FUN
	popq	%rbp
	ret
	.cfi_endproc

# FIXED
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
