        .text
        .align 2
        .globl _start

_start:
        LI s0, 0            # Initialize s0 to 0
        LI s1, 16           # Initialize s1 to 16

L0:
        LB a0, 400(s0)      # Load a byte from memory at address s0 + 400 into a0 (assuming LEDs are connected to a0)
        JAL wait            # Jump and link to the wait label
        ADDI s0, s0, 1      # Increment s0 by 1
        BNE s0, s1, L0      # Branch to L0 if s0 is not equal to s1
        EBREAK              # Halt the program

wait:
        LI t0, 1            # Initialize t0 to 1
        SLLI t0, t0, 2      # Shift t0 left by 2 (multiply by 4)
L1:
        ADDI t0, t0, -1     # Decrement t0 by 1
        BNEZ t0, L1         # Branch to L1 if t0 is not zero
        RET                 # Return from the function

        .data
        .align 2


