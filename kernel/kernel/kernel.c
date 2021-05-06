#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/kernel/tty.h"
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	terminal_writestring("Welcome to lqos!\n");
}
