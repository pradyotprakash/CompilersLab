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
sub $t0, $t1, $t0
sw $t0, -12($sp)
# loading intconst
addi $t0, $0, 1
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
sw $t1, -804($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -808($sp)
lw $t0, -808($sp)
addi $t1, $0, 40
mul $t0, $t0, $t1
lw $t1, -804($sp)
sub $t0, $t1, $t0
sw $t0, -812($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -816($sp)
lw $t0, -816($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -812($sp)
sub $t0, $t1, $t0
sw $t0, -820($sp)
# loading intconst
addi $t0, $0, 4
sw $t0, -824($sp)
# assignment
lw $t0, -824($sp)
lw $t1, -820($sp)
sw $t0, 0($t1)
sw $t0, -828($sp)
li $v0, 4
la $a0, S_0
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -4
sw $t1, -804($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -808($sp)
lw $t0, -808($sp)
addi $t1, $0, 40
mul $t0, $t0, $t1
lw $t1, -804($sp)
sub $t0, $t1, $t0
sw $t0, -812($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -816($sp)
lw $t0, -816($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -812($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -820($sp)
lw $t0, -820($sp)
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
sw $t1, -804($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -808($sp)
lw $t0, -808($sp)
addi $t1, $0, 40
mul $t0, $t0, $t1
lw $t1, -804($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -812($sp)
lw $t0, -812($sp)
sw $t0, -816($sp)
sw $sp, -824($sp)
addi $sp, $sp, -824
jal F_f
li $v0, 4
la $a0, S_1
syscall
li $v0 4
la $a0, space
syscall
addi $t1, $sp, -4
sw $t1, -804($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -808($sp)
lw $t0, -808($sp)
addi $t1, $0, 40
mul $t0, $t0, $t1
lw $t1, -804($sp)
sub $t0, $t1, $t0
sw $t0, -812($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -816($sp)
lw $t0, -816($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -812($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -820($sp)
lw $t0, -820($sp)
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
S_1: .asciiz "d"
newl: .asciiz "\n"
space: .asciiz " "
