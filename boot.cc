
// NOTE: this file contains the assembly which is
// run before booting.

asm(
".set ALIGN,    1<<0\n"
".set MEMINFO,  1<<1\n"
".set FLAGS,    ALIGN | MEMINFO\n"
".set MAGIC,    0x1BADB002\n"
".set CHECKSUM, -(MAGIC + FLAGS)\n"

// multiboot header
".section .multiboot_header\n"
".align 4\n"
".long MAGIC\n"
".long FLAGS\n"
".long CHECKSUM\n"

// stack definition
".section .bootstrap_stack, \"aw\", @nobits\n"
"stack_bottom:\n"
".skip 0x4000\n"
"stack_top:\n"

// entry point
".section .text\n"
".global _start\n"
".type _start, @function\n"
"_start:\n"
"movl $stack_top, %esp\n" // set stack.
"call _init\n" // global constructors
"call GlobalEntryPoint\n" // call global entry point
"call _fini\n" // global destructors
"cli\n"
"hlt\n"
".Lhang: jmp .Lhang\n" // infinite loop
);
