mult  %1, %0;      # multiply values (small * large is faster)
mflo  $t0;         # retrieve the 64-bit result in two regs
mfhi  $t1;         #
srl   $t0, 12;     # equivalent to dividing LO by 4096
and   $t1, 0x0fff; # mask HI result to fit in upper 12 bits of
sll   $t1, 20;     # LO result, then shift bits to position
or    $t0, $t1;    # combine the bits
sw    $t0, ( %2 ); # store the result to r2
