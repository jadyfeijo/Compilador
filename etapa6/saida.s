# START ASM GEN
	.section	.rodata

# STRING
.meuString:
	.string "%d\n" 
	.text

# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)
_O: .long 0
_I: .long 1

# BEGIN FUN
	.globl	main
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
