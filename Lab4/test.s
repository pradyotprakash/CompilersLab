.data
space: .asciiz "\n"
.text
# setup of g
F_g:
sw $ra, 4($sp)
addi $t1, $sp, -4
sw $t1, -8($sp)
lw $t0, -8($sp)
addi $t0, $t0, 0
sw $t0, -12($sp)
addi $t1, $sp, 8
lw $t1, 0($t1)
sw $t1, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
sw $t0, -20($sp)
addi $t1, $sp, -4
addi $t0, $sp, -8
lw $t2 0($t1)
sw $t2 0($t0)
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
sw $t1, -8($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -12($sp)
addi $t0, $sp, -20
addi $t1, $sp, -12
lw $t2 0($t1)
sw $t2 0($t0)
sw $sp, -28($sp)
addi $sp, $sp, -28
jal F_g
addi $t1, $sp, -16
lw $t0, -8($sp)
lw $t2 0($t1)
sw $t2 0($t0)
addi $t0, $sp, -28
lw $t2 0($t1)
sw $t2 0($t0)
addi $t1, $sp, -4
addi $t0, $sp, -8
lw $t2 0($t1)
sw $t2 0($t0)
lw $t0, -8($sp)
sw $t0, -12($sp)
lw $t0, -12($sp)
li $v0, 1
add $a0, $0, $t0
syscall
addi $v0, $0, 4
la $a0, space
syscall
# loading intconst
addi $t0, $0, 0
sw $t0, -8($sp)
# copying to RV
addi $t0, $sp, 8
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
