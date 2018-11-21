	.file	"add.c"
	.section	".text"
	.align 4
	.global add
	.type	add, #function
	.proc	04
add:
	save	%sp, -120, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	ld	[%fp+68], %g2
	ld	[%fp+72], %g1
	add	%g2, %g1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %g1
	mov	%g1, %i0
	return	%i7+8
	 nop
	.size	add, .-add
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -120, %sp
	mov	1, %o0
	mov	3, %o1
	call	add, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-20]
	mov	0, %g1
	mov	%g1, %i0
	return	%i7+8
	 nop
	.size	main, .-main
	.ident	"GCC: (GNU) 4.3.3"
