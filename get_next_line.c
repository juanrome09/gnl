/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrome <juanrome@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:44:48 by juanrome          #+#    #+#             */
/*   Updated: 2025/01/29 20:22:42 by juanrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *Master_Line, char *buffer)
{
    int size;
    size = 1;

    while(!ft_strchr(Master_Line, '\n') && size > 0)
    {
        size = read(fd, buffer, BUFFER_SIZE);
        if(size < 0)
            return (free(buffer),free(Master_Line), Master_Line = NULL);
        Master_Line[size] = 0;
        Master_Line = ft_strjoin(Master_Line, buffer);
        if(!Master_Line)
        return (free(buffer), buffer = NULL);
    }
    return (free(buffer), Master_Line);
}

char	*extract_remaining(char	*Master_Line)
{
	int		len;
	int		i;
	char	*rest;

	len = 0;
	i = 0;
	if (Master_Line == NULL)
		return (NULL);
	while (Master_Line[len] != '\n' && Master_Line[len])
		len++;
	if (Master_Line[len] == '\n')
		len++;
	rest = malloc((ft_strlen(Master_Line) - len + 1) * sizeof(char));
	if (!rest)
		return (free (Master_Line), NULL);
	while (Master_Line[len + i])
	{
		rest[i] = Master_Line[len + i];
		i++;
	}
	free (Master_Line);
	rest[i] = 0;
	return (rest);
}

char	*extract_line(char *Master_line)
{
    int     i;
    int     len;
    char    *line;

    i = 0;
    len = 0;

    if (Master_line == NULL)
        return(NULL);
    while (Master_line[len] != '\n' && Master_line[len])
        len++;
    if (len == '\n')
        len++;
    if (len == 0)
        return(NULL);
    line = malloc((len + 1) * sizeof(char));
	if (!line)
        return(NULL);
    while (i < len)
    {
        line[i] = Master_line[i];
        i++;
    }
    line[i] = 0;
    return (line);
}

char *get_next_line(int fd)
{
    static char *Master_Line;
    char        *line;
    char        *buffer;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return(free(Master_Line), Master_Line = NULL);
    buffer = malloc((BUFFER_SIZE + 1) * sizeof (char));
    if (!buffer)
        return(free(Master_Line), Master_Line = NULL);
    Master_Line = read_line(fd, Master_Line, buffer);
    if (Master_Line == NULL)
        return(NULL);
    line = extract_line(Master_Line);
    if(!Master_Line)
        return (free(line), NULL);
    if (*Master_Line == '\0')
        return (free(Master_Line), Master_Line = NULL, line);
    return line;
}

int main(void)
{
	int	fd;
	char	*line;
	
	fd = open("archivo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
