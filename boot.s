
// NOTE: this file contains the assembly which is
// run before booting.

.set kMagic,    0x1badb002
.set kAlign,    1 << 0
.set kMemory,  1 << 1
.set flags,    kAlign | kMemory
.set checksum, -(kMagic + flags)

// multiboot header
.section .multiboot_header
.align 4
.long kMagic
.long flags
.long checksum

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
