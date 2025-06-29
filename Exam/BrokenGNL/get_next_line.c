#include "get_next_line.h"

/**
 * If dest == src and n == 0, return dest
 * if dest is greater than src copy reversibly
 * else copy normally using memcpy
 * at the end return dest
 */
void *ft_memmove(void *dest, void *src, size_t n)
{
	if(dest == src | n == 0)
		return dest;
	else if(dest > src)
	{
		while(n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
		return ft_memcpy(dest, src, n);
	return dest;
}

/**
 * copy memory from i to n from src to dest
 * 
 */
void *ft_memcpy(void *dest, void *src, size_t n)
{
	int i = 0;
	while(n > i)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}
/**
 * returns a pointer to the char found in the string
 */
char *ft_strchr(char *s, char c)
{

	int i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return s + i;
		i++;
	}
	return NULL;
}

/**
 * add a null check
 */
size_t ft_strlen(char *s)
{
	if(!s)
		return 0;
	size_t ret = 0;
	while(*s)
	{
		s++;
		ret++;
	}
	return ret;
}

/**
 * fully working
 */
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if(!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}
/**
 * fully working
 */
int str_append_str(char *s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
/**
 * put everything in an infinite loop
 * change while(!tmp) to while(tmp)
 * put the if str_append_mem if statement in that while loop
 * add ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1)
 * and break inside of the while(tmp) and close it
 * after that keep the str_append_str if statement and the read line
 * after reading -->
 * if(read_b == -1)
 * free ret and return 
 * if(read_b == 0)
 * if(ret && ret isn't empty)
 * {
 * 		null terminate the b and return ret
 * }
 * else
 * 		null terminate b free ret and return null
 * all is done
 */

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	while(1)
	{
		char *tmp = ft_strchr(b, '\n');
		while(tmp)
		{
			if(!str_append_mem(&ret, b, tmp - b + 1))
			{
				free(ret);
				return NULL;
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			break;
		}
		if(!str_append_str(&ret, b))
		{
			free(ret);
			return NULL;
		}
		int read_b = read(fd, b, BUFFER_SIZE);
		if(read_b == -1)
		{
			free(ret);
			return NULL;
		}
		if(read_b == 0)
		{
			if(ret && ret[0] != 0)
			{
				b[0] = '\0';
				return ret;
			}
			else
			{
				b[0] = '\0';
				free(ret);
				return NULL;
			}
		}
		b[read_b] = 0;
	}
	return ret;
}
