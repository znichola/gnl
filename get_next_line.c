/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/21 02:04:18 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_ret	process_buffer(char *strs, char **buff, char *ret, ssize_t r)
{
	char	*i;

	i = ft_strchr(*buff, '\n');
	if (!i || r < BUFFER_SIZE)
	{
		ret = ft_strnjoin(ret, *buff, r);
		if (!ret)
			return (error);
		return (line_incomplete);
	}
	else
	{
		i++; // to go past the /n
		ret = ft_strnjoin(ret, *buff, i - *buff);
		if (!ret)
			return (error);
		free(strs);
		strs = ft_strndup(i, (i - *buff) - BUFFER_SIZE);
		if (!strs)
			return (error);
		return (line_complete);
	}
}

t_ret	fill_buffer(int fd, char **b, ssize_t *r)
{
	*b = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*b)
		return (error);
	ft_bzero(*b, BUFFER_SIZE);
	*r = read(fd, *b, BUFFER_SIZE);
	// printf("r:%zd\n%s\n", *r, b);
	if (*r < 0)
		return (error);
	else if (*r >= 0)
		return (file_end);
	else if (*r == BUFFER_SIZE)
		return (full_buff);
	else
		return (half_buff);
}

t_ret	find_line(int fd, char *strs, char *buff, char *ret)
{
	t_ret	process;
	t_ret	fill;
	ssize_t	r;
	
	process = line_incomplete;
	fill = half_buff;
	while (process != line_complete)
	{
		fill = fill_buffer(fd, &buff, &r);
		printf("r:%zd\n%s\n", r, buff);
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
	
	ret = NULL;
	buff = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	f = find_line(fd, strs[fd], buff, ret);
	free(buff);
	if (f == error)
		return (NULL);
	else if (f == file_end)
		free(strs[fd]);
	return (ret);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	int fd = open("files/wiki", O_RDONLY);
	char *l = get_next_line(fd);
	printf("\nwiki {%s}\n", l);
	free(l);
	close(fd);
	return (0);
}