
// This file defines some functions used in task.cc
// The name mangling is from g++. This is poor practice as
// it will not be the same on other compilers.

.text
// void basilisk::Task::Switch(Task *task)
.globl	_ZN8basilisk4Task6SwitchEPS0_
.align	16, 0x90
.type	_ZN8basilisk4Task6SwitchEPS0_,@function
_ZN8basilisk4Task6SwitchEPS0_:
	pushl	%ebp
	movl	%esp, %ebp

	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx

	// this @ %eax
	// task @ %ecx

	// The first field in this & task is stackp,
	// which stands for stack pointer. All necessary information
	// should be pushed onto the first stack and poped off the second
	// stack.

	// First, push all the information,
	// then save esp in stackp of this,
	// mov stackp from task to esp,
	// pop off the information in reverse order.

	// The information that must be saved is:
	// 1. eip, already on stack.
	// 2. esp, saved in stackp.
	// 3. callee saved registers.

	subl	$12, %esp

	movl	%ebx, -4(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -12(%ebp)

	movl	%esp, (%eax)
	movl	(%ecx), %esp
	leal	12(%esp), %ebp

	movl	-4(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-12(%ebp), %edi

	addl	$12, %esp
	popl	%ebp
	ret

// void basilisk::Task::Initialize(void *call)
.globl	_ZN8basilisk4Task10InitializeEPv
.align	16, 0x90
.type	_ZN8basilisk4Task10InitializeEPv,@function
_ZN8basilisk4Task10InitializeEPv:
	pushl	%ebp
	movl	%esp, %ebp

	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx

	// this @ %eax
	// func @ %ecx

	// To initiate a task, we have to create a dummy stack
	// that Switch can later use.

	// switch to this's stackp.
	// 1. push eip (func)
	// 2. push esp (pointer to stack).
	// 3. push callee saved registers.

	movl	%esp, %edx   // save current esp
	movl	(%eax), %esp // move stackp to esp
	movl	%esp, %ebp

	// push what the thread should return to, Sleep.
	pushl	%ecx // push func
	pushl	%ebp // push stack, after sleep push.
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, -12(%ebp)

	movl	%esp, (%eax)
	movl	%edx, %esp

	popl	%ebp
	ret
