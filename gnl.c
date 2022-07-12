# include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


# define GET_NEXT_LINE_H
# define SUCCESS 1
# define END_OF_FILE 0
# define READ_ERROR -1

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start + 1)
	{
		p = (char *)malloc(sizeof(char) * 1);
		if (p == NULL)
			return (NULL);
		*p = '\0';
		return (p);
	}
	while (start-- > 0)
		s++;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s, (len + 1));
	return (p);
}

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (n == 0 || buf1 == buf2)
		return (buf1);
	s1 = (unsigned char *)buf1;
	s2 = (unsigned char *)buf2;
	while (n--)
	{
		*s1++ = *s2++;
	}
	return (buf1);
}


void	*ft_memmove(void *buf1, const void *buf2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (n == 0 || buf1 == buf2)
		return (buf1);
	s1 = (unsigned char *)buf1;
	s2 = (unsigned char *)buf2;
	if (s1 > s2)
	{
		while (n--)
			s1[n] = s2[n];
	}
	else
		ft_memcpy(buf1, buf2, n);
	return (buf1);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	size_t	len;

	tmp = (char *)s;
	len = ft_strlen(tmp) + 1;
	tmp = tmp + len - 1;
	while (len-- > 0)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp--;
	}
	return (NULL);
}

static char	*free_return(char *save)
{
	free(save);
	save = NULL;
	return (NULL);
}

static int	count_till_endl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	total_len = len1 + len2;
	if (!(ret = (char *)malloc((total_len + 1) * sizeof(char))))
		return (NULL);
	ft_memmove(ret, s1, len1);
	ft_memmove(ret + len1, s2, len2);
	ret[total_len] = '\0';
	free((char *)s1);
	return (ret);
}

static char	*get_save(char *save)
{
	char	*ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n')
	{
		if (!save[i])
			return (free_return(save));
		i++;
	}
	if (!(ret = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1))))
		return (NULL);
	i++;
	while (save[i])
		ret[j++] = save[i++];
	ret[j] = '\0';
	free(save);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int		read_res;
	char		*buf;
	static char	*save;

	read_res = SUCCESS;
	if (fd < 0 || !line || BUFFER_SIZE < 1 ||
	!(buf = (char *)malloc((size_t)BUFFER_SIZE + 1)))
		return (READ_ERROR);
	while (!(ft_strchr(save, '\n')) && read_res != 0)
	{
		if ((read_res = read(fd, buf, BUFFER_SIZE)) == READ_ERROR)
		{
			free(buf);
			return (READ_ERROR);
		}
		buf[read_res] = '\0';
		save = gnl_strjoin(save, buf);
	}
	free(buf);
	*line = ft_substr(save, 0, count_till_endl(save));
	save = get_save(save);
	return ((read_res == END_OF_FILE) ? END_OF_FILE : SUCCESS);
}

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc == 1 || argc == 2)
	{
		fd = (argc == 1) ? 0 : open(argv[1], P_RDONLY);
		while (get_next_line(fd, &line) == 1)
		{
			printf("%s\n", line);
			free(line);
		}
		close(fd);
	}
	else
		return (2);
	system("leaks a.out");
	return (0);
}