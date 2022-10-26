/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 04:30:18 by znichola         ###   ########.fr       */
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
			// need to read from file
			//ft_bzero(rest->root, BUFFER_SIZE);
			read_out = read(fd, rest->root, BUFFER_SIZE);
			rest->root[read_out] = '\0';
			//if readout == 0 return ret rembere to free and NULL
			if (read_out <= 0)
			{
				free(rest->root);
				rest->root = NULL;
				rest->seek = NULL;
				return (ret);
			}
			rest->seek = rest->root;
			// printf("some newline{%s}\n", rest->seek);
		}
		s = ft_strchr(rest->seek, DELIM);
		// printf("here {%s}\n", s);
		if (*s != '\n')
		{
			// merg the full buffer
			ret = ft_strmerg(ret, rest->seek);
			if (!ret)
				return (NULL);
			rest->seek = s;
		}
		else
		{
			// merg the remainder of what's in the buffer
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
	// static t_rest rest[4096];
	
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