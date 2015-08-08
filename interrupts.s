
.text
.global handler
handler:
	pushl	%ebp
	movl	%esp, %ebp

	// call SystemCallHandler with pointer to
	// arguments stack section.
	subl	$4, %esp
	leal	16(%ebp), %eax // skip return address & other thing.
	movl	%eax, -4(%ebp)
	calll	SystemCallHandler

	addl	$4, %esp
	popl	%ebp
	iret

.global test_interrupts
test_interrupts:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$4, %esp
	movl	$5, -4(%ebp)
	int	$0x80

	addl	$4, %esp
	popl	%ebp
	ret
