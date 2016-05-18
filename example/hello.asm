# Hello World!
# This is a really convoluted way of doing it.

	.data cursor 0xfa0 # Start of video memory space
	.array hello 13

start:	ldi r0, hello # Populate the string array
	ldi r1, 0x48 # 'H'
	jsr fill
	ldi r1, 0x65 # 'e'
	jsr fill
	ldi r1, 0x6c # 'l'
	jsr fill
	jsr fill
	ldi r1, 0x6f # 'o'
	jsr fill
	ldi r1, 0x20 # ' '
	jsr fill
	ldi r1, 0x57 # 'W'
	jsr fill
	ldi r1, 0x6f # 'o'
	jsr fill
	ldi r1, 0x72 # 'r'
	jsr fill
	ldi r1, 0x6c # 'l'
	jsr fill
	ldi r1, 0x64 # 'd'
	jsr fill
	ldi r1, 0x21 # '!'
	jsr fill
	ldi r1, 0    # '\0'
	jsr fill

	ldi r0, hello
	jsr write
	end

fill:	str r1, r0		# r0 contains address
	addi r0, r0, 1		# r1 contains data
	ret

write:	addi r21, r0, 0		# r0: string array index -> r21
wloop:	ld r20, cursor		# r20: position in video memory
	ldr r0, r21
	bez wend
	str r0, r20
	addi r20, r20, 1
	addi r21, r21, 1
	st r20, cursor
	j wloop
wend: 	ret
	