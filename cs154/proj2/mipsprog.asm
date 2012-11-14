addi $t0, $zero, 1
jal l5:
addi $t1, $zero, 2
addi $t2, $zero, 3
addi $t3, $zero, 4
l5: addi $t4, $zero, 5
addi $t1, $t1, 1
bne $t2, $t1, l4
jr $31
l4: addi $t5, $zero, 6
addi $t6, $zero, 7
addi $t5, $t5, 1
bne $t6, $t5, l1
bne $t0, $t1, l2
add $t0, $t0, $t1
add $t2, $t0, $t6
add $t0, $t0, $t3
l1: add $t0, $t0, $t4
sw $t6, 0($t1)
lw $t5, 0($t1)
l2:add $t0, $t5, $t6
add $t0, $t0, $zero
lw $t2, 0($t1)
sw $t0, 0($t1)
j l3
add $t6, $zero, $zero
lw $t3, 0($t1)
l3: add $t3, $t3, $zero
