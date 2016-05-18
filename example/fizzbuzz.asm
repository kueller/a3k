# A FizzBuzz type program
# Writes results to R7
# Prints fizz/buzz now.
# Still messy leftovers from when it was only numerical.

	ldi r0, 100 	#Will loop 100 times, high to low

loop:	ldi r21, 0xfa0
	ldi r7, 0  
	ldi r4, 0	#Stores fizzbuzz value temporarily in R4
	addi r1, r0, 0
	ldi r2, 3
	ldi r3, 5
	mod r0, r0, r2
	bez fizz
fcheck:	addi r0, r1, 0
	mod r0, r0, r3 
	bez buzz
bcheck:	addi r0, r1, 0
	addi r7, r4, 0	#Finally moves the result in R4 to R7
	addi r0, r0, -1
	jsr clear
	bgz loop
	end

fizz:	ldi r20, 0x66
	str r20, r21
	addi r21, r21, 1
	ldi r20, 0x69
	str r20, r21
	addi r21, r21, 1
	ldi r20, 0x7a
	str r20, r21
	addi r21, r21, 1
	str r20, r21
	addi r21, r21, 1
	j fcheck

buzz:	ldi r20, 0x62
	str r20, r21
	addi r21, r21, 1
	ldi r20, 0x75
	str r20, r21
	addi r21, r21, 1
	ldi r20, 0x7a
	str r20, r21
	addi r21, r21, 1
	str r20, r21
	addi r21, r21, 1	
	j bcheck

clear:	ldi r21, 0xfa0
	ldi r20, 0x20
	addi r25, r0, 0
	ld r0, 0xfa0		# Check if is already cleared
	subi r0, r0, 0x20
	bez cskip
	ldi r0, 8
cloop:	str r20, r21
	subi r0, r0, 1
	addi r21, r21, 1
	bgz cloop
cskip:	addi, r0, r25, 0
	ret

