/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:12:01 by mimatsub          #+#    #+#             */
/*   Updated: 2022/07/03 21:43:39 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>


#define BUFFER_SIZE 3


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
	size_t		len;
	char		*dest;

	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, count + 1);
	return (dest);
}

size_t ft_strlenn(char *str)
{
    size_t count;

    if (!str) // ?
        return (0);
    while (*str++)
    {
        count++;
        if (*str == '\n' || *str == EOF) // EOFの見分け方ってこれでいいのか？
        {
            if (*str == '\n')
                count++;
            return (count + 1);
        }
    }
    return (0);
}

char *get_next_line(int fd)
{
    //gnl:lineのmalloc数を知りたい（改行まで何文字あるか知りたい）
    //char *buf->malloc BUFFER_SIZE
    char *buf;
    char *line;
    static char *save;
    size_t count;

    if (fd < 1 || BUFFER_SIZE < 1)
        return (NULL);
    FILE *file = fopen(fd, "r");
    //bufにBUFFER_SIZE分を読み込む-①
    buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf)
        return (NULL);
    fread(buf, sizeof(char), BUFFER_SIZE, file);
    // bufの文字数をカウント
    count = ft_strlenn(buf);
    //char *save->malloc BUFFER_SIZE
    // 1.bufに\nかEOFが含まれている
    if (count != 0)
    {
        //そこまでの文字数(\n含めた文字数)をカウント
        //char *line->malloc カウントした文字数
        line = (char *)malloc(sizeof(char) * (count + 1));  // +1 -> '\0'
        if (!line)
            return (NULL);
        // dup save->line(あれば)
        line = ft_strdup_len(buf, count);
        // buf のポインタの位置ずらす
        buf = buf + count;
        // dup buf->line(join)
       // ft_strjoin()

        
    }

        // free(save)
        // if EOF
        //     free(buf)
        //     return
        
    //2.含まれてない
    else if (count == 0)
    {
        // 最後までカウント(BUFFER_SIZE文字)

        //strdup buf->save(join)
        save = ft_strjoin(save, buf);
        //カウントを維持したまま①に戻る
    }
    fclose(file);
    return (line);
        
}


gnl:lineのmalloc数を知りたい（改行まで何文字あるか知りたい）
    char *buf->malloc BUFFER_SIZE
    char *save->malloc BUFFER_SIZE
    bufにBUFFER_SIZE分を読み込む-①
    bufの文字数をカウント
    1.bufに\nかEOFが含まれている
        そこまでの文字数(\n含めた文字数)をカウント
        char *line->malloc カウントした文字数
        dup save->line(あれば)
        dup buf->line(join)
        free(save)
        if EOF
            free(buf)
            return
        
    2.含まれてない
        最後までカウント(BUFFER_SIZE文字)
        strdup buf->save(join)
        カウントを維持したまま①に戻る

lineには二次元配列で入れるの？
そしたらこっちもstatic変数になるのか？

最初以外のgnl
    char *buf->malloc BUFFER_SIZE
    bufにBUFFER_SIZE分を読み込む
    char *line malloc 改行までの文字数
    save分をlineに格納
    1.改行が含まれている
        改行までをlineに格納(join)
        改行以降をtmp(save)に格納
        tmpを維持したまま（static変数？）lineを返す
    2.改行が含まれていない
        lineに格納(join)
        bufにBUFFER_SIZE分を読み込む
        1.2を繰り返す
    3.EOFである
        EOFまでをlineに格納(join)
        malloc->lineの最後に'\0'
        lineを返す
        終わり
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd)
{

    
    // //gnl:lineのmalloc数を知りたい（改行まで何文字あるか知りたい）
    // //char *buf->malloc BUFFER_SIZE
    // char *buf;
    // char *line;
    // static char *save;
    // size_t count;

    // if (fd < 1 || BUFFER_SIZE < 1)
    //     return (NULL);
    // FILE *file = fopen(fd, "r");
    // //bufにBUFFER_SIZE分を読み込む-①
    // buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    // if (!buf)
    //     return (NULL);
    // fread(buf, sizeof(char), BUFFER_SIZE, file);
    // // bufの文字数をカウント
    // count = ft_strlenn(buf);
    // //char *save->malloc BUFFER_SIZE
    // // 1.bufに\nかEOFが含まれている
    // if (count != 0)
    // {
    //     //そこまでの文字数(\n含めた文字数)をカウント
    //     //char *line->malloc カウントした文字数
    //     line = (char *)malloc(sizeof(char) * (count + 1));  // +1 -> '\0'
    //     if (!line)
    //         return (NULL);
    //     // dup save->line(あれば)
    //     line = ft_strdup_len(buf, count);
    //     // buf のポインタの位置ずらす
    //     buf = buf + count;
    //     // dup buf->line(join)
    //    // ft_strjoin()

        
    // }

    //     // free(save)
    //     // if EOF
    //     //     free(buf)
    //     //     return
        
    // //2.含まれてない
    // else if (count == 0)
    // {
    //     // 最後までカウント(BUFFER_SIZE文字)

    //     //strdup buf->save(join)
    //     save = ft_strjoin(save, buf);
    //     //カウントを維持したまま①に戻る
    // }
    // fclose(file);
    // return (line);
    printf("%i", fd);
    char *s = "he";
    return (s);
}

int	main(void)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("test.txt", O_RDONLY);
	while (line)
	{
		
        line = get_next_line(fd);
		printf("> %s", line);
        //printf("%i", fd);
		free(line);
	}
    
	return (0);
}