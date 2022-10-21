/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/21 19:48:44 by znichola         ###   ########.fr       */
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
	char	*s;

	s = ft_strchr(*buff, '\n');
		// printf("\nsfsdfsdhere s:%ld, <%s> buff<%s>\n", s - *buff, s, *buff);
	if (s == 0) // || r <= BUFFER_SIZE
	{
		*ret = ft_strnjoin(*ret, *buff, r);
		if (!ret)
			return (error);
		return (line_incomplete);
	}
	else
	{
		// s++; // to go past the /n
		// printf("\nret<%s>", *ret);
		*ret = ft_strnjoin(*ret, *buff, s - *buff);
		// printf("\nret<%s>", *ret);
		if (!*ret)
			return (error);
		free(*strs);
		*strs = ft_strndup(s, (s - *buff) - BUFFER_SIZE);
		if (!*strs)
			return (error);
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
		return (file_end);
	else
		return (half_buff);
}

// t_ret	process_rest(char **strs, char *ret)
// {
// 	char	*s;
	
// 	s = ft_strchr(*strs, '\n');
// 	ret = ft_strnjoin(ret, *strs, s - *strs);
// }

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

char	*get_next_line(int fd)
{
	static	char *strs[4096];
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
	f = find_line(fd, &strs[fd], buff, &ret);
	free(buff);
	if (f == error)
		return (NULL);
	else if (f == file_end)
		free(strs[fd]);
	return (ret);
}

char	*foo(int fd)
{
	static	char *rest[4096];
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
		f = process_leftover(&rest[fd], &ret);
	if (f == error)
		return (NULL);
	f = find_line(fd, &rest[fd], buff, &ret);
	free(buff);
	if (f == error)
		return (NULL);
	else if (f == file_end)
		free(rest[fd]);
	return (ret);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	int fd = open("files/odyssey", O_RDONLY);
	for (int i = 0; i < 7; i++)
	{
		char *l = foo(fd);
		// char *l = get_next_line(fd);
		printf("\nl%d {\n%s}\n", i, l);
		free(l);
	}
	close(fd);
	return (0);
}