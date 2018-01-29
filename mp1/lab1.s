	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"lab1.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"What is the minimum threat level (or -1 to exit)? \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"Goodbye.\000"
	.align	2
.LC3:
	.ascii	"\012The input is invalid, you entered: %d\012\000"
	.align	2
.LC4:
	.ascii	"\012The minimum threat level(>= 3) is %d\012\000"
	.align	2
.LC5:
	.ascii	"How many times must a threat level occur so not a f"
	.ascii	"alse alarm? \000"
	.align	2
.LC6:
	.ascii	"\012A false alarm if the count is < %d\012\000"
	.align	2
.LC7:
	.ascii	"Threat detected with level %d and appears %d times\012"
	.ascii	"\000"
	.align	2
.LC8:
	.ascii	"No threat detected\000"
	.align	2
.LC9:
	.ascii	"Goodbye\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 2120
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #2128
	ldr	r3, .L15
	str	r3, [fp, #-112]
	ldr	r3, .L15+4
	str	r3, [fp, #-116]
	ldr	r3, .L15+8
	str	r3, [fp, #-120]
	ldr	r3, .L15+12
	str	r3, [fp, #-124]
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r0, .L15+16
	bl	printf
	ldr	r3, .L15+20
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	sub	r2, fp, #108
	mov	r0, r2
	mov	r1, #100
	mov	r2, r3
	bl	fgets
	sub	r2, fp, #108
	sub	r3, fp, #112
	mov	r0, r2
	ldr	r1, .L15+24
	mov	r2, r3
	bl	sscanf
	b	.L2
.L5:
	ldr	r3, [fp, #-112]
	cmn	r3, #1
	bne	.L3
	ldr	r0, .L15+28
	bl	puts
	mov	r3, #0
	b	.L14
.L3:
	ldr	r3, [fp, #-112]
	ldr	r0, .L15+32
	mov	r1, r3
	bl	printf
	ldr	r0, .L15+16
	bl	printf
	ldr	r3, .L15+20
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	sub	r2, fp, #108
	mov	r0, r2
	mov	r1, #100
	mov	r2, r3
	bl	fgets
	sub	r2, fp, #108
	sub	r3, fp, #112
	mov	r0, r2
	ldr	r1, .L15+24
	mov	r2, r3
	bl	sscanf
.L2:
	ldr	r3, [fp, #-112]
	cmp	r3, #2
	ble	.L5
	ldr	r3, [fp, #-112]
	ldr	r0, .L15+36
	mov	r1, r3
	bl	printf
	ldr	r0, .L15+40
	bl	printf
	ldr	r3, .L15+20
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	sub	r2, fp, #108
	mov	r0, r2
	mov	r1, #100
	mov	r2, r3
	bl	fgets
	sub	r2, fp, #108
	sub	r3, fp, #116
	mov	r0, r2
	ldr	r1, .L15+24
	mov	r2, r3
	bl	sscanf
	b	.L6
.L8:
	ldr	r3, [fp, #-116]
	cmn	r3, #1
	bne	.L7
	ldr	r0, .L15+28
	bl	puts
	mov	r3, #0
	b	.L14
.L7:
	ldr	r3, [fp, #-116]
	ldr	r0, .L15+32
	mov	r1, r3
	bl	printf
	ldr	r0, .L15+40
	bl	printf
	ldr	r3, .L15+20
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	sub	r2, fp, #108
	mov	r0, r2
	mov	r1, #100
	mov	r2, r3
	bl	fgets
	sub	r2, fp, #108
	sub	r3, fp, #116
	mov	r0, r2
	ldr	r1, .L15+24
	mov	r2, r3
	bl	sscanf
.L6:
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	ble	.L8
	ldr	r3, [fp, #-116]
	ldr	r0, .L15+44
	mov	r1, r3
	bl	printf
.L13:
	mov	r3, #0
	str	r3, [fp, #-120]
	mov	r3, #0
	str	r3, [fp, #-124]
	sub	r1, fp, #108
	sub	r2, fp, #120
	sub	ip, fp, #124
	sub	r3, fp, #2112
	sub	r3, r3, #4
	sub	r3, r3, #8
	str	r3, [sp]
	mov	r0, r1
	mov	r1, #100
	mov	r3, ip
	bl	get_SampleSet
	mov	r3, r0
	cmp	r3, #0
	bne	.L9
	b	.L10
.L9:
	ldr	r3, [fp, #-124]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-120]
	cmn	r3, #1
	bne	.L11
	sub	r3, fp, #2112
	sub	r3, r3, #4
	sub	r3, r3, #8
	mov	r0, r3
	ldr	r1, [fp, #-8]
	bl	selection_Sort
	ldr	lr, [fp, #-112]
	ldr	r2, [fp, #-116]
	sub	r3, fp, #2112
	sub	r3, r3, #4
	sub	r3, r3, #8
	sub	ip, fp, #120
	sub	r1, fp, #124
	str	r1, [sp]
	str	r2, [sp, #4]
	mov	r0, r3
	ldr	r1, [fp, #-8]
	mov	r2, lr
	mov	r3, ip
	bl	get_ThreatLevel
	ldr	r2, [fp, #-124]
	ldr	r3, [fp, #-116]
	cmp	r2, r3
	blt	.L12
	ldr	r2, [fp, #-120]
	ldr	r3, [fp, #-112]
	cmp	r2, r3
	blt	.L12
	ldr	r2, [fp, #-120]
	ldr	r3, [fp, #-124]
	ldr	r0, .L15+48
	mov	r1, r2
	mov	r2, r3
	bl	printf
	b	.L11
.L12:
	ldr	r0, .L15+52
	bl	puts
.L11:
	ldr	r3, [fp, #-120]
	cmn	r3, #1
	bge	.L13
.L10:
	ldr	r0, .L15+56
	bl	puts
	mov	r0, #0
	bl	exit
.L14:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, lr}
	bx	lr
.L16:
	.align	2
.L15:
	.word	-12345
	.word	-137153163
	.word	-54321
	.word	-99999
	.word	.LC0
	.word	_impure_ptr
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.size	main, .-main
	.section	.rodata
	.align	2
.LC10:
	.ascii	"\012 The input data is repeated, this is invalid.\000"
	.align	2
.LC11:
	.ascii	"\012 The input data is %s,this is invalid.\012\000"
	.align	2
.LC12:
	.ascii	"\012 get maximum samples.\000"
	.text
	.align	2
	.global	get_SampleSet
	.type	get_SampleSet, %function
get_SampleSet:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	str	r3, [fp, #-28]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L18
.L26:
	ldr	r3, .L27
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	fgets
	ldr	r0, [fp, #-16]
	ldr	r1, .L27+4
	ldr	r2, [fp, #-24]
	bl	sscanf
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #1
	beq	.L19
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L20
	ldr	r0, .L27+8
	bl	puts
.L20:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L21
	ldr	r0, .L27+12
	ldr	r1, [fp, #-16]
	bl	printf
.L21:
	mov	r3, #0
	b	.L22
.L19:
	ldr	r3, [fp, #-28]
	ldr	r3, [r3]
	cmp	r3, #500
	blt	.L23
	ldr	r3, [fp, #-24]
	mvn	r2, #0
	str	r2, [r3]
	ldr	r0, .L27+16
	bl	puts
	b	.L24
.L23:
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	cmp	r3, #0
	bge	.L25
	b	.L24
.L25:
	ldr	r3, [fp, #-28]
	ldr	r3, [r3]
	add	r1, r3, #1
	ldr	r2, [fp, #-28]
	str	r1, [r2]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #4]
	add	r3, r2, r3
	ldr	r2, [fp, #-24]
	ldr	r2, [r2]
	str	r2, [r3]
.L18:
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	cmp	r3, #0
	bge	.L26
.L24:
	mov	r3, #1
.L22:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, lr}
	bx	lr
.L28:
	.align	2
.L27:
	.word	_impure_ptr
	.word	.LC1
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.size	get_SampleSet, .-get_SampleSet
	.align	2
	.global	selection_Sort
	.type	selection_Sort, %function
selection_Sort:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	mov	r3, #0
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L30
.L34:
	ldr	r3, [fp, #-12]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L31
.L33:
	ldr	r3, [fp, #-16]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	bge	.L32
	ldr	r3, [fp, #-8]
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-16]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [fp, #-20]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [fp, #-8]
	str	r2, [r3]
.L32:
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L31:
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	blt	.L33
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L30:
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	blt	.L34
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	selection_Sort, .-selection_Sort
	.align	2
	.global	get_ThreatLevel
	.type	get_ThreatLevel, %function
get_ThreatLevel:
	@ Function supports interworking.
	@ args = 8, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	str	r3, [fp, #-28]
	mov	r3, #1
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-20]
	sub	r3, r3, #1
	str	r3, [fp, #-20]
	b	.L36
.L41:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	ble	.L37
	ldr	r3, [fp, #-20]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-20]
	sub	r3, r3, #-1073741823
	mov	r3, r3, asl #2
	ldr	r1, [fp, #-16]
	add	r3, r1, r3
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L37
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L38
.L37:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #8]
	cmp	r2, r3
	blt	.L39
	ldr	r3, [fp, #4]
	ldr	r2, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-20]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-28]
	str	r2, [r3]
	b	.L35
.L39:
	mov	r3, #1
	str	r3, [fp, #-8]
.L38:
	ldr	r3, [fp, #-20]
	sub	r3, r3, #1
	str	r3, [fp, #-20]
.L36:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	bge	.L41
.L35:
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	get_ThreatLevel, .-get_ThreatLevel
	.ident	"GCC: (15:4.9.3+svn231177-1) 4.9.3 20150529 (prerelease)"
