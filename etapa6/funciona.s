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
_b:	.long	1

_myTemp0:	.long	0

_string0:	.string	"Ok!\n"

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

# EQUAL
	movl	_b(%rip), %edx
	movl	_I(%rip), %eax
	cmpl	%eax, %edx
	jne myLabel0

# PRINT
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	_string0(%rip), %rdi
	call	fwrite@PLT

# LABEL
myLabel0:

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
