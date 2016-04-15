# setup of x
x:
sw $ra, 4($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -4($sp)
# copying to RV
lw $t0, -4($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
# setup of main
main:
sw $ra, 4($sp)
sw $sp, -8($sp)
jal x
# loading intconst
addi $t0, $0, 1
sw $t0, -16($sp)
# Load values onto registers
lw $t0, -4($sp)
lw $t1, -16($sp)
# generate op code
add $t0, $t0, $t1
# store the value back into memory
sw $t0, -20($sp)
# copying to RV
lw $t0, -20($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
Global symbol table:
--------------------
Format: name returnType arguments
Function () (   )
Function (main) (int   )
Function (x) (int   )
struct s
struct t



Other symbol tables:
--------------------
function main symbol table:




function x symbol table:




struct s symbol table:

(b) (int   ) offset: (-104) size: (4) 
(a) (int  [5][5] ) offset: (-4) size: (100) 
(c) (int   ) offset: (0) size: (4) 



struct t symbol table:

(b) (int   ) offset: (-4) size: (4) 
(a) (int   ) offset: (0) size: (4) 



