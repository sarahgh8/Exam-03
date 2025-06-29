#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif 

/**
 * This fucntion filters the the buffer from teh given word
 */

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
 * The main function takes arguments and validate them
 * based on the 2 things
 * 1. There must be only 2 arguments (a.out / argv[1] = word)
 * 2. argv[1] shouldn't be empty
 * 
 * next it reads the whole stdin and stores it in the buffer
 * and then send the the buffer and the word to ft_filter fucntion.
 */
int main(int argc, char **argv)
{

    if(argc != 2 || argv[1][0] == '\0')
        return 1;
    ssize_t r;
    char buffer[BUFFER_SIZE];
    char *word = argv[1];
    char *input = NULL;
    size_t total_size = 0;
    while((r = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        char *new_input = realloc(input, total_size + r + 1);
        input = new_input;
        memmove(input + total_size, buffer, r);
        total_size += r;
        input[total_size] = '\0';
    }
    if(r < 0)
    {
        perror("Error");
        return 1;
    }
    ft_filter(input, word);
    return 0;
}