# a3k

![http://i.imgur.com/0sgpHr7.png](http://i.imgur.com/0sgpHr7.png)

a3k is a mini 16 bit virtual machine that runs a small main memory-less assembly
language. Mostly useless and made just for fun. 

It features two programs:

**kasm**: Command line program to assemble a text source file to binary.
**a3k**: Graphical Qt frontend to run the binary. Pictured above.

## Instruction Set

There are 15 instructions in the a3k ISA. You can preface a line with a label
for jump and branch instructions, and use `#` for comments.

There are 8 accessible registers, with a 9th inaccessible register used to store
return values for subroutine jumps. Registers are called in the for `R0`, `R1`,
etc.

Everything is case insensitive.

For an example, see the [example file](example/fb.asm).

### ADD

Description: Takes the sum of the source registers. Result into r[dest].

Format: `add r[dest], r[src1], r[src2]`

```
|------3'x----|---3'dest---|---3'src1---|---3'src2---|---0001---|
```

### ADDI

Description: Takes the sum of the source register and signed immediate.

Format: `addi r[dest], r[src1], imm`

```
|------------6'imm---------|---3'src1---|---3'src2---|---0010---|
```

### AND

Description: Takes the bitwise and of the source registers.

Format: `and r[dest], r[src1], r[src2]`

```
|------3'x----|---3'dest---|---3'src1---|---3'src2---|---0011---|
```

### INV

Description: Takes the inverse of the source register. Returns it to the
same register.

Format:	`inv r[src1]`

```
|-------------------9'x-----------------|---3'src1---|---0100---|
```

### MULT

Descrption: Takes the product of the source registers.

Format: `mult r[dest], r[src1], r[src2]`

```
|------3'x----|---3'dest---|---3'src1---|---3'src2---|---0101---|
```

### DIV

Description: Takes the quotient of the source registers. ***src1 / src 2***

Format: `div r[dest], r[src1], r[src2]`

```
|------3'x----|---3'dest---|---3'src1---|---3'src2---|---0110---|
```

### MOD

Description: Takes the modulus of the two source registers.

Format: `mod r[dest], r[src1], r[src2]`

```
|------3'x----|---3'dest---|---3'src1---|---3'src2---|---0111---|
```

### LDI

Description: Loads r[dest] with the signed immeditate value.

Format: `ldi r[dest], imm`

```
|------------------9'imm----------------|---3'dest---|---0011---|
```

### BLZ

Description: Jumps to the instruction specified by ***label*** if the value
in R0 is less than zero.

Format: `blz label`

```
|------------------------12'offset-------------------|---1001---|
```

### BEZ

Description: Jumps to the instruction specified by ***label*** if the value
in R0 is equal to zero.

Format: `bez label`

```
|------------------------12'offset-------------------|---1010---|
```

### BGZ

Description: Jumps to the instruction specified by ***label*** if the value
in R0 is greater than zero.

Format: `bgz label`

```
|------------------------12'offset-------------------|---1011---|
```

### JMP

Description: Unconditional jump to instruction specified by ***label***.

Format: `jmp label`

```
|------------------------12'offset-------------------|---1100---|
```

### JSR

Description: Unconditional jump to instruction specified by ***label***.
Stores the next address before jump into R8, which can be reloaded with RET.

Format: `jsr label`

```
|------------------------12'offset-------------------|---1101---|
```

### RET

Description: Loads the return address from R8 and does an unconditional jump.
To be used after JSR.

Format: `ret`

```
|---------------------------12'x---------------------|---1110---|
```

### END

Description: Specifies the end of the program.

Format: `end`

```
|---------------------------12'x---------------------|---1111---|
```