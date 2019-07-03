# Eduarda Trindade 274709

# START ASM GEN
	.section	.rodata

# STRING
.meuString: 
    .string "%d\n"
    .text

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
_a: .long 111
_b: .long 88
_c: .long 73
_99: .long 99

# BEGIN FUN
	.globl	main 
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp

# COPY
 	movl	_b(%rip), %eax
 	movl	%eax, _a(%rip)

# PRINT
	movl	_c(%rip), %eax
	movl	%eax, %esi
	leaq	.meuString(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# RETURN
	movl	_99(%rip), %eax

# END FUN
	leave
	ret
	.cfi_endproc

# FIXED
    .size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
