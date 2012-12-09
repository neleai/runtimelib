	.text
	.p2align 4,,15
.globl aesrand
	.type	aesrand, @function
aesrand:
	.cfi_startproc
  mov %rdi,%rax
  movdqa    (%rax),%xmm0
  movdqa  16(%rax),%xmm1
  movdqa  32(%rax),%xmm2
  movdqa  48(%rax),%xmm3

  movdqa %xmm0,%xmm4
  movdqa %xmm1,%xmm5
  movdqa %xmm2,%xmm6
  movdqa %xmm3,%xmm7

  aesenc %xmm4,%xmm0
  aesenc %xmm5,%xmm1
  aesenc %xmm6,%xmm2
  aesenc %xmm7,%xmm3

  aesenc %xmm4,%xmm0
  aesenc %xmm5,%xmm1
  aesenc %xmm6,%xmm2
  aesenc %xmm7,%xmm3

  aesenc %xmm4,%xmm0
  aesenc %xmm5,%xmm1
  aesenc %xmm6,%xmm2
  aesenc %xmm7,%xmm3

  aesenc %xmm4,%xmm0
  aesenc %xmm5,%xmm1
  aesenc %xmm6,%xmm2
  aesenc %xmm7,%xmm3

  movdqa %xmm0,   (%rax)
  movdqa %xmm1, 16(%rax)
  movdqa %xmm2, 32(%rax)
  movdqa %xmm3, 48(%rax)

	ret
	.cfi_endproc
