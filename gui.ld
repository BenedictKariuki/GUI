OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x100; /* initial position of the location counter, i.e., the entry point */
	.text :
	{
        *(.text); 
	}
    .data :
    {
        *(.data);
        *(.rodata);
        *(.bss);
    }

    heap = ALIGN(2); /* location counter aligned to the next exp boundary.
                      exp must be an expression whose value is a power of two.
                      ALIGN does not change the value of the location counter - it just does 
                      arithmetic on it. N.B. This is an absolute value. This type of assignment means "Take the address returned by ALIGN() and give it the name 'heap'" */
}
