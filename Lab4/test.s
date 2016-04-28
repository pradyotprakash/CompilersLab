.text
# setup of f
F_f:
sw $ra, 4($sp)
addi $t1, $sp, 8
lw $t1, 0($t1)
sw $t1, -4($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -8($sp)
lw $t0, -8($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -4($sp)
sub $t1, $t1, $t0
sw $t1, -12($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
sw $t0, -20($sp)
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
addi $t1, $sp, -4
sw $t1, -1604($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -1608($sp)
lw $t0, -1608($sp)
addi $t1, $0, 80
mul $t0, $t0, $t1
lw $t1, -1604($sp)
sub $t1, $t1, $t0
sw $t1, -1612($sp)
lw $t0, -1612($sp)
sw $t0, -1616($sp)
sw $sp, -1624($sp)
addi $sp, $sp, -1624
jal F_f
li $v0, 4
la $a0, S_0
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -4
sw $t1, -1604($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -1608($sp)
lw $t0, -1608($sp)
addi $t1, $0, 80
mul $t0, $t0, $t1
lw $t1, -1604($sp)
sub $t1, $t1, $t0
sw $t1, -1612($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -1616($sp)
lw $t0, -1616($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -1612($sp)
sub $t1, $t1, $t0
addi $t0, $sp, -1620
lw $t2 0($t1)
sw $t2 0($t0)
lw $t0, -1620($sp)
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
S_0: .asciiz "d"
newl: .asciiz "\n"
space: .asciiz " "
