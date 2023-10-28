/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:03:46 by sshahary          #+#    #+#             */
/*   Updated: 2023/10/28 12:36:43 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	ft_checkerrors(int fd)
// {
// 	if (fd < 0 || BUFFER_SIZE < 1)
// 		return (1);
// 	return (0);
// }

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
	i = 0;
	while (str && str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
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
	line = ft_calloc((ft_strlen(str) - i + 1), (sizeof(char)));
	if (!line)
		return (free(str), NULL);
	i++;
	while (str[i - 1] != '\0') // (- 1) put later
		line[j++] = str[i++];
	line[j] = '\0';
	free(str);
	return (line);
}

// Function to read from the file descriptor
char	*ft_read(int fd, char *str)
{
	int		i;
	char	*tmp;

	if (read(fd, 0, 0) < 0)
		return (free(str), NULL);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	i = read(fd, tmp, BUFFER_SIZE);
	while (i > 0)
	{
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp);
		if (ft_strchr(tmp, '\n') || i == 0)
			break ;
		i = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	if (i <= 0 && str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

// Function to get the next line
char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (free(str), NULL);
	if (!str)
		str = ft_calloc(1, 1);
	str = ft_read(fd, str);
	if (!str)
		return (free(str), NULL);
	line = substr_n(str);
	str = substr_n_after(str);
	return (line);
}

// void leak(void)
// {
// 	system("leaks a.out");
// }

// int main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	i = 30;
// 	fd = open("example.txt", O_RDONLY);
// 	while (i > 0)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			printf("\nft returned NULL\n");
// 			leak();
// 			return (0);
// 		}
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// 	leak();
// 	return (0);
// }