/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:51:19 by wlo               #+#    #+#             */
/*   Updated: 2021/05/28 14:51:33 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t     ft_strlen_total(char *a)
{       
        int     length;
        
        length = 0;
        if (!a)
            return (0);
        while (*a != '\0' && *a !='\n')
        {       
                length++;
                a++;
        }
        return (length);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *arr;
    size_t    i;
    size_t    j;

    if (!s1 || !s2)
        return (0);
    arr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!arr)
        return (0);
    i = 0;
    while (s1[i])
    {
        arr[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        arr[i + j] = s2[j];
        j++;
    }
    arr[i + j] = '\0';
    free(s1);
    return (arr);
}

void    new_buffer(char *s)
{
    size_t  i;
    char    *c;

    c = ft_strchr(s , '\n');
    if (!c)
        return;
    c++;
    i = 0;
    while (c[i])
    {
        s[i] = c[i];
        i++;
    }
    s[i] = '\0';
}

int get_next_line(int fd, char **line)
{
    static char buffer[BUFFER_SIZE + 1];
    char        *arr = 0;
    int         ret;

    if (fd < 0 || line == 0)
        return (-1);
    if (buffer[0])
        arr = ft_substr(buffer, 0, ft_strlen_total(buffer) + 1);
    while (ft_strchr(arr, '\n') == 0)
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (-1);
        buffer[ret] = '\0'; 
        if (ret == 0)
            break;
        if (!arr)
            arr = ft_substr(buffer, 0, (size_t)ret);
        else
            arr = ft_strjoin(arr, buffer);
    }
    *line = ft_substr(arr, 0, ft_strlen_total(arr));
    new_buffer(buffer);
    free(arr);
    if (!line[0])
        *line = ft_substr("\0", 0, 1);
    if (ret == 0)
        return (0);
    return (1);
}

// int main()
// {
//     int     fd;
// 	char	*line;
// 	int     i;

// 	fd = open("try", O_RDONLY);

//     while ((i = get_next_line(fd, &line)) > 0)
// 	{
// 	    printf("\e[33mline READ:\e[0m\n|%s|\n", line);
//         free(line);
// 	}
// 	if (i == -1)
//         printf("\e[31mError encountered\e[0m\n");
//     else if (!i)
//         printf("\e[32mEOF reached\e[0m\n|%s|\n", line);
//     else
//         printf("Unexpected return of get_next_line\ni == %d\n", i);
// 	close(fd);
//    // system("leaks a.out");
//     return (0);
// }