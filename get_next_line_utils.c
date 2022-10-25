/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:21 by znichola          #+#    #+#             */
/*   Updated: 2022/10/25 22:03:45 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void debug_print(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	#ifdef DEBUG
	vfprintf(stdout, fmt, ap);
	#endif
	va_end(ap);
}

void malloc_print(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	#ifdef DEBUG_MALLOC
	vfprintf(stdout, fmt, ap);
	#endif
	va_end(ap);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = (void *)malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	// error_print("here trying to print shit%p\n", s);
	// error_print("lsfjdsf {%s}\n", s);
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n > 0)
	{
		*p = '\0';
		p++;
		n--;
	}
}

char	*ft_buffmerg(char *s, char *buff)
{
	char	*ret;
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buff)
		return (s);
	while (s[i] != '\0')
		i++;
	while (buff[j] != '\0' && *buff != DELIM)
		j++;
	if (buff[j] == DELIM)
		j++;
	ret = (char *)malloc(sizeof(char) * (i + j + 1));
	malloc_print("I malloc-ed in buff merg,	ret:%p\n", ret);
	if (!ret)
		return (NULL);
	r = ret;
	while (*s)
		*r++ = *s++;
	while (*buff != '\0' && *buff != DELIM)
		*r++ = *buff++;
	if (*buff == DELIM)
		*r++ = DELIM;
	*r = '\0';
	if (*s)
		free(s);
	malloc_print("I freed 			buff:%p\n", s);
	return (ret);
}
