/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 01:34:37 by znichola         ###   ########.fr       */
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

// int	seekbuffer(int fd, t_rest *rest)
// {
// 	if (initbuffer(rest) == MALLOC_ERROR)
// 		return (MALLOC_ERROR);
// 	rest->seek = ft_strchr(rest->seek, DELIM);
// 	if (rest->seek)
// 	{
// 		// found something with strchr
// 		// no need to refill the buffer
// 		return (LINE_FOUND);
// 	}
// 	// no new line with strchr
// 	// should look inside buffer for new content to return.
// 	ft_bzero(rest->root, BUFFER_SIZE + 1);
// 	rest->read_return = read(fd, rest->root, BUFFER_SIZE);
// 	rest->seek = ft_strchr(rest->root, DELIM);
// 	if (!rest->seek && rest->read_return == END_OF_FILE)
// 		return (END_OF_FILE);
// 	return (LINE_INCOMPLETE);
// }

// int	recursivebuff(int fd, t_rest rest, char *ret)
// {
// 	rest->seek = ft_strchr(rest->seek, DELIM);
// 	if (!rest->seek)
// 	{
// 		ret = ft_buffmerg(ret, rest->seek);
		
// 	}
// 	if (rest.read_return == 0 || rest->seek);
// }


// the full buffer needs to be appended to ret
// the part of the buffer only because of \n
// part of the buffer because of the \0

int	seekline(int fd, t_rest *rest, char **ret)
{
	// this will look for the next line to be printed.
	int	r;
	char	*s;
	int		saved_buffer;

	saved_buffer = 0;
	r = BUFFER_SIZE;
	s = NULL;
	int	skkked = 13;
	while (r)
	{
		s = ft_strchr(rest->seek, DELIM);
		int tmp = (int)(rest->seek - rest->root);
		// (void)tmp;
		// if ( (!s && !rest->seek[0]))
		// if (!s && rest->seek - rest->root == r)
		if (r == skkked)
		{
			// i found nothing left in the buffer, and so we read again.
			r = read(fd, rest->root, BUFFER_SIZE);
			if (r)
			{
				rest->seek = rest->root;
				skkked = 0;
				// we've read something but to process we wait for the next loop.
				// printf("we've read something but to process we wait for the next loop.\n");
				// printf("root is {%s}\n", rest->root);
			}
			else if (r == 0)
			{
				printf("file finished {%s}\n", *ret);
				return(1);
			}
			else if ((!r && !s))
			{
				// we've read nothing. or an error. 
				// printf("we've read nothing. or an error. \n");
				return (0);
			}
		}
		else if (!s && rest->seek[0])
		{
			// no \n but we have something in seek.
			// printf("no \\n but we have something in seek.\n");
			*ret = ft_buffmerg(*ret, rest->seek);
			rest->seek = ft_strchr(rest->seek, '\0');
			ft_bzero(rest->root, BUFFER_SIZE);
			// rest->seek = rest->root;
			// saved_buffer = 1;
			// rest->seek = NULL;
		}
		else if (s)
		{
			// there is a /n in the rest
			// printf(" there is a \\n in the rest\n");
			*ret = ft_buffmerg(*ret, rest->seek);
			rest->seek = s + 1;
		}
		tmp = (int)(rest->seek - rest->root);
			printf("minus!%ld	r:%d\n", rest->seek - rest->root, r);
	}
	return (1);
}

#ifdef MAIN
int main(void)
{
	int fd = open("files/odyssey", O_RDONLY);
	static t_rest rest[4096];

	for (int i = 0; i < 3; i++)
	{
		char *ret = (char *)calloc(1, 1);
		initbuffer(&rest[fd]);
		int x = seekline(fd, &rest[fd], &ret);
		printf("signal:%d ret:%d\n", rest->read_return, x);
		printf("\nl%d {%s}\n", i, rest->seek);
		
		// char *l = get_next_line(fd);
		// printf("\nl%d {%s}\n", i, l);
		// free(l);
	}
	close(fd);
	return (0);
}
#endif /* main */