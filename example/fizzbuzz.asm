# A FizzBuzz type program
# Writes results to R7
# 1 for "fizz", 2 for "buzz", 3 for "fizzbuzz"

	ldi r0, 200 	#Will loop 200 times, high to low

loop:	ldi r7, 0  
	ldi r4, 0	#Stores fizzbuzz value temporarily in R4
	addi r1, r0, 0
	ldi r2, 3
	ldi r3, 5
	mod r0, r0, r2
	bez fizz
fizz_o:	addi r0, r1, 0
	mod r0, r0, r3 
	bez buzz
buzz_o:	addi r0, r1, 0
	addi r7, r4, 0	#Finally moves the result in R4 to R7
	addi r0, r0, -1
	bgz loop
	end

fizz:	addi r4, r4, 1
	jmp fizz_o

buzz:	addi r4, r4, 2
	jmp buzz_o

