/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_old.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/25 21:12:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_old.h"

void error_print(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	#ifdef PRINT
	vfprintf(stdout, fmt, ap);
	#endif
	va_end(ap);
}

char	*freeret(t_rest *s, char *ret)
{
	if (s->root)
	{
		error_print("fr I freed 			s->root:%p\n", s->root);
		free(s->root);
		s->root = NULL;
	}
	if (ret)
	{
		error_print("fr I freed 		ret%p\n", ret);
		free(ret);
		ret = NULL;
	}
	return (NULL);
}

char	*fill_buffer(int fd, char *b, t_return *r)
{
	int	foo;

	ft_bzero(b, BUFFER_SIZE);
	foo = read(fd, b, BUFFER_SIZE);
	// printf("foo:%d\n", foo);
	if (foo < 0)
		return (NULL);
	else if (foo == BUFFER_SIZE)
		*r = buffer_filled;
	else if (*r >= 0)
		*r = buffer_filled;
	else
		*r = end_of_file;
	return (b);
}

char	*seekbuffer(int fd, t_rest *s, t_return *ret)
{
	if (s->root == NULL) // if no buffer is already allocated
	{
		s->root = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!s->root)
		{
			*ret = malloc_error2;
			return (NULL);
		}
		error_print("I malloc-ed the seekbuffer	root:%p\n", s->root);
		s->s = s->root;
	}
	// printf("root:%p seek:%p diff:%d	", s->root, s->s, (int)(s->s - s->root));
	s->s = ft_strchr(s->s, DELIM);
	if (!s->s || s->s - s->root >= BUFFER_SIZE)
	{
		s->s = s->root;
		
		ft_bzero(s->root, BUFFER_SIZE + 1);
		int foo = read(fd, s->root, BUFFER_SIZE);
		printf("read output:%d\n", foo);
		if (foo < 0)
		{
			return (NULL);
			// return (freeret(s, NULL));
		}
		else if (foo == BUFFER_SIZE)
			*ret = buffer_filled;
		else// if (foo >= 0)
		{
			printf("end of file\n");
			*ret = foo;
		}
	}
	if (*(s->s) == DELIM)
	{
		*ret = buffer_advanced;
		s->s += 1;
	}
	return (s->s);
}


char	*get_next_line(int fd)
{
	static t_rest rest[4096];
	t_return r = unmodified;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || 0 > read(fd, NULL, 0))
		return (NULL);
	char *ret = (char *)calloc(1, 1);
	error_print("I malloc-ed the return		ret:%p {%s}\n", ret, ret);
	// int bar = 1;

	while (r != line_found && r != end_of_file && r != malloc_error2)
	{
		char *buff = seekbuffer(fd, &rest[fd], &r);
		if (!buff)
		{
			return (freeret(&rest[fd], ret));
		}
		// printf("\nreturn[%d] seekbuffer{%s} end of line:%d\n", r, buff, r);
		ret = ft_buffmerg(ret, buff);
		if (!ret)
			return (freeret(NULL, buff));
		if (ft_strchr(ret, DELIM) || r < BUFFER_SIZE) //need a condtion here to find wh
			r = line_found;
		if (r == end_of_file && r == 0)
		{
			// if (bar == 1)
			// 	// printf("br is 2\n");
			// bar = 2;
			freeret(&rest[fd], NULL);
			return (NULL);
		}
	}
	return (ret);
}

#ifdef MAIN
int main(void)
{
	int fd = open("files/empty", O_RDONLY);

	for (int i = 0; i < 3; i++)
	{
		char *l = get_next_line(fd);
		printf("\nl%d {%s}\n", i, l);
		free(l);
	}
	close(fd);
	return (0);
}
#endif /* main */