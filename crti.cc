
asm(
	".section .init\n"
	".global _init\n"
	".type _init, @function\n"
	"_init:\n"
	"push %ebp\n"
	"movl %esp, %ebp\n"
	// contents of .init will be generated here.

	".section .fini\n"
	".global _fini\n"
	".type _fini, @function\n"
	"_fini:\n"
	"push %ebp\n"
	"movl %esp, %ebp\n"
	// contents of .fini will be generated here.
);
