.text
# setup of f
F_f:
sw $ra, 4($sp)
addi $t1, $sp, -4
sw $t1, -12($sp)
lw $t0, -12($sp)
addi $t0, $t0, 0
sw $t0, -16($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -20($sp)
# assignment
lw $t0, -20($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
sw $t0, -24($sp)
addi $t1, $sp, -4
addi $t0, $sp, -12
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
lw $t0, -12($sp)
sw $t0, -20($sp)
lw $t0, -20($sp)
li $v0, 1
add $a0, $0, $t0
syscall
li $v0 4
la $a0, space
syscall
addi $v0, $0, 4
la $a0, newl
syscall
addi $t1, $sp, -4
addi $t0, $sp, -12
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
# copying to RV
# rlocation here 12
addi $t0, $sp, 12
addi $t1, $sp, -12
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
addi $t1, $sp, -12
sw $t1, -20($sp)
lw $t0, -20($sp)
addi $t0, $t0, 0
sw $t0, -24($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -28($sp)
# assignment
lw $t0, -28($sp)
lw $t1, -24($sp)
sw $t0, 0($t1)
sw $t0, -32($sp)
addi $t1, $sp, -12
sw $t1, -20($sp)
lw $t0, -20($sp)
addi $t0, $t0, 0
sw $t0, -24($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -28($sp)
# assignment
lw $t0, -28($sp)
lw $t1, -24($sp)
sw $t0, 0($t1)
sw $t0, -32($sp)
addi $t1, $sp, -4
sw $t1, -20($sp)
sw $sp, -36($sp)
addi $sp, $sp, -36
jal F_f
addi $t1, $sp, -24
lw $t0, -20($sp)
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
addi $t0, $sp, -36
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
addi $t1, $sp, -12
addi $t0, $sp, -20
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
lw $t0, -20($sp)
sw $t0, -28($sp)
lw $t0, -28($sp)
li $v0, 1
add $a0, $0, $t0
syscall
li $v0 4
la $a0, space
syscall
addi $v0, $0, 4
la $a0, newl
syscall
addi $t1, $sp, -4
addi $t0, $sp, -20
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
lw $t0, -20($sp)
sw $t0, -28($sp)
lw $t0, -28($sp)
li $v0, 1
add $a0, $0, $t0
syscall
li $v0 4
la $a0, space
syscall
addi $v0, $0, 4
la $a0, newl
syscall
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
.data
newl: .asciiz "\n"
space: .asciiz " "
