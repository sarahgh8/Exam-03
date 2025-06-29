#include "get_next_line.h"

void *ft_memmove(void *dest, void *src, size_t n)
{
	if(dest == src || n == 0)
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
char *ft_strchr(char *s, char c) //comparison
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
size_t ft_strlen(char *s) //not s
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
int str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
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
		ssize_t read_b = read(fd, b, BUFFER_SIZE);
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
			else{
				b[0] ='\0';
				free(ret);
				return NULL;
			}
		}
		b[read_b] = 0;
	}
	return ret;
}

int main()
{
	char *line;
	int fd = open("get_next_line.h", O_RDONLY);
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}