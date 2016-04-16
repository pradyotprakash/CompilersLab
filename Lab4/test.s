# setup of f
f:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -8($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -12($sp)
lw $t0, -12($sp)
lw $t0, 0($t0)
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -8($sp)
sw $t0, 0($t1)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -8($sp)
lw $t0, -8($sp)
sw $t0, -12($sp)
# loading intconst
addi $t0, $0, 3
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -8($sp)
# copying to RV
lw $t0, -8($sp)
sw $t0, 12($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of g
g:
sw $ra, 4($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -4($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -8($sp)
# Load values onto registers
lw $t0, -4($sp)
lw $t1, -8($sp)
# generate op code
mul $t0, $t0, $t1
# store the value back into memory
sw $t0, -12($sp)
# copying to RV
lw $t0, -12($sp)
sw $t0, 12($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -12($sp)
addi $t0, $sp, -8
sw $t0, -16($sp)
lw $t0, -16($sp)
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -12($sp)
lw $t0, -12($sp)
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -12($sp)
lw $t0, -12($sp)
sw $t0, -20($sp)
sw $sp, -28($sp)
addi $sp, $sp, -28
jal f
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -28($sp)
lw $t0, -28($sp)
lw $t0, 0($t0)
sw $t0, -32($sp)
lw $t0, -32($sp)
sw $t0, -40($sp)
sw $sp, -48($sp)
addi $sp, $sp, -48
jal g
# Load values onto registers
lw $t0, -16($sp)
lw $t1, -36($sp)
# generate op code
add $t0, $t0, $t1
# store the value back into memory
sw $t0, -48($sp)
# copying to RV
lw $t0, -48($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
add $a0, $v0, $0
li $v0, 1
syscall
li $v0, 5
syscall

