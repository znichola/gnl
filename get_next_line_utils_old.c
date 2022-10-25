/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_old.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:21 by znichola          #+#    #+#             */
/*   Updated: 2022/10/25 20:59:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_subsstr(char const *s, char const *end)
{
	char	*ret;
	size_t	i;
	size_t	e;
	
	if (end < s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	// printf("length of str:%lu clac%lu\n", i, end - s);
	if ((size_t)(end - s) < i)
		i = end - s;
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	e = 0;
	while (e < i)
	{
		ret[e] = s[e];
		e++;
	}
	ret[e] = '\0';
	return (ret);
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	len += 1;
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	while (len-- > 0)
		ret[len] = s[len];
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*r;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	ret = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!ret)
		return (NULL);
	r = ret;
	while (*s1)
		*r++ = *s1++;
	while (*s2)
		*r++ = *s2++;
	*r = '\0';

	return (ret);
}

char	*ft_buffmerg(char *s, char *buff)
{
	char	*ret;
	char	*r;
	size_t	i;
	size_t	j;
	char 	t;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	while (buff[j] != '\0' && *buff != DELIM)
	{
		t = buff[j];
		// printf("\nt:%zu t{%c}\n", j, t);
		j++;
	}
	if (buff[j] == DELIM)
		j++;
	ret = (char *)malloc(sizeof(char) * (i + j + 1));
	error_print("I malloc-ed in buff merg,	ret:%p\n", ret);
	if (!ret)
		return (NULL);
	r = ret;
	while (*s)
		*r++ = *s++;
	while (*buff != '\0' && *buff != DELIM)
		*r++ = *buff++;
	// printf("merged stop r{%s}\nbuff{%s}\n", r, buff);
	if (*buff == DELIM)
		*r++ = DELIM;
	*r = '\0';
	if (*s)
		free(s);
	error_print("I freed 			buff:%p\n", s);
	return (ret);
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
