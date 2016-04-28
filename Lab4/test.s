.text
# setup of f
F_f:
sw $ra, 4($sp)
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
lw $t0, 0($t0)
sw $t0, -812($sp)
lw $t0, -812($sp)
sw $t0, -816($sp)
sw $sp, -824($sp)
addi $sp, $sp, -824
jal F_f
# default return statement
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
.data
newl: .asciiz "\n"
space: .asciiz " "
