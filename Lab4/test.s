# setup of main
main:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -8
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -12
sw $t0, -16($sp)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -20($sp)
addi $t0, $sp, -8
lw $t0, 0($t0)
sw $t0, -24($sp)
# Load values onto registers
lw $t0, -20($sp)
lw $t1, -24($sp)
# generate op code
slt $t0, $t0, $t1
# store the value back into memory
sw $t0, -28($sp)
# assignment
lw $t0, -28($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -12
lw $t0, 0($t0)
sw $t0, -16($sp)
lw $t0, -16($sp)
li $v0, 1
add $a0, $0, $t0
syscall
addi $t0, $sp, -4
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -12
sw $t0, -16($sp)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -20($sp)
lw $t0, -20($sp)
addi $t1, $0, 0
addi $t2, $0, 1
movz $t1, $t2, $t0
sw $t1, -24($sp)
# assignment
lw $t0, -24($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
addi $t0, $sp, -12
lw $t0, 0($t0)
sw $t0, -16($sp)
lw $t0, -16($sp)
li $v0, 1
add $a0, $0, $t0
syscall
# loading intconst
addi $t0, $0, 0
sw $t0, -16($sp)
# copying to RV
lw $t0, -16($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
