/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/22 14:52:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_ret	process_buffer(char **strs, char **buff, char **ret)
{
	char	*a;
	char	*b;
	
	a = ft_strchr(*buff, DELIM);
	if (!a)
	{
		b = ft_strjoin(*ret, *buff);
		if (!ret)
			return (error2);
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
			return (error2);
		// free(*strs);
		*a = '\0';
		a = b;
		b = ft_strjoin(*ret, *buff);
		if (!b)
		{
			free(a);
			return (error2);
		}
		if (!*strs)
			free(*strs);
		*strs = a;
		free(*ret);
		*ret = b;
		return (line_complete);
	}
		// free(*ret);
		// *ret = NULL;
		// *ret = b;
		// return (line_incomplete);
}

t_ret	process_stored(char **strs, char **ret, char **buff)
{
	char	*a;
	char	*b;
	
	if (!*strs)
		return (stor_end);
	a = ft_strchr(*strs, DELIM);
	if (!a) // it is full of stuff
	{
		b = ft_strjoin(*ret, *strs);
		free(*strs);
	}
	else
	{
		a++;
		b = ft_strdup(a);
		if (!b)
			return (error2);
		free(*strs);
		*a = '\0';
		a = b;
		b = ft_strjoin(*ret, *strs);
		*strs = a;
	}
	if (!b)
		return (error2);
	free(*ret);
	*ret = b;
	if (a)
	{
		free(*buff);
		return (line_complete);
	}
	return (stor_end);
	// else 
	// 	return (stor_end);
}

t_ret	fill_buffer(int fd, char *b, ssize_t *r)
{
	ft_bzero(b, BUFFER_SIZE);
	*r = read(fd, b, BUFFER_SIZE);
	if (*r < 0)
		return (error2);
	else if (*r == BUFFER_SIZE)
		return (full_buff);
	else if (*r >= 0)
		return (file_end);
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
		process = process_buffer(strs, &buff, ret);
		if (process == error2 || fill == error2)
			return (error2);
		else if (fill == file_end)
			return (file_end);
	}
	return (line_complete);
}

char	*managment(int fd, char **buff, char **ret)
{
	// if (action == initialise)
	// {
		if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);
		*ret = (char *)malloc(sizeof(char));
		if (!*ret)
			return (NULL);
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!*buff)
		{
			free(*ret);
			return (NULL); // free stuff before quit
		}
		**ret = '\0';
	// }
	// else if (action == liberate)
	// {
	// 	free(**buff);
	// }
	return (*ret);
}

char	*get_next_line(int fd)
{
	static	char *rest[4096];
	char	*buff;
	char	*ret;
	t_ret	f;
	
	if (!managment(fd, &buff, &ret))
		return (NULL);
	
	f = process_stored(&rest[fd], &ret, &buff);
	if (f == line_complete)
		return (ret);
	if (f == error2)
		return (NULL);
	f = find_line(fd, &rest[fd], buff, &ret);
	if (f == error2)
		return (NULL);
	else if (f == file_end)
	{
		// free(rest[fd]);
		rest[fd] = NULL;
	}
	free(buff);
	return (ret);
}

#ifdef MAIN
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
#endif /* main */