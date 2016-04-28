.text
# setup of main
main:
sw $ra, 4($sp)
addi $t1, $sp, -4
sw $t1, -16($sp)
addi $t1, $sp, -8
sw $t1, -20($sp)
lw $t0, -20($sp)
sw $t0, -24($sp)
# assignment
lw $t0, -24($sp)
lw $t1, -16($sp)
sw $t0, 0($t1)
sw $t0, -28($sp)
addi $t1, $sp, -8
sw $t1, -16($sp)
lw $t0, -16($sp)
addi $t0, $t0, 0
sw $t0, -20($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -24($sp)
# assignment
lw $t0, -24($sp)
lw $t1, -20($sp)
sw $t0, 0($t1)
sw $t0, -28($sp)
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -16($sp)
lw $t0, -16($sp)
addi $t0, $t0, -4
sw $t0, -20($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -24($sp)
# assignment
lw $t0, -24($sp)
lw $t1, -20($sp)
sw $t0, 0($t1)
sw $t0, -28($sp)
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -16($sp)
addi $t0, $sp, -20
lw $t1, -16($sp)
addi $t1, $t1, 0
lw $t2 0($t1)
sw $t2 0($t0)
lw $t0, -20($sp)
li $v0, 1
add $a0, $0, $t0
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -8
addi $t0, $sp, -24
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 -4($t1)
sw $t2 -4($t0)
addi $t0, $sp, -32
addi $t1, $sp, -28
lw $t2 0($t1)
sw $t2 0($t0)
lw $t0, -32($sp)
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
