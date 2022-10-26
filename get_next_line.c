/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 02:28:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	seekline(int fd, char **rest)
{
	int	r;
	char	buff[BUFFER_SIZE + 1];
	char	*s;

	s = ft_strchr(*rest, DELIM);
	r = 1;
	while (!s && r)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r && !*rest)
			*rest = ft_buffmerg(NULL, buff);
	}
	return (0);
}

#ifdef MAIN
int main(void)
{
	int fd = open("files/odyssey", O_RDONLY);
	static char *rest[1024];

	// char *ret = (char *)calloc(1, 1);
	// char *foo = "foo\nbar";

	for (int i = 0; i < 3; i++)
	{
		// char *ret = (char *)calloc(1, 1);
		
		int r = seekline(fd, &rest[fd]);
		printf("\nl%d r:%d {%s}\n", i, r, rest[fd]);
		
		// char *l = get_next_line(fd);
		// printf("\nl%d {%s}\n", i, l);
		// free(l);
	}
	close(fd);
	return (0);
}
#endif /* main */