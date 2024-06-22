.section        __TEXT,__text,regular,pure_instructions
.build_version macos, 12, 0     sdk_version 13, 1
.global _main 
.p2align        4, 0x90

_main:
	## Print string to stdout
	movq $0x2000004, %rax           ## System call for sys_write
	movq $1, %rdi                 	## 1 is stdout
	leaq hello(%rip), %rsi          ## Relative string addr
	movq $20, %rdx                	## Len (bytes)
	syscall                    	

	## Exit the program
	movq $0x2000001, %rax           ## System call for sys_exit
	xorq %rdi, %rdi               	## Status 0
	syscall

hello:
	.asciz "Hello Victoria Chan!"
