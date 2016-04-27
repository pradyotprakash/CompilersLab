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
addi $t1, $sp, 8
lw $t1, 0($t1)
sw $t1, -4($sp)
lw $t0, -4($sp)
li $v0, 1
add $a0, $0, $t0
syscall
addi $v0, $0, 4
la $a0, space
syscall
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
li.s $f0, 1.3
s.s $f0, -4($sp)
l.s $f0, -4($sp)
cvt.w.s $f0, $f0
mfc1 $t0, $f0
sw $t0, -8($sp)
sw $sp, -16($sp)
addi $sp, $sp, -16
jal F_f
# loading intconst
addi $t0, $0, 0
sw $t0, -4($sp)
# copying to RV
lw $t0, -4($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
