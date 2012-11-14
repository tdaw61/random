addi $t0, $zero, 1
addi $t1, $zero, 2
slt $t2, $t0, $t1
sub $t3, $t1, $t0
add $t0, $t1, $t1
j label
slti $t4, $t2, 1
add $t6, $t5, $zero
label: sw $t4, 0($a0) 
lw $t5, 0($a0)
