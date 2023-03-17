.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

main:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 20000
	subu $s0, $fp, 8
	sw $s0, -8($fp)
	li $t0, 1
	sw $t0, -12($fp)
	lw $t2, -12($fp)
	li $s1, 4
	mul $t1, $t2, $s1
	sw $t1, -16($fp)
	lw $t4, -8($fp)
	lw $t5, -16($fp)
	la $s0, -8($fp)
	add $t3, $s0, $t5
	sw $t3, -20($fp)
	li $t6, 13
	sw $t6, -24($fp)
	lw $t7, -20($fp)
	lw $t0, -24($fp)
	sw $t0, 0($t7)
	sw $t7, -20($fp)
	li $t1, 1
	sw $t1, -28($fp)
	lw $t3, -28($fp)
	li $s1, 4
	mul $t2, $t3, $s1
	sw $t2, -32($fp)
	lw $t5, -8($fp)
	lw $t6, -32($fp)
	la $s0, -8($fp)
	add $t4, $s0, $t6
	sw $t4, -36($fp)
	lw $t0, -36($fp)
	lw $t7, 0($t0)
	sw $t7, -40($fp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)
	lw $t1, -40($fp)
	move $a0, $t1
	jal write
	sw $t1, -40($fp)
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	li $t2, 0
	sw $t2, -44($fp)
	lw $t3, -44($fp)
	move $v0, $t3
	addi $sp, $sp, 20000
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra
