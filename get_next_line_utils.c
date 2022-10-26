/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:21 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 04:26:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void debug_print(const char *restrict fmt, ...)
// {
// 	va_list ap;
// 	va_start(ap, fmt);
// 	#ifdef DEBUG
// 	vfprintf(stdout, fmt, ap);
// 	#endif
// 	va_end(ap);
// }

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
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return ((char*)s);
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

size_t	ft_strleno(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != DELIM)
	{
		i++;
	}
	if (s[i] == DELIM)
		i++;
	return (i);
}

char *ft_strmerg(char *ret, char *buff)
{
	char	*f_ret;
	char	*f_r;
	char	*t;
	
	f_ret = (char *)malloc((ft_strleno(ret) + ft_strleno(buff) + 1) * sizeof(char));
	if (!f_ret)
		return (NULL);
	f_r = f_ret;
	t = ret;
	if (ret)
		while (*ret)
			*f_r++ = *ret++;
	if (buff)
	{
		while (*buff && *buff != DELIM)
			*f_r++ = *buff++;
		if (*buff == DELIM)
			*f_r++ = '\n';
	}
	*f_r = '\0';
	if (t)
		free(t);
	return (f_ret);
}