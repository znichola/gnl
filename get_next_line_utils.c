/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:21 by znichola          #+#    #+#             */
/*   Updated: 2022/10/22 00:05:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s) + 1;
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	return ((char *)ft_memcpy(ret, s, len));
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*r;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

char	*ft_nextword(char **str, char const c)
{
	char	*ret;
	char	*end;
	size_t	len;

	while (**str == c && **str != '\0')
		(*str)++;
	end = (char *)*str;
	// while (*end != c && *end != '\0')
	// 	end++;
	len = end - *str + 1;
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	end = ret;
	while (len-- > 1)
		*end++ = *(*str)++;
	*end = '\0';
	return (ret);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strpmerg(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*r;
	size_t	i;

	if (!s3)
		i = ft_strlen(s1);
	else
		i = s3 - s2;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	r = ret;
	while (*s1)
		*r++ = *s1++;
	while (*s2 && s2 <= s3)
		*r++ = *s2++;
	*r = '\0';
	// free(s1);
	// free(s2);
	return (ret);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*ret;
	char	*r;
	size_t	i;

	i = ft_strlen(s2);

	if (n > i || n == 0)
		i = ft_strlen(s1) + i;
	else
		i = ft_strlen(s1) + n;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	r = ret;
	while (*s1)
		*r++ = *s1++;
	i += 1;
	while (*s2 && i-- > 0)
		*r++ = *s2++;
	*r = '\0';
	// free(s2);
	return (ret);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest != NULL || src != NULL)
		while (n-- > 0)
			*d++ = *s++;
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	len;
	
	len = ft_strlen(s);
	if (n + 1 < len)
		len = n;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	return ((char *)ft_memcpy(ret, s, (len + 1)));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*td;

	td = dest;
	if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
	while (*dest)
	{
		dest++;
		size--;
	}
	while (*src && size-- > 1)
		*dest++ = *src++;
	*dest = '\0';
	while (*src++)
		dest++;
	return (dest - td);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (size > 0)
	{
		if (slen + 1 < size)
			while (*src)
				*dest++ = *src++;
		else if (size != 0)
			while (--size > 0)
				*dest++ = *src++;
		*dest = '\0';
	}
	return (slen);
}

char	*ft_strchr(const char *s, int c)
{
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = (void *)malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}
