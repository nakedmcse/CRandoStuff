	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 13, 1
	.globl	_swap                           ## -- Begin function swap
	.p2align	4, 0x90
_swap:                                  ## @swap
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, (%rax)
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rcx
	movq	%rcx, (%rax)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_heapify                        ## -- Begin function heapify
	.p2align	4, 0x90
_heapify:                               ## @heapify
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-16(%rbp), %eax
	shll	$1, %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	movl	-16(%rbp), %eax
	shll	$1, %eax
	addl	$2, %eax
	movl	%eax, -28(%rbp)
	movl	-24(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB1_3
## %bb.1:
	movq	-8(%rbp), %rax
	movslq	-24(%rbp), %rcx
	movl	(%rax,%rcx,8), %eax
	movq	-8(%rbp), %rcx
	movslq	-20(%rbp), %rdx
	cmpl	(%rcx,%rdx,8), %eax
	jge	LBB1_3
## %bb.2:
	movl	-24(%rbp), %eax
	movl	%eax, -20(%rbp)
LBB1_3:
	movl	-28(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB1_6
## %bb.4:
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movl	(%rax,%rcx,8), %eax
	movq	-8(%rbp), %rcx
	movslq	-20(%rbp), %rdx
	cmpl	(%rcx,%rdx,8), %eax
	jge	LBB1_6
## %bb.5:
	movl	-28(%rbp), %eax
	movl	%eax, -20(%rbp)
LBB1_6:
	movl	-20(%rbp), %eax
	cmpl	-16(%rbp), %eax
	je	LBB1_8
## %bb.7:
	movq	-8(%rbp), %rdi
	movslq	-16(%rbp), %rax
	shlq	$3, %rax
	addq	%rax, %rdi
	movq	-8(%rbp), %rsi
	movslq	-20(%rbp), %rax
	shlq	$3, %rax
	addq	%rax, %rsi
	callq	_swap
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %esi
	movl	-20(%rbp), %edx
	callq	_heapify
LBB1_8:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_heapPush                       ## -- Begin function heapPush
	.p2align	4, 0x90
_heapPush:                              ## @heapPush
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	%ecx, -24(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdi
	movq	-16(%rbp), %rax
	movslq	(%rax), %rsi
	shlq	$3, %rsi
	callq	_realloc
	movq	%rax, %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	subl	$1, %eax
	movl	%eax, -28(%rbp)
	movl	-20(%rbp), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movslq	-28(%rbp), %rcx
	movl	%edx, (%rax,%rcx,8)
	movl	-24(%rbp), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movslq	-28(%rbp), %rcx
	movl	%edx, 4(%rax,%rcx,8)
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	cmpl	$0, -28(%rbp)
	movb	%al, -29(%rbp)                  ## 1-byte Spill
	je	LBB2_3
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)                 ## 8-byte Spill
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	$2, %ecx
	cltd
	idivl	%ecx
	movl	%eax, %ecx
	movq	-40(%rbp), %rax                 ## 8-byte Reload
	movslq	%ecx, %rcx
	movl	(%rax,%rcx,8), %eax
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rcx
	movslq	-28(%rbp), %rdx
	cmpl	(%rcx,%rdx,8), %eax
	setg	%al
	movb	%al, -29(%rbp)                  ## 1-byte Spill
LBB2_3:                                 ##   in Loop: Header=BB2_1 Depth=1
	movb	-29(%rbp), %al                  ## 1-byte Reload
	testb	$1, %al
	jne	LBB2_4
	jmp	LBB2_5
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rdi
	movslq	-28(%rbp), %rax
	shlq	$3, %rax
	addq	%rax, %rdi
	movq	-8(%rbp), %rax
	movq	(%rax), %rsi
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	$2, %ecx
	cltd
	idivl	%ecx
	cltq
	shlq	$3, %rax
	addq	%rax, %rsi
	callq	_swap
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	$2, %ecx
	cltd
	idivl	%ecx
	movl	%eax, -28(%rbp)
	jmp	LBB2_1
LBB2_5:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_heapPop                        ## -- Begin function heapPop
	.p2align	4, 0x90
_heapPop:                               ## @heapPop
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rax
	cmpl	$0, (%rax)
	jg	LBB3_2
## %bb.1:
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	LBB3_3
LBB3_2:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	-24(%rbp), %rdx
	movl	(%rdx), %edx
	subl	$1, %edx
	movslq	%edx, %rdx
	movq	(%rcx,%rdx,8), %rcx
	movq	%rcx, (%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %ecx
	subl	$1, %ecx
	movl	%ecx, (%rax)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdi
	movq	-24(%rbp), %rax
	movslq	(%rax), %rsi
	shlq	$3, %rsi
	callq	_realloc
	movq	%rax, %rcx
	movq	-16(%rbp), %rax
	movq	%rcx, (%rax)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdi
	movq	-24(%rbp), %rax
	movl	(%rax), %esi
	xorl	%edx, %edx
	callq	_heapify
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB3_3:
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3                               ## -- Begin function main
LCPI4_0:
	.quad	0x412e848000000000              ## double 1.0E+6
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4
LCPI4_1:
	.long	1127219200                      ## 0x43300000
	.long	1160773632                      ## 0x45300000
	.long	0                               ## 0x0
	.long	0                               ## 0x0
LCPI4_2:
	.quad	0x4330000000000000              ## double 4503599627370496
	.quad	0x4530000000000000              ## double 1.9342813113834067E+25
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movl	$0, -4(%rbp)
	xorl	%eax, %eax
	movl	%eax, %edi
	callq	_time
	movl	%eax, %edi
	callq	_srand
	movq	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	movl	$4294967295, %edx               ## imm = 0xFFFFFFFF
	movl	$1, %ecx
	callq	_heapPush
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	movl	$4294967295, %edx               ## imm = 0xFFFFFFFF
	movl	$2, %ecx
	callq	_heapPush
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	movl	$4294967295, %edx               ## imm = 0xFFFFFFFF
	movl	$3, %ecx
	callq	_heapPush
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	movl	$4294967291, %edx               ## imm = 0xFFFFFFFB
	movl	$4, %ecx
	callq	_heapPush
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	movl	$4294967287, %edx               ## imm = 0xFFFFFFF7
	movl	$5, %ecx
	callq	_heapPush
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$0, -20(%rbp)
	jle	LBB4_3
## %bb.2:                               ##   in Loop: Header=BB4_1 Depth=1
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	callq	_heapPop
	movq	%rax, -32(%rbp)
	movl	-28(%rbp), %esi
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB4_1
LBB4_3:
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	callq	_clock
	movq	%rax, -40(%rbp)
	movl	$0, -44(%rbp)
LBB4_4:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10000000, -44(%rbp)            ## imm = 0x989680
	jge	LBB4_7
## %bb.5:                               ##   in Loop: Header=BB4_4 Depth=1
	callq	_rand
	movl	$11, %ecx
	cltd
	idivl	%ecx
	xorl	%eax, %eax
	subl	%edx, %eax
	movl	%eax, -48(%rbp)
	callq	_rand
	movl	$10000000, %ecx                 ## imm = 0x989680
	cltd
	idivl	%ecx
	movl	%edx, -52(%rbp)
	movl	-48(%rbp), %edx
	movl	-52(%rbp), %ecx
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	callq	_heapPush
## %bb.6:                               ##   in Loop: Header=BB4_4 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	LBB4_4
LBB4_7:
	callq	_clock
	movq	-40(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, %xmm0
	movaps	LCPI4_1(%rip), %xmm1            ## xmm1 = [1127219200,1160773632,0,0]
	punpckldq	%xmm1, %xmm0            ## xmm0 = xmm0[0],xmm1[0],xmm0[1],xmm1[1]
	movapd	LCPI4_2(%rip), %xmm1            ## xmm1 = [4.503599627370496E+15,1.9342813113834067E+25]
	subpd	%xmm1, %xmm0
	movaps	%xmm0, %xmm1
	unpckhpd	%xmm0, %xmm0                    ## xmm0 = xmm0[1,1]
	addsd	%xmm1, %xmm0
	movsd	LCPI4_0(%rip), %xmm1            ## xmm1 = mem[0],zero
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -64(%rbp)
	movsd	-64(%rbp), %xmm0                ## xmm0 = mem[0],zero
	leaq	L_.str.4(%rip), %rdi
	movb	$1, %al
	callq	_printf
	callq	_clock
	movq	%rax, -40(%rbp)
	movl	$0, -68(%rbp)
LBB4_8:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$0, -20(%rbp)
	jle	LBB4_10
## %bb.9:                               ##   in Loop: Header=BB4_8 Depth=1
	leaq	-16(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	callq	_heapPop
	movq	%rax, -80(%rbp)
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -68(%rbp)
	jmp	LBB4_8
LBB4_10:
	callq	_clock
	movq	-40(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, %xmm0
	movaps	LCPI4_1(%rip), %xmm1            ## xmm1 = [1127219200,1160773632,0,0]
	punpckldq	%xmm1, %xmm0            ## xmm0 = xmm0[0],xmm1[0],xmm0[1],xmm1[1]
	movapd	LCPI4_2(%rip), %xmm1            ## xmm1 = [4.503599627370496E+15,1.9342813113834067E+25]
	subpd	%xmm1, %xmm0
	movaps	%xmm0, %xmm1
	unpckhpd	%xmm0, %xmm0                    ## xmm0 = xmm0[1,1]
	addsd	%xmm1, %xmm0
	movsd	LCPI4_0(%rip), %xmm1            ## xmm1 = mem[0],zero
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -64(%rbp)
	movl	-68(%rbp), %esi
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movsd	-64(%rbp), %xmm0                ## xmm0 = mem[0],zero
	leaq	L_.str.6(%rip), %rdi
	movb	$1, %al
	callq	_printf
	movq	-16(%rbp), %rdi
	callq	_free
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Simple Priority Queue Enqueued: 1:1,2:1,3:1,4:5,5:9\n"

L_.str.1:                               ## @.str.1
	.asciz	"Simple Priority Queue Dequeued: "

L_.str.2:                               ## @.str.2
	.asciz	"%d "

L_.str.3:                               ## @.str.3
	.asciz	"\n"

L_.str.4:                               ## @.str.4
	.asciz	"Simple priority queue enqueue time: %f\n"

L_.str.5:                               ## @.str.5
	.asciz	"Simple priority queue dequeued items: %d\n"

L_.str.6:                               ## @.str.6
	.asciz	"Simple priority queue dequeue time: %f\n"

.subsections_via_symbols
