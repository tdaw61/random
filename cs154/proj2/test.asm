addi	$s0, $0, 254
addi	$s1, $0, 1
addi	$s2, $0, 255
addi	$s3, $0, 255
addi	$s4, $0, 255
addi	$s5, $0, 255
add	$s6, $s0, $s1 
sw	$s6, 0($0)
lw	$s7, 0($0)
addi	$s7, $0, 0
addi	$s0, $0, 1
addi	$s1, $s0, 1
addi	$s2, $s0, 2
addi	$s3, $s0, 3
addi	$s0, $s0, 1
addi    $s0, $s0, 1
addi    $s0, $s0, 1
addi    $s0, $s0, 1
addi    $s0, $s0, 1
addi	$s0, $0, 5
addi    $s0, $0, 254
addi    $s1, $0, 1
jal	label2
addi    $s2, $0, 255
addi    $s3, $0, 200
addi    $s4, $0, 200
addi    $s5, $0, 200
label2:addi	$s0, $0, 100
jr	$31
