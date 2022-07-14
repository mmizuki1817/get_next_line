/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimatsub <mimatsub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:44:20 by mimatsub          #+#    #+#             */
/*   Updated: 2022/07/13 01:45:00 by mimatsub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t n);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strdup_len(const char *s, size_t count);

char	*ft_strdup(const char *s);

size_t ft_strlen_n(char *str);

#endif