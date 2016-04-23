# setup of main
main:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -8($sp)
# loading intconst
addi $t0, $0, 0
sw $t0, -12($sp)
# assignment
lw $t0, -12($sp)
lw $t1, -8($sp)
sw $t0, 0($t1)
LABEL0:
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -20($sp)
# Load values onto registers
lw $t0, -16($sp)
lw $t1, -20($sp)
# generate op code
slt $t0, $t0, $t1
# store the value back into memory
sw $t0, -24($sp)
lw $t0, -24($sp)
beq $t0, $0, LABEL1
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -32($sp)
lw $t0, -32($sp)
li $v0, 1
add $a0, $0, $t0
syscall
addi $t0, $sp, -4
sw $t0, -32($sp)
lw $t0, -32($sp)
lw $t1, 0($t0)
addi $t2, $t1, 1
sw $t2, 0($t0)
sw $t1, -36($sp)
j LABEL0
LABEL1:
# loading intconst
addi $t0, $0, 0
sw $t0, -8($sp)
# copying to RV
lw $t0, -8($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
