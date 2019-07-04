# START ASM GEN
	.section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)

_myTemp1:	.long	0

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

_myTemp0:	.long	0

_"Got you!":	.string	"Got you!"

_"Ok!":	.string	"Ok!"

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
	 

# IF
	 

# PRINT
	movl	_"Ok!"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# LABEL
myLabel0:

# LESS
	 

# IF
	 

# PRINT
	movl	_"Got you!"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# JUMP
	 

# LABEL
myLabel1:

# PRINT
	movl	_a(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# LABEL
myLabel2:

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
