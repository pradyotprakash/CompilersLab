.text
# setup of f
F_f:
sw $ra, 4($sp)
li.s $f0, 3.3
s.s $f0, -4($sp)
# copying to RV
l.s $f0, -4($sp)
cvt.w.s $f0, $f0
mfc1 $t0, $f0
sw $t0, 8($sp)
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
sw $t1, -20($sp)
addi $t1, $sp, -8
sw $t1, -24($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -28($sp)
# assignment
lw $t0, -28($sp)
lw $t1, -24($sp)
sw $t0, 0($t1)
sw $t0, -32($sp)
# assignment
lw $t0, -32($sp)
lw $t1, -20($sp)
sw $t0, 0($t1)
sw $t0, -36($sp)
addi $t1, $sp, -12
sw $t1, -20($sp)
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -24($sp)
li.s $f0, 2.5
s.s $f0, -28($sp)
lw $t0, -24($sp)
mtc1 $t0, $f0
cvt.s.w $f0, $f0
l.s $f1, -28($sp)
mul.s $f0, $f0, $f1
s.s $f0, -32($sp)
l.s $f0, -32($sp)
lw $t1, -20($sp)
s.s $f0, 0($t1)
s.s $f0, -36($sp)
li $v0, 4
la $a0, S_0
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -4
lw $t1, 0($t1)
sw $t1, -20($sp)
lw $t0, -20($sp)
li $v0, 1
add $a0, $0, $t0
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -12
lw $t1, 0($t1)
sw $t1, -24($sp)
l.s $f12, -24($sp)
li $v0, 2
syscall
li $v0 4
la $a0, space
syscall
li $v0, 4
la $a0, S_1
syscall
li $v0 4
la $a0, space
syscall
addi $v0, $0, 4
la $a0, newl
syscall
sw $sp, -28($sp)
addi $sp, $sp, -28
jal F_f
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
# loading intconst
addi $t0, $0, 0
sw $t0, -20($sp)
# copying to RV
addi $t0, $sp, 8
addi $t1, $sp, -20
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
.data
S_0: .asciiz "Output:"
S_1: .asciiz "p"
newl: .asciiz "\n"
space: .asciiz " "
