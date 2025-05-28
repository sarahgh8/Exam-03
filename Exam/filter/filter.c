#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#ifndef BUFF_S
#define BUFF_S 4096
#endif

// int _strchr(char *str, char c)
// {
//     int i = -1;
//     while(str[++i])
//     {
//         if(str[i] == c)
//             return 1;
//         continue;
//     }
//     return 0;
// }
// int search(char *buff, char *word, int start, size_t size)
// {
// }
void ft_filter(char *buffer, char *word)
{
    size_t word_len = strlen(word);
    size_t i = 0;
    while(buffer[i])
    {
        size_t j = 0;
        while(buffer[i + j] && word[j] && buffer[i + j] == word[j])
            j++;
        if(j == word_len)
        {
            size_t k = 0;
            while(k < word_len)
            {
                write(1, "*", 1);
                k++;
            }
            i += word_len;
        }
        else
        {
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

/**
 * The main function got a lot of stuff to do,
 * first it validats the args, they should be 2
 * (the executable and the word)
 * and the word (argv[1]) shouldn't be empty
 * 
 * then we declare 5 vars, a char to store the chars we read from the stdin
 * i for indexing and intialize it with zero
 * r = to store how many
 */
int main(int argc, char **argv)
{

    if(argc != 2 || argv[1][0] == '\0')
        return 1;
    
    char c;
    int i = 0;
    ssize_t r;
    
    char *buffer;
    char *word = argv[1];
    
    buffer = calloc(1, sizeof(char));
    if(!buffer)
        return (perror("error"), 1);
    
    while((r = read(0, &c, 1)))
    {
        buffer = realloc(buffer, i + 2);
        if(!buffer)
            return(perror("error"), free(buffer), 1);
        buffer[i] = c;
        i++;
        buffer[i] = '\0';
    }

    ft_filter(buffer, word);
    free(buffer);
    return 0;
}