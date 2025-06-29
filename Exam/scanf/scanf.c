#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

/**
 *  This function skips every space it encounters in the stdin
 *  and stops when it encounters a nomral charactar and return it to the
 *  stdin, or stops if it encounters EOF.
 * 
 *  @param f it takes a file decriptor such as the STDIN.
 *  @return it returns 1 in case of success, and -1 if there was an error.
 * 
*/
int match_space(FILE *f)
{
    int c = fgetc(f);
    while(c != EOF && isspace(c))
		c = fgetc(f);
	if(c == EOF)
		return -1;
	ungetc(c, f);
    return 1;
}

/**
 *  This function matches the read characters with the user input, and skips
 *  them, so we only store the data we want, if the character isn't matching and isn't
 *  EOF then we read a wrong char and we need to return it to the stdin, so we use ungetc
 *  @example format string: (Name: %s\n)
 *              user input: Name: Sarah\n
 *              so here we skip Name: and stores Sarah in the passed variable.
 *  @param f it takes the file descriptor (STDIN)
 *  @param c the character we want to match with
 *  @return returns 1 if the 2 chars match, -1 if they don't
 */
int match_char(FILE *f, char c)
{
	return (fgetc(f) == c);
}

/**
 *  This fucntion scans characters when %c is used
 *  we first read from the stdin using fgetc, and checks if
 *  it's EOF or not, if not we assign the read character pointer 
 *  with the read character.
 *  @param f (STDIN)
 *  @param ap the argument list, in this fucntion we need an integer pointer
 *              to store the ascii of the read character
 *  @return returns 1 in case of success, and -1 if EOF encounterd
 */
int scan_char(FILE *f, va_list ap)
{
    int *c_arg = va_arg(ap, int *);
    int c = fgetc(f);
    if(c == EOF)
        return -1;
    *c_arg = c;
    return 1;
}

/**
 *  This function scans a number from the stdin when %d is used
 *  it first checks for the sign of the number, if it's negative
 *  it assigns -1 to sign variable
 *  and then it loops on the characters and checks if they're digits
 *  if true it behaves like atoi, and changes the flag read var to 1, indicating of the success
 *  of the operation, if not a digit and not EOF, it ungets the char
 *  at the end it assigns the pointer sent by ap, to the end result multiplied by the sign
 * 
 *  @param f (STDIN)
 *  @param ap the arguments list, we need an integer ponter to store the number
 *  @return it returns 1 in case of success, and -1 if there's a read error
 */
int scan_int(FILE *f, va_list ap)
{
    int *i_arg = va_arg(ap, int *);
    int sign = 1, result = 0, read = 0;
    int i = fgetc(f);

    if(i == '-' || i == '+')
    {
        if(i == '-')
            sign = -1;
        i = fgetc(f);
    }
    while(i != EOF && isdigit(i))
    {
        result *= 10;
		result += i - '0';
        read = 1;
        i = fgetc(f); 
    }
    if(i != EOF)
        ungetc(i, f);
    if(!read)
        return 0;
	printf("%d\n", result * sign);
    *i_arg = result * sign;
	printf("%d\n", *i_arg);
    return 1;
}
/**
 * 	This function scans a string from the stdin when %s is used
 * 	it walks through the characters read from the stdin and checks
 *  if they're not spaces or EOF, it continue reading and adding the chars
 * 	to the array sent by ap, after the loop is exited, if it didn't encounter EOF
 * 	it returns the space to the stdin using ungetc, and then terminate the string with '\0'
 * 
 * 	@param f (STDIN)
 * 	@param ap the arguments list, char * is used in here to store string in it
 * 	@return returns 1 in case of success, and -1 in case of error (zero char read)
 */
int scan_string(FILE *f, va_list ap)
{
	char *s_arg = va_arg(ap, char *);
	int i = 0;
	int c;

	while((c = fgetc(f)) != EOF && !isspace(c))
		s_arg[i++] = c;
	if(c != EOF)
		ungetc(c, f);
	s_arg[i] = '\0';
	if(!i)
		return -1;
	return 1;
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int main ()
{
	char str[100];
	int num;
	char ch;

	// 1. Valid input
	ft_scanf("Hello %s %d %c", str, &num, &ch);
	// Input: Hello Sarah 42 A
	// Expected: str = "Sarah", num = 42, ch = 'A'
	printf("%s %d %c\n", str, num, ch);

	// 2. Missing part
	// ft_scanf("Name: %s Age: %d", str, &num);
	// Input: Name:   (no name)
	// Expected: return -1, nothing scanned

	// 3. Extra literal mismatch
	// ft_scanf("Start %s", str);
	// Input: Sturt Sarah
	// Expected: match_char fails on 'a' vs. 'u'
}
