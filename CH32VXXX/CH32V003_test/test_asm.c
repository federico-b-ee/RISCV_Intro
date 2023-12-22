#include <stdio.h>
void main()
{ 
    register int r_t2 asm("t2");
    int c = 16;
    asm volatile
	(
		"addi	t0, x0, %[in]\n\t"
		"addi	%[out], t0, 4\n\t"
		: [out]"=r"(r_t2)
		: [in]"r"(c)
		: "t0", "t1"
	);

	printf("%d", r_t2);
}