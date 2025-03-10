/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrome <juanrome@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:44:48 by juanrome          #+#    #+#             */
/*   Updated: 2025/03/10 17:36:01 by juanrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *master_line, char *buffer)
{
	int	size;

	size = 1;
	while (!ft_strchr(master_line, '\n') && size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size < 0)
			return (free(buffer), free(master_line), master_line = NULL);
		buffer[size] = '\0';
		master_line = ft_strjoin(master_line, buffer);
		if (!master_line)
			return (free(buffer), NULL);
	}
	return (free(buffer), master_line);
}

char	*extract_remaining(char	*master_line)
{
	int		len;
	int		i;
	char	*rest;

	len = 0;
	i = 0;
	if (master_line == NULL)
		return (NULL);
	while (master_line[len] != '\n' && master_line[len])
		len++;
	if (master_line[len] == '\n')
		len++;
	rest = malloc((ft_strlen(master_line) - len + 1) * sizeof(char));
	if (!rest)
		return (free (master_line), NULL);
	while (master_line[len + i])
	{
		rest[i] = master_line[len + i];
		i++;
	}
	free (master_line);
	rest[i] = 0;
	return (rest);
}

char	*extract_line(char *master_line)
{
	char	*line;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (master_line == NULL)
		return (NULL);
	while (master_line[len] != '\n' && master_line[len])
		len++;
	if (master_line[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = master_line[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*master_line;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(master_line);
		return (master_line = NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buffer)
		return (free(master_line), master_line = NULL);
	master_line = read_line(fd, master_line, buffer);
	if (master_line == NULL)
		return (NULL);
	line = extract_line(master_line);
	if (!line)
		return (free (master_line), master_line = NULL);
	master_line = extract_remaining(master_line);
	if (!master_line)
		return (free(line), NULL);
	if (*master_line == '\0')
		return (free(master_line), master_line = NULL, line);
	return (line);
}
/* int main(void)
{
    int fd;
    char *line;

    fd = open("archivo.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}*/