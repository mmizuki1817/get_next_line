/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utiles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:40:30 by mimatsub          #+#    #+#             */
/*   Updated: 2022/07/13 01:40:52 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>


size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while (n > 1 && *src != '\0')
	{
		*dst++ = *src++;
		n--;
	}
	*dst = '\0';
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		len;
	size_t		i;
	size_t		j;

	if (dst == NULL && size == 0)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
	{
		len = src_len + size;
		return (len);
	}
	i = dst_len;
	j = 0;
	while (size - dst_len > 1 && src[j] != '\0')
	{
		dst[i++] = src[j++];
		size--;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(sizeof(char) * len);
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, (ft_strlen(s1) + 1));
	ft_strlcat(p, s2, len);
	return (p);
}

char	*ft_strdup_len(const char *s, size_t count)
{
	char		*dest;

	dest = (char *)malloc((count + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, count + 1);
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(s);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, len + 1);
	return (dest);
}

size_t ft_strlen_n(char *str)
{
    size_t count;

    count = 0;
    if (!str) // ?
        return (-1); // 負の数可能？
    while (*str++)
    {
        count++;
        //if (*str == '\n' || *str == EOF) // EOFの見分け方ってこれでいいのか？
        if (*str == '\n')
        {
            return (count + 1);
        }
    }
    return (0);
}