/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:03:46 by sshahary          #+#    #+#             */
/*   Updated: 2023/10/27 11:29:03 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_checkerrors(int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (1);
	return (0);
}

// Function to find and return a line
char	*substr_n(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	if (str[i] != '\0' && str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	ft_strlcpy(line, str, i + 1);
	return (line);
}

// Function to return the remaining string after the newline
char	*substr_n_after(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		line = ft_calloc((ft_strlen(str) - i + 1), (sizeof(char)));
		if (!line)
			return (free(str), NULL);
		ft_strlcpy(line, str + i, ft_strlen(str) - i + 1);
		return (line);
	}
	i++;
	line = ft_calloc((ft_strlen(str) - i + 1), (sizeof(char)));
	if (!line)
		return (NULL);
	ft_strlcpy(line, str + i, ft_strlen(str) - i + 1);
	return (line);
}

// Function to read from the file descriptor
char	*ft_read(int fd, char *str)
{
	int		i;
	char	*tmp;
	char	*new_str;

	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	i = 1;
	while (i > 0 && !(ft_strchr(str, '\n')))
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
			return (free(tmp), free(str), NULL);
		tmp[i] = '\0';
		new_str = ft_calloc(ft_strlen(str) + i + 1, sizeof(char));
		if (!new_str)
			return (free(tmp), free(str), NULL);
		ft_strlcpy(new_str, str, ft_strlen(str) + i + 1);
		ft_strlcat(new_str, tmp, ft_strlen(str) + i + 1);
		free(str);
		str = new_str;
	}
	free(tmp);
	new_str = 0;
	return (str);
}

// Function to get the next line
char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*new_str;

	if (ft_checkerrors(fd))
		return (NULL);
	if (!str)
		str = ft_calloc(1, 1);
	str = ft_read(fd, str);
	if (!str)
		return (free(str), NULL);
	line = substr_n(str);
	new_str = substr_n_after(str);
	free(str);
	str = new_str;
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
// 	printf("line :%s", get_next_line(fd));
// 	printf("line :%s", get_next_line(fd));
// 	printf("line :%s", get_next_line(fd));
// 	// char *line;
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("line: %s\n", line);
// 	// 	free(line); // Free each line after printing
// 	// }
// 	close(fd);
// 	return (0);
// }