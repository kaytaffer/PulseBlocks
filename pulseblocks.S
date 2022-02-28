
.macro    PUSH reg
  addi    $sp,$sp,-4
  sw    \reg,0($sp)
.endm

.macro    POP reg
  lw    \reg,0($sp)
  addi    $sp,$sp,4
.endm



.data

.global enableInterrupt
.global delay

.text

 delay: # helper function, creates delay by occupying processor for a while. Accepts milliseconds as 
        # argument. Returns nothing.
        # start of while loop
        blez    $a0, returnx            # branch if a0 is less than 0
        nop
        addi    $a0,$a0,-1              # ms = ms - 1;
        add     $t0,$0,$0               # i is t0 , set to 0
    forx:   slti    $t1,$t0,0x0EFA          # if t0 < constant, set t1 to 1
            beq     $t1,$0,delay            # if t1 is 0, exit for-loop
            nop                             # do nothing
            addiu   $t0,$t0,1               # increment "i" (t0)
            j       forx                    # go to next iteration of for-loop
            nop
    returnx: jr      $ra
            nop


#enables interrupts from timers and other I/O
enableInterrupt:
	ei	
		
	jr	$ra
	nop
