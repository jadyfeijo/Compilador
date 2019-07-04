# START ASM GEN
	.section	.rodata

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
_IOOO:	.long	0
_myTemp1:	.long	0
_E:	.long	5
_G:	.long	3
_H:	.long	2
_I:	.long	1
_O:	.long	0

	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:	.long	0

	.globl	_c
	.data
	.type	_c, @object
	.size	_c, 4
_c:	.long	0

	.globl	_n
	.data
	.type	_n, @object
	.size	_n, 4
_n:	.long	0

	.globl	_v
	.data
	.type	_v, @object
	.size	_v, 4
_v:	.long	0

	.globl	_x
	.data
	.type	_x, @object
	.size	_x, 4
_x:	.long	0
_myTemp6:	.long	0
_myTemp0:	.long	0
_myTemp5:	.long	0

	.globl	_"nao imprime"
	.data
	.type	_"nao imprime", @object
	.size	_"nao imprime", 4
_"nao imprime":	.long	0
_myLabel2:	.long	0
_myLabel0:	.long	0
_myTemp4:	.long	0

	.globl	_"Got you!"
	.data
	.type	_"Got you!", @object
	.size	_"Got you!", 4
_"Got you!":	.long	0

	.globl	_"Digite"
	.data
	.type	_"Digite", @object
	.size	_"Digite", 4
_"Digite":	.long	0

	.globl	_mat
	.data
	.type	_mat, @object
	.size	_mat, 4
_mat:	.long	0
_myTemp3:	.long	0
_AAA:	.long	0
_EE:	.long	0
_myLabel3:	.long	0
_IO:	.long	0
_myTemp2:	.long	0

	.globl	_")la)la)la"
	.data
	.type	_")la)la)la", @object
	.size	_")la)la)la", 4
_")la)la)la":	.long	0
_myLabel1:	.long	0

	.globl	_"teste"
	.data
	.type	_"teste", @object
	.size	_"teste", 4
_"teste":	.long	0
_myTemp7:	.long	0

# STRING
.meuString:
	.string "%d\n" 
	.text

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# BEGIN FUN
	.globl	incn
	.type	incn, @function
incn:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp

# NOT FINISHED TAC 28

# NOT FINISHED TAC 28

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# ADD
	movl	_x(%rip), %edx
	movl	_n(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp0(%rip)

# RETURN
	movl	_myTemp0(%rip), %eax

# END FUN
	popq	%rbp
	ret
	.cfi_endproc

# BEGIN FUN
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# ADD
	movl	_H(%rip), %edx
	movl	_H(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp1(%rip)

# PRINT
	movl	_myTemp1(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 1

# PRINT
	movl	_"Digite"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 1

# PRINT
	movl	_")la)la)la"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 1

# PRINT
	movl	_"teste"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 21

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 14

# NOT FINISHED TAC 7

# NOT FINISHED TAC 1

# PRINT
	movl	_"Got you!"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 9

# NOT FINISHED TAC 8

# NOT FINISHED TAC 1

# PRINT
	movl	_"nao imprime"(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# NOT FINISHED TAC 8

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 4

# ADD
	movl	_E(%rip), %edx
	movl	_myTemp3(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp4(%rip)

# COPY
	movl	_myTemp4(%rip), %eax
	movl	%eax, _a(%rip)

# NOT FINISHED TAC 8

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 10

# NOT FINISHED TAC 7

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# ADD
	movl	_c(%rip), %edx
	movl	_I(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _myTemp6(%rip)

# COPY
	movl	_myTemp6(%rip), %eax
	movl	%eax, _c(%rip)

# NOT FINISHED TAC 9

# NOT FINISHED TAC 8

# NOT FINISHED TAC 1

# NOT FINISHED TAC 1

# NOT FINISHED TAC 32

# NOT FINISHED TAC 1

# NOT FINISHED TAC 31

# PRINT
	movl	_myTemp7(%rip), %eax
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
