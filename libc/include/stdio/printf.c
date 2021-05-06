#include <stdarg.h>
#include <stddef.h>

#include "../stdio.h"
#include "../string.h"
#include "../../../kernel/include/kernel/tty.h"

#define _FMT_SEP '%'
#define _FMT_CHAR 'c'
#define _FMT_STR  's'

void print(const char *ptr, size_t size)
{
	while (*ptr != '\0') {
		terminal_putchar(*ptr);
		ptr++;
	}
}

/*Support only char and strings*/
int printf(const char *fmt, ...)
{
	va_list args;
	int num_params = 0;
	const char *fmt_cpy = fmt;
	char *arg;
	size_t  len;

	/*Need to parse received arguments*/
	while (*fmt) {
		if ( *fmt == _FMT_SEP && ( *(fmt+1) != *fmt  || *(fmt-1) != *fmt )) {
			num_params++;
		}

		fmt++;
	}
	
	va_start(args, num_params);

	/*Re-parsing from beginning*/
	fmt = fmt_cpy;

	while (*fmt != '\0') {
		if ( *fmt == _FMT_SEP && ( *(fmt+1) != *fmt  || *(fmt-1) != *fmt )) {
			fmt++;
			switch (*fmt) {
				case _FMT_CHAR:
					arg = va_arg(args, char *);
					print(arg,sizeof(char));
					break;
				case _FMT_STR:
					arg = va_arg(args, char *);
					len = strlen((const char *)arg);
					print(arg,len);
					break;

			}
		} else {
			print(fmt,sizeof(char));
		}

		fmt++;
	}
	

	va_end(args);

	return 0;
}
