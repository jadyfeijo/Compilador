# START ASM GEN
	.section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)

_myTemp1:	.long	0

_A:	.long	9

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

	.globl	_c
	.data
	.type	_c, @object
	.size	_c, 4
_c:	.long	0

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

# COPY
	movl	_E(%rip), %eax
	movl	%eax, _a(%rip)

# COPY
	movl	_O(%rip), %eax
	movl	%eax, _b(%rip)

# COPY
	movl	_A(%rip), %eax
	movl	%eax, _c(%rip)

# ADD
	movl	_b(%rip), %edx
	movl	_c(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp0(%rip)

# COPY
	movl	_myTemp0(%rip), %eax
	movl	%eax, _a(%rip)

# EQUAL
	movl	_b(%rip), %edx
	movl	_I(%rip), %eax
	cmpl	%eax, %edx
	jne myLabel0

# PRINT
	movl	_a(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# JUMP
	jmp	myLabel1

# LABEL
myLabel0:

# PRINT
	movl	_b(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# LABEL
myLabel1:

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
