.text
# setup of f
F_f:
sw $ra, 4($sp)
addi $t1, $sp, 8
lw $t1, 0($t1)
sw $t1, -4($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -8($sp)
# Load values onto registers
lw $t0, -4($sp)
lw $t1, -8($sp)
# generate op code
add $t0, $t0, $t1
# store the value back into memory
sw $t0, -12($sp)
# copying to RV
# rlocation here 12
addi $t0, $sp, 12
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
