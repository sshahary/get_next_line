/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:38:20 by sshahary          #+#    #+#             */
/*   Updated: 2023/10/27 15:28:07 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	c = c % 256;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

// int	ft_strchr(char *str, char c)
// {
// 	while (str && *str)
// 	{
// 		if (*str == c)
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	if (!dst || !src)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (i >= dstsize)
		return (dstsize + src_len);
	else
		return (dst_len + src_len);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	size;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	size = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	str = (char *)malloc(size);
// 	if (!str)
// 		return (str);
// 	str[0] = '\0';
// 	if (s1 && s1[0])
// 		ft_strlcat(str, s1, size);
// 	if (s2 && s2[0])
// 		ft_strlcat(str, s2, size);
// 	return (str);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(size);
	if (!str || (!s1 && !s2))
		return (NULL);
	while (s1 && s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	int		s;

// 	s = ft_strlen(s1) + ft_strlen(s2);
// 	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!result || !s1 || !s2)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		result[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		result[i] = s2[j];
// 		j++;
// 	}
// 	result[s] = '\0';
// 	return (result);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*s;
// 	size_t	i;
// 	size_t	max;

// 	max = 0 - 1;
// 	if ((long long)count * size > max)
// 		return (NULL);
// 	i = 0;
// 	s = (char *)malloc(count * size);
// 	if (!s)
// 		return (NULL);
// 	while (count * size > i)
// 	{
// 		s[i] = 0;
// 		i++;
// 	}
// 	return (s);
// }

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	i = 0;
	s = (void *)src;
	d = dst;
	if (d == s || n == 0)
		return (d);
	while (i < (int)n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc(count * size);
	if (!s)
		return (NULL);
	while (count * size > i)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src || !dst || !dstsize)
		return (0);
	while (src && src[i] != '\0' )
	{
		i++;
	}
	if (dstsize > 0)
	{
		while (src[j] != '\0' && j < dstsize - 1)
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (i);
}
