/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 05:14:58 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	initbuffer(t_rest *rest)
{
	if (rest->root == NULL)
	{
		rest->root = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
			if (!rest->root)
				return (MALLOC_ERROR);
		rest->seek = rest->root;
	}
	return (1);
}

char *freeret(t_rest *rest, int r, char *ret)
{
	free(rest->root);
	rest->root = NULL;
	rest->seek = NULL;
	if (r == -1)
		free(ret);
	return (ret);
}

char	*seekline(int fd, t_rest *rest)
{
	char	*s;
	char	*ret;
	int		read_out;
	
	read_out = 1;
	ret = NULL;
	while (1)
	{
		if (rest->seek[0] == '\0')
		{
			read_out = read(fd, rest->root, BUFFER_SIZE);
			rest->root[read_out] = '\0';
			if (read_out <= 0)
				return (freeret(rest, read_out, ret));
			rest->seek = rest->root;
		}
		s = ft_strchr(rest->seek, DELIM);
		if (*s != '\n')
		{
			ret = ft_strmerg(ret, rest->seek);
			if (!ret)
				return (NULL);
			rest->seek = s;
		}
		else
		{
			ret = ft_strmerg(ret, rest->seek);
			rest->seek = s + 1;
			return (ret);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_rest rest[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	initbuffer(&rest[fd]);
	return (seekline(fd, &rest[fd]));
}

#ifdef MAIN
int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int fd = open("files/odyssey", O_RDONLY);
	if (fd == -1)
		return (0);
	
	for (int i = 0; i < 20; i++)
	{
		char *l = get_next_line(fd);
		printf("\nl%d {%s}\n", i, l);
		free(l);
	}
	close(fd);
	return (0);
}
#endif /* main */