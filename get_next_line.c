/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:12:01 by mimatsub          #+#    #+#             */
/*   Updated: 2022/07/13 01:48:53 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 20

char *get_next_line(int fd)
{
    char *buf;
    char *line;
    static char *save;
    size_t n;

    if (fd < 1 || BUFFER_SIZE < 1)
        return (NULL);

    // 前回分のsaveが残ってる
    if (save)
    {
        // \nまでか\0までをlineに移す
        // \nがあるかを調べる
        n = ft_strlen_n(save);
        // if \nまで
        if (n > 0)
        {
            line = ft_strdup_len(save, n);
            save = ft_strdup(save+n);
            return (line);
        }
        // else if \0まで
        else if (n == 0)
        {
            line = ft_strdup(save);
        }
    }
        
    //bufにBUFFER_SIZE分を読み込む-①
    buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf)
        return (NULL);
    ssize_t read_byte = read(fd, buf, BUFFER_SIZE);

    // /nがあるか探す(0 or not) && /nまでの文字数カウント
    n = ft_strlen_n(buf);
    // \nがある
    if (n > 0)
    {
        // すでにlineに値が入っている
        if (*line)
        {
            // lineに/nまでをくっつける
            line = ft_strjoin(line, buf);
        }
        // lineには値が入っていない
        else
        {
            // lineに/nまでを入れる
            line = ft_strdup_len(buf, n);
        }

        // saveに/n以降を入れる
        save = ft_strdup(buf+n); // if ちょうど終わってた時は？
        free(buf);
        return(line); //free(line)のタイミングは？
    }
    // \nがない
    if (n == 0)
    {
        // \nが来るまでreadしてbufに入れてlineにつなげてを繰り返す？
        buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        if (!buf)
            return (NULL);
        ssize_t read_byte = read(fd, buf, BUFFER_SIZE);
    }

    // if (n == -1)
    //    return (NULL)
}

int	main(void)
{
	int		fd;
	char	*line;
    int n=3;

	line = "";
	fd = open("text.txt", O_RDONLY);
	//while (line)
	while (n--)
    {
        line = get_next_line(fd);
		printf("> %s", line);
		free(line);
	}
    
	return (0);
}


/*
gnl:
    char *line
    char *save

    lineのmalloc数を知りたい（改行まで何文字あるか知りたい）
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