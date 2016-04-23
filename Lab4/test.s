.data
space: .asciiz "\n"
.text
# setup of main
main:
sw $ra, 4($sp)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 0
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 7
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 3
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 4
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 7
sw $t0, -68($sp)
lw $t0, -68($sp)
sub $t0, $0, $t0
sw $t0, -72($sp)
# assignment
lw $t0, -72($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 5
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 0
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 6
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 12
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 7
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 9
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 8
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 2
sw $t0, -68($sp)
# assignment
lw $t0, -68($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 9
sw $t0, -60($sp)
lw $t0, -60($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -56($sp)
sub $t0, $t1, $t0
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 3
sw $t0, -68($sp)
lw $t0, -68($sp)
sub $t0, $0, $t0
sw $t0, -72($sp)
# assignment
lw $t0, -72($sp)
lw $t1, -64($sp)
sw $t0, 0($t1)
addi $t0, $sp, -44
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 0
sw $t0, -60($sp)
# assignment
lw $t0, -60($sp)
lw $t1, -56($sp)
sw $t0, 0($t1)
LABEL0:
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -68($sp)
# Load values onto registers
lw $t0, -64($sp)
lw $t1, -68($sp)
# generate op code
slt $t0, $t0, $t1
# store the value back into memory
sw $t0, -72($sp)
lw $t0, -72($sp)
beq $t0, $0, LABEL1
addi $t0, $sp, -48
sw $t0, -80($sp)
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -84($sp)
# loading intconst
addi $t0, $0, 1
sw $t0, -88($sp)
# Load values onto registers
lw $t0, -84($sp)
lw $t1, -88($sp)
# generate op code
add $t0, $t0, $t1
# store the value back into memory
sw $t0, -92($sp)
# assignment
lw $t0, -92($sp)
lw $t1, -80($sp)
sw $t0, 0($t1)
LABEL2:
addi $t0, $sp, -48
lw $t0, 0($t0)
sw $t0, -96($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -100($sp)
# Load values onto registers
lw $t0, -96($sp)
lw $t1, -100($sp)
# generate op code
slt $t0, $t0, $t1
# store the value back into memory
sw $t0, -104($sp)
lw $t0, -104($sp)
beq $t0, $0, LABEL3
addi $t0, $sp, -4
sw $t0, -112($sp)
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -116($sp)
lw $t0, -116($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -112($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -120($sp)
addi $t0, $sp, -4
sw $t0, -124($sp)
addi $t0, $sp, -48
lw $t0, 0($t0)
sw $t0, -128($sp)
lw $t0, -128($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -124($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -132($sp)
# Load values onto registers
lw $t0, -120($sp)
lw $t1, -132($sp)
# generate op code
slt $t0, $t1, $t0
# store the value back into memory
sw $t0, -136($sp)
lw $t0, -136($sp)
beq $t0, $0, LABEL4
addi $t0, $sp, -52
sw $t0, -144($sp)
addi $t0, $sp, -4
sw $t0, -148($sp)
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -152($sp)
lw $t0, -152($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -148($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -156($sp)
# assignment
lw $t0, -156($sp)
lw $t1, -144($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -144($sp)
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -148($sp)
lw $t0, -148($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -144($sp)
sub $t0, $t1, $t0
sw $t0, -152($sp)
addi $t0, $sp, -4
sw $t0, -156($sp)
addi $t0, $sp, -48
lw $t0, 0($t0)
sw $t0, -160($sp)
lw $t0, -160($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -156($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -164($sp)
# assignment
lw $t0, -164($sp)
lw $t1, -152($sp)
sw $t0, 0($t1)
addi $t0, $sp, -4
sw $t0, -144($sp)
addi $t0, $sp, -48
lw $t0, 0($t0)
sw $t0, -148($sp)
lw $t0, -148($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -144($sp)
sub $t0, $t1, $t0
sw $t0, -152($sp)
addi $t0, $sp, -52
lw $t0, 0($t0)
sw $t0, -156($sp)
# assignment
lw $t0, -156($sp)
lw $t1, -152($sp)
sw $t0, 0($t1)
j LABEL5
LABEL4:
LABEL5:
addi $t0, $sp, -48
sw $t0, -112($sp)
lw $t0, -112($sp)
lw $t1, 0($t0)
addi $t2, $t1, 1
sw $t2, 0($t0)
sw $t1, -116($sp)
j LABEL2
LABEL3:
addi $t0, $sp, -44
sw $t0, -80($sp)
lw $t0, -80($sp)
lw $t1, 0($t0)
addi $t2, $t1, 1
sw $t2, 0($t0)
sw $t1, -84($sp)
j LABEL0
LABEL1:
addi $t0, $sp, -44
sw $t0, -56($sp)
# loading intconst
addi $t0, $0, 0
sw $t0, -60($sp)
# assignment
lw $t0, -60($sp)
lw $t1, -56($sp)
sw $t0, 0($t1)
LABEL6:
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -64($sp)
# loading intconst
addi $t0, $0, 10
sw $t0, -68($sp)
# Load values onto registers
lw $t0, -64($sp)
lw $t1, -68($sp)
# generate op code
slt $t0, $t0, $t1
# store the value back into memory
sw $t0, -72($sp)
lw $t0, -72($sp)
beq $t0, $0, LABEL7
addi $t0, $sp, -4
sw $t0, -80($sp)
addi $t0, $sp, -44
lw $t0, 0($t0)
sw $t0, -84($sp)
lw $t0, -84($sp)
addi $t1, $0, 4
mul $t0, $t0, $t1
lw $t1, -80($sp)
sub $t0, $t1, $t0
lw $t0, 0($t0)
sw $t0, -88($sp)
lw $t0, -88($sp)
li $v0, 1
add $a0, $0, $t0
syscall
addi $v0, $0, 4
la $a0, space
syscall
addi $t0, $sp, -44
sw $t0, -80($sp)
lw $t0, -80($sp)
lw $t1, 0($t0)
addi $t2, $t1, 1
sw $t2, 0($t0)
sw $t1, -84($sp)
j LABEL6
LABEL7:
# loading intconst
addi $t0, $0, 0
sw $t0, -56($sp)
# copying to RV
lw $t0, -56($sp)
sw $t0, 8($sp)
add $v0, $t0, $0
# returning
lw $ra, 4($sp)
lw $sp, 0($sp)
jr $ra
