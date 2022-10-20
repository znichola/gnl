/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/21 00:27:29 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_ret	process_buffer(char *strs, char *buff, char *ret)
{
	char	*i;

	i = ft_strchr(buff, '\n');
	if (!i)
	{
		ret = ft_strnjoin(ret, buff, BUFFER_SIZE);
		if (!ret)
			return (error);
		return (line_incomplete);
	}
	else
	{
		i++; // to go past the /n
		ret = ft_strnjoin(ret, buff, i - buff);
		if (!ret)
			return (error);
		free(strs);
		strs = ft_strndup(i, (i - buff) - BUFFER_SIZE);
		if (!strs)
			return (error);
		return (line_complete);
	}
}

t_ret	fill_buffer(int fd, char *b)
{
	ssize_t	l;

	b = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!b)
		return (NULL);
	ft_bzero(b, BUFFER_SIZE);
	l = read(fd, b, BUFFER_SIZE);
	if (l < 0)
		return (error);
	else if (l == 0)
		return (file_end);
	else if (l == BUFFER_SIZE)
		return (full_buff);
	else
		return (half_buff);
}

t_ret	find_line(int fd, char *strs, char *buff, char *ret)
{
	t_ret	process;
	t_ret	fill;

	process = line_incomplete;
	fill == half_buff;
	while (process != line_complete)
	{
		fill = fill_buffer(fd, buff);
		process = process_buffer(strs, buff, ret);
		if (process == error || fill == error)
			return (error);
		else if (buff == file_end)
			return (file_end);
	}
	return (line_complete);
}

char	*get_next_line(int fd)
{
	static	char *strs[4096];
	char	*buff;
	char	*ret;
	
	(void)find_line(fd, strs[fd], buff, ret);

	free(buff);
	return (ret);
}


