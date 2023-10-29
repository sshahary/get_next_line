/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:03:46 by sshahary          #+#    #+#             */
/*   Updated: 2023/10/29 17:46:53 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function to find and return a line
char	*substr_n(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str && str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// Function to return the remaining string after the newline
char	*substr_n_after(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	line = ft_calloc((ft_strlen(str) - i + 1), (sizeof(char)));
	if (!line)
		return (free(str), NULL);
	i++;
	while (str[i] != '\0')
		line[j++] = str[i++];
	line[j] = '\0';
	free(str);
	return (line);
}

// Function to read from the file descriptor
char	*ft_read(int fd, char *str)
{
	int		i;
	char	tmp[BUFFER_SIZE + 1];

	if (read(fd, 0, 0) < 0)
		return (free(str), NULL);
	i = 1;
	while (i > 0 && !ft_strchr(str, '\n'))
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
			return (free(str), NULL);
		tmp[i] = '\0';
		str = ft_strjoin_temp(str, tmp);
	}
	if (i <= 0 && str[0] == '\0')
		return (free(str), NULL);
	return (str);
}

// Function to get the next line
char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!str)
	{
		str = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
		if (!str)
			return (NULL);
	}
	str = ft_read(fd, str);
	if (!str)
		return (free(str), NULL);
	line = substr_n(str);
	str = substr_n_after(str);
	return (line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("123.text", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	printf("line :%s", get_next_line(fd));
// 	// printf("line :%s", get_next_line(fd));
// 	// printf("line :%s", get_next_line(fd));
// 	// printf("line :%s", get_next_line(fd));
// 	// char *line;
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("line: %s\n", line);
// 	// 	free(line); // Free each line after printing
// 	// }
// 	close(fd);
// 	return (0);
// }