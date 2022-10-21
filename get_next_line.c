/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/22 01:42:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_ret	process_chunk(char **chunk, char **split_chunk)
{
	*split_chunk = ft_nextword(chunk, DELIM);
	if (!*split_chunk)
		return (error);
	return (success);
}

t_ret	process_leftover(char **leftover, char **ret)
{
	char	*head;
	char	*t;
	
	head = *leftover;
	t = ft_nextword(&head, DELIM);
	if (!t)
		return (error);
	*ret = ft_strpmerg(*ret, t, NULL);
	if (!*ret)
		return (error);
	t = ft_strndup(head, 0);
	free(*leftover);
	*leftover = t;
	return (success);
}

t_ret	process_buffer(char **strs, char **buff, char **ret, ssize_t r)
{
	char	*a;
	char	*b;
	
	(void)r;
	a = ft_strchr(*buff, DELIM);
		// printf("\nsfsdfsdhere s:%ld, <%s> buff<%s>\n", s - *buff, s, *buff);
	if (!a)
	{
		b = ft_strjoin(*ret, *buff);
		if (!ret)
			return (error);
		free(*ret);
		*ret = NULL;
		*ret = b;
		return (line_incomplete);
	}
	else
	{
		a++;
		b = ft_strdup(a);
		if (!b)
			return (error);
		// free(*strs);
		*a = '\0';
		a = b;
		b = ft_strjoin(*ret, *buff);
		if (!b)
		{
			free(a);
			return (error);
		}
		*strs = a;
		free(*ret);
		*ret = b;
		return (line_complete);
	}
}

t_ret	fill_buffer(int fd, char *b, ssize_t *r)
{
	// b = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	// if (!b)
	// 	return (error);
	ft_bzero(b, BUFFER_SIZE);
	*r = read(fd, b, BUFFER_SIZE);
	// printf("r:%zd\n%s\n", *r, b);
	if (*r < 0)
		return (error);
	else if (*r == BUFFER_SIZE)
		return (full_buff);
	else if (*r >= 0)
	{
		// printf("\nfond the end\n");
		return (file_end);
	}
	else
		return (half_buff);
}

t_ret	find_line(int fd, char **strs, char *buff, char **ret)
{
	t_ret	process;
	t_ret	fill;
	ssize_t	r;
	
	process = line_incomplete;
	fill = half_buff;
	while (process == line_incomplete)
	{
		fill = fill_buffer(fd, buff, &r);
		// printf("buff<%s>\n", buff);
		// printf("r:%zd\n%s\n", r, buff);
		process = process_buffer(strs, &buff, ret, r);
		if (process == error || fill == error)
			return (error);
		else if (fill == file_end)
			return (file_end);
	}
	return (line_complete);
}

t_ret	process_stored(char **strs, char **ret)
{
	char	*a;
	char	*b;
	
	a = ft_strchr(*strs, DELIM);
	if (!a) // it is full of stuff
		b = ft_strjoin(*ret, *strs);
	else
	{
		b = ft_strdup(a);
		if (!b)
			return (error);
		// free(*strs);
		*a = '\0';
		a = b;
		b = ft_strjoin(*ret, *strs);
		*strs = a;
	}
	if (!b)
		return (error);
	free(*ret);
	*ret = b;
	if (a)
		return (file_end);
	else 
		return (stor_end);
}

char	*get_next_line(int fd)
{
	static	char *rest[4096];
	// char	buff[BUFFER_SIZE];
	char	*buff;
	char	*ret;
	t_ret	f;
	
	// ret = NULL;
	// buff = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char));
	if (!ret)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL); // free stuff before quit
	*ret = '\0';
	// setup done;

	f = success;
	if (rest[fd])
		f = process_stored(&rest[fd], &ret);
	if (f == file_end)
		return (ret);
	if (f == error)
		return (NULL);
	f = find_line(fd, &rest[fd], buff, &ret);
	// free(buff);
	if (f == error)
		return (NULL);
	else if (f == file_end)
	{
		free(rest[fd]);
		rest[fd] = NULL;
		return (ret);
	}
	return (ret);
}


int main(void)
{
	// (void)argc;
	// (void)argv;
	
	int fd = open("files/odyssey", O_RDONLY);
	for (int i = 0; i < 20; i++)
	{
		char *l = get_next_line(fd);
		// char *l = get_next_line(fd);
		printf("\nl%d {%s}\n", i, l);
		free(l);
	}
	close(fd);
	return (0);
}