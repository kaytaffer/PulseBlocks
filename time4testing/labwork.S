# labwork.S
# Written 2015-2017 by F Lundevall
# Skeleton file for IS1200/IS1500 lab 1.
# The macros PUSH and POP are in the public domain.
# Please add your own code at the end of the file.

#
# Please keep the two macros PUSH and POP unchanged
#
.macro    PUSH reg
  addi    $sp,$sp,-4
  sw    \reg,0($sp)
.endm

.macro    POP reg
  lw    \reg,0($sp)
  addi    $sp,$sp,4
.endm
#
# Please add your own code below this line
#



.data

.global delay
.global time2string

.text


hexasc: addi    $t0,$a0,0x30            # Converts for ASCII table, enough for values 0-9
        slti    $t1,$t0,0x3a            # t1 0 if t0 greater than 3a (for input values > 0x9)
        bne     $t1,$0,onlyDec          # skip next code if 0-9
        nop                             # delay slot filler (jic)
        addi    $t0,$t0,0x7             # converts for ASCII table A-F (separated by @-char in ASCII)
onlyDec:move    $v0,$t0                 # return value
        jr      $ra                     # jump back to main
        nop
  
delay:  # start of while loop
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

time2string:#a0 adress to area in memory suitably large
            #a1 timeinfo in 16 lsb, 16 msb to be ignored
        PUSH    $ra
        sra     $t3,$a1,12              # first digit of minute
        andi    $t3,$t3,0x000F
        PUSH    $a0
        move    $a0,$t3
        jal     hexasc
        nop
        POP     $a0
  
        sb      $v0,0($a0)
  
        sra     $t3,$a1,8               # second digit of minute
        andi    $t3,$t3,0x000F
        PUSH    $a0
        move    $a0,$t3
        jal     hexasc
        nop
        POP     $a0
  
        sb      $v0,1($a0)
  
        addi    $t3,$0,0x3a             # :
  
        sb      $t3,2($a0)
  
        sra     $t3,$a1,4               # first digit of second
        andi    $t3,$t3,0x000F
        PUSH    $a0
        move    $a0,$t3
        jal     hexasc
        nop
        POP     $a0
        sb      $v0,3($a0)

        sra     $t3,$a1,0               # second digit of second
        andi    $t3,$t3,0x000F
        PUSH    $a0
        move    $a0,$t3
        jal     hexasc
        nop
        POP     $a0
  
        sb      $v0,4($a0)

        sb      $0,5($a0)               #null character at end of string
        POP     $ra
        jr      $ra                     #back to main
        nop

