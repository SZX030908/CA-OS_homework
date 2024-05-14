	.file	"BubbleSort.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
.LFB0 = .
	addi.w	$r16,$r0,9			# 0x9
	la.local	$r17,array
	or	$r15,$r17,$r0
	b	.L2
.L3:
	addi.w	$r12,$r12,-4
	beq	$r12,$r15,.L7
.L4:
	ld.w	$r13,$r12,-4
	ld.w	$r14,$r12,0
	bge	$r13,$r14,.L3
	st.w	$r14,$r12,-4
	st.w	$r13,$r12,0
	b	.L3
.L7:
	addi.w	$r16,$r16,-1
	beq	$r16,$r0,.L5
.L2:
	addi.w	$r12,$r17,36
	b	.L4
.L5:
	or	$r4,$r0,$r0
	jr	$r1
.LFE0:
	.size	main, .-main
	.globl	array
	.data
	.align	2
	.type	array, @object
	.size	array, 40
array:
	.word	5
	.word	7
	.word	2
	.word	4
	.word	0
	.word	1
	.word	8
	.word	9
	.word	6
	.word	3
	.section	.eh_frame,"aw",@progbits
.Lframe1:
	.4byte	.LECIE1-.LSCIE1
.LSCIE1:
	.4byte	0
	.byte	0x3
	.ascii	"\000"
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.byte	0xc
	.byte	0x3
	.byte	0
	.align	2
.LECIE1:
.LSFDE1:
	.4byte	.LEFDE1-.LASFDE1
.LASFDE1:
	.4byte	.LASFDE1-.Lframe1
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	2
.LEFDE1:
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
