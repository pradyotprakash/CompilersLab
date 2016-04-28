.data
space: .asciiz "\n"
.text
# setup of f
F_f:
sw $ra, 4($sp)
addi $t1, $sp, 8
sw $t1, -4($sp)
lw $t0, -4($sp)
lw $t1, 0($t0)
addi $t2, $t1, 1
sw $t2, 0($t0)
sw $t1, -8($sp)
# copying to RV
addi $t0, $sp, 12
addi $t1, $sp, -8
lw $t2 0($t1)
sw $t2 0($t0)
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
addi $t1, $sp, -4
sw $t1, -12($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
sw $t0, -20($sp)
addi $t1, $sp, -8
sw $t1, -12($sp)
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -16($sp)
addi $t0, $sp, -24
addi $t1, $sp, -16
lw $t2 0($t1)
sw $t2 0($t0)
sw $sp, -32($sp)
addi $sp, $sp, -32
jal F_f
# assignment
lw $t0, -20($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
sw $t0, -32($sp)
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -12($sp)
l.s $f12, -12($sp)
li $v0, 2
syscall
addi $v0, $0, 4
la $a0, space
syscall
# loading intconst
addi $t0, $0, 0
sw $t0, -12($sp)
# copying to RV
addi $t0, $sp, 8
addi $t1, $sp, -12
lw $t2 0($t1)
sw $t2 0($t0)
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
