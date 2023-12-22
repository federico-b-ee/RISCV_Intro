.text
.align 2
.globl _start

_start:
    LI a0, 0           # Initialize a0 to 0

    # Copy 16 bytes from address 400 to address 800
    LI s1, 16          # Initialize s1 to 16
    LI s0, 0           # Initialize s0 to 0

L0:
    LB a1, 400(s0)     # Load a byte from memory at address s0 + 400 into a1
    SB a1, 800(s0)     # Store a byte from a1 to memory at address s0 + 800

    ADDI s0, s0, 1     # Increment s0 by 1
    BNE s0, s1, L0     # Branch to L0 if s0 is not equal to s1

    # Read 16 bytes from address 800
    LI s0, 0           # Reset s0 to 0

L1:
    LB a0, 800(s0)     # Load a byte from memory at address s0 + 800 into a0

    ADDI s0, s0, 1     # Increment s0 by 1
    BNE s0, s1, L1     # Branch to L1 if s0 is not equal to s1
    EBREAK             # Halt the program


.data
.align 2



