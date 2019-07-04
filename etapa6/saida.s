# START ASM GEN
	.section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
_O: .long 0
_I: .long 1

_E:	.long	5
_I:	.long	1
_O:	.long	0
_a:	.long	a
_b:	.long	b
_myTemp0:	.long	0

# STRING
.meuString:
	.string "%d\n" 
	.text

# BEGIN FUN
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp

# PRINT
	movl	_I(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# ADD
	movl	_a(%rip), %edx
	movl	_b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp0(%rip)

# COPY
	movl	_myTemp0(%rip), %eax
	movl	%eax, _a(%rip)

# PRINT
	movl	_a(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

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
