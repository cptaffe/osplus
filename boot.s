
// NOTE: this file contains the assembly which is
// run before booting.

.set ALIGN,    1 << 0
.set MEMINFO,  1 << 1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

// multiboot header
.section .multiboot_header
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

// stack definition
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 0x4000
stack_top:

// entry point
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp // set stack.
	call GlobalEntryPoint // call global entry point

