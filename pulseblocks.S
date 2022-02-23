
.macro    PUSH reg
  addi    $sp,$sp,-4
  sw    \reg,0($sp)
.endm

.macro    POP reg
  lw    \reg,0($sp)
  addi    $sp,$sp,4
.endm



.data

.global enable_interrupt

.text

# enable_interrupt i camelCase?

enable_interrupt:
	ei	
		
	jr	$ra
	nop
