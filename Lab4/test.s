# setup of f
f:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -8($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -12($sp)
lw $t0, -12($sp)
lw $t0, 0($t0)
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -8($sp)
sw $t0, 0($t1)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -8($sp)
lw $t0, -8($sp)
sw $t0, -12($sp)
# loading intconst
addi $t0, $0, 3
sw $t0, -16($sp)
# assignment
lw $t0, -16($sp)
lw $t1, -12($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
lw $t0, 0($t0)
sw $t0, -8($sp)
# copying to RV
lw $t0, -8($sp)
sw $t0, 12($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of g
g:
sw $ra, 4($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -4($sp)
addi $t0, $sp, 8
lw $t0, 0($t0)
sw $t0, -8($sp)
# Load values onto registers
lw $t0, -4($sp)
lw $t1, -8($sp)
# generate op code
mul $t0, $t0, $t1
# store the value back into memory
sw $t0, -12($sp)
# copying to RV
lw $t0, -12($sp)
sw $t0, 12($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
addi $t0, $sp, -120
sw $t0, -124($sp)
addi $t0, $sp, -4
sw $t0, -128($sp)
sw $t0, -128($sp)
addi $t0, $t0, 0
sw $t0, -132($sp)
sw $t0, -132($sp)
addi $t0, $t0, 0
sw $t0, -136($sp)
lw $t0, -136($sp)
sw $t0, -140($sp)
# assignment
lw $t0, -140($sp)
lw $t1, -124($sp)
sw $t0, 0($t1)
addi $t0, $sp, -120
lw $t0, 0($t0)
sw $t0, -124($sp)
lw $t0, -124($sp)
sw $t0, -128($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -132($sp)
# assignment
lw $t0, -132($sp)
lw $t1, -128($sp)
sw $t0, 0($t1)
addi $t0, $sp, -120
lw $t0, 0($t0)
sw $t0, -124($sp)
lw $t0, -124($sp)
sw $t0, -132($sp)
sw $sp, -140($sp)
addi $sp, $sp, -140
jal f
addi $t0, $sp, -4
sw $t0, -140($sp)
sw $t0, -140($sp)
addi $t0, $t0, 0
sw $t0, -144($sp)
sw $t0, -144($sp)
addi $t0, $t0, 0
lw $t0, 0($t0)
sw $t0, -148($sp)
lw $t0, -148($sp)
sw $t0, -156($sp)
sw $sp, -164($sp)
addi $sp, $sp, -164
jal g
# Load values onto registers
lw $t0, -128($sp)
lw $t1, -152($sp)
# generate op code
add $t0, $t0, $t1
# store the value back into memory
sw $t0, -164($sp)
# copying to RV
lw $t0, -164($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
add $a0, $v0, $0
li $v0, 1
syscall
li $v0, 5
syscall

