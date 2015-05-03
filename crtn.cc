
asm(
	".section .init\n"
	// contents of .init will be generated here.
	"popl %ebp\n"
	"ret\n"

	".section .fini\n"
	// contents of .fini will be generated here.
	"popl %ebp\n"
	"ret\n"
);
