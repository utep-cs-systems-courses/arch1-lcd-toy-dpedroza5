	.arch msp430g2553
	.p2align 1,0

#include "lcdutils.h"
	
	.data
	state:	 #1

	.text
	.global color
jt:
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word GREEN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word CYAN
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word PURPLE
	.word default

	.global color

color:
	cmp #31, &state
	jc default
	mov &state, r13
	add r13, r13
	mov jt(r13), r0

default:
	mov #1, &state
	mov #0xFFFF, r12
	call #font_text
GREEN:
	add #1, &state
	mov #0x07e0, r12
	call #font_text
CYAN:
	add #1, &state
	mov #0xffe0, r12
	call #font_text
PURPLE:
	add #1, &state
	mov #0xf114, r12
	call #font_text
