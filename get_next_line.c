/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:11 by znichola          #+#    #+#             */
/*   Updated: 2022/10/25 18:08:34 by znichola         ###   ########.fr       */
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
		if (!(b = ft_strjoin(*ret, *buff)))
			return (error2);
	}
	else
	{
		if (!(b = ft_strdup(++a)))
			return (error2);
		*a = '\0';
		a = b;
		if (!(b = ft_strjoin(*ret, *buff)))
		{
			free(a);
			return (error2);
		}
		if (!*strs)
			free(*strs);
		*strs = a;
	}
	free(*ret);
	*ret = NULL;
	*ret = b;
	return (line_incomplete);
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

t_ret	fill_buffer2(int fd, char *b, ssize_t *r)
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
		(void)r;
		(void)fd;
		// fill = fill_buffer(fd, buff, &r);
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

// char	*get_next_line(int fd)
// {
// 	static	char *rest[4096];
// 	char	*buff;
// 	char	*ret;
// 	t_ret	f;
	
// 	if (!managment(fd, &buff, &ret))
// 		return (NULL);
	
// 	f = process_stored(&rest[fd], &ret, &buff);
// 	if (f == line_complete)
// 		return (ret);
// 	if (f == error2)
// 		return (NULL);
// 	f = find_line(fd, &rest[fd], buff, &ret);
// 	if (f == error2)
// 		return (NULL);
// 	else if (f == file_end)
// 	{
// 		// free(rest[fd]);
// 		rest[fd] = NULL;
// 	}
// 	free(buff);
// 	if (!*ret)
// 	{
// 		free(ret);
// 		return (NULL);
// 	}
// 	return (ret);
// }

void error_print(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	#ifdef PRINT
	vfprintf(stdout, fmt, ap);
	#endif
	va_end(ap);
}

char	*freeret(char *stat, char *z)
{

	if (!stat)
	{
		free(stat);
		stat = NULL;
	}
	if (!z)
		free(z);
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
		error_print("I malloc-ed the seekbuffer:%p\n", s->root);
		s->s = s->root;
	}
	// printf("root:%p seek:%p diff:%d	", s->root, s->s, (int)(s->s - s->root));
	s->s = ft_strchr(s->s, DELIM);
	if (!s->s || s->s - s->root >= BUFFER_SIZE)
	{
		s->s = s->root;
		
		ft_bzero(s->root, BUFFER_SIZE + 1);
		int foo = read(fd, s->root, BUFFER_SIZE);
		// printf("read output:%d\n", foo);
		if (foo < 0)
		{
			error_print("I freed s->root:%p\n", s->root);
			return (freeret(s->root, NULL));
		}
			// return (NULL); // need to free s->root also.
		else if (foo == BUFFER_SIZE)
			*ret = buffer_filled;
		else if (foo >= 0)
		{
			// printf("end of fileadasdasdasdsasd\n");
			// s->root[foo] = 'g';
			// s->s = s->root;
			*ret = end_of_file;
		}
	}
	if (*ret == end_of_file && *(s->s) != DELIM)
		; //printf("real end of file\n"); // misiing a case when the file does not end with a \n
		// return (NULL);
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
	char *ret = (char *)calloc(1, 1);
	error_print("I malloc-ed ret:%p\n", ret);
	int bar = 1;

	while (r != line_found && r != end_of_file && r != malloc_error2)
	{
		char *buff = seekbuffer(fd, &rest[fd], &r);
		if (!buff)
		{
			// freeret(rest[fd].root, ret);
			error_print("I freed the seek buffer:%p and ret%p\n", rest[fd].root, ret);
			freeret(rest[fd].root, ret);
			// free(rest[fd].root);
			// free(ret);
			// rest[fd].root = NULL;
			return (freeret(rest[fd].root, ret));
		}
		// printf("\nreturn[%d] seekbuffer{%s} end of line:%d\n", r, buff, r);
		ret = ft_buffmerg(ret, buff);
		if (!ret)
			return (freeret(NULL, buff));
		if (!ret && ft_strchr(ret, DELIM)) //|| *buff != '\0')
			r = line_found;
		// else
		// 	return (ret);
		if (r == end_of_file)
		{
			if (bar == 1)
				// printf("br is 2\n");
			bar = 2;
			// printf("this is the end of the file. baby\n");
			// printf("buff{%s}\n", buff);
			// printf("buff2{%s}\n", rest[fd].root);
			// printf("free bufff\n");
			// buff = NULL;
			// return (ret);
			error_print("I freed the seek buffer:%p\n", rest[fd].root);
			free(rest[fd].root);
			rest[fd].root = NULL;
			return (NULL);
		}
	}
	// if (r == end_of_file)
	// {
	// 	// printf("end of file\n");
	// 	free(rest[fd].root);
	// }
	// if (*ret == '\0')
	// {
	// 	return (freeret(ret));
	// 	// free(ret);
	// 	// return (NULL);
	// }
	return (ret);
	
	// char *buff = seekbuffer(fd, &rest[fd], &r);
}

#ifdef MAIN
int main(void)
{
	// (void)argc;
	// (void)argv;
	char *tst = "this_is_add_very_long_string";

	printf("\nsubsstr{%s}\n", ft_subsstr(tst, tst+50));

	int fd = open("files/empty", O_RDONLY);
	char *ret = (char *)malloc(1);
	*ret = '\0';
	// fd = 1000;
	// close(fd);
	for (int i = 0; i < 3; i++)
	{
		// static t_rest rest[4096];
		// t_return r = unmodified;
		// char *buff = seekbuffer(fd, &rest[fd], &r);
		// // printf("\nreturn[%d] seekbuffer{%s}\n", r, buff);
		// ret = ft_buffmerg(ret, buff);
		// if (ft_strchr(ret, DELIM))
		// {
		// 	printf("l%d r:%d\n{%s}\n", i, r, ret);
		// }
		// if (r == buffer_advanced)
		// printf("\nbar:{%s}\n", bar);
		// ret = seekbuffer(fd, &rest[fd], &r);

		// char *l = gnl(fd);
		char *l = get_next_line(fd);
		printf("\nl%d {%s}\n", i, l);
		free(l);
	}
	close(fd);
	return (0);
}
#endif /* main */