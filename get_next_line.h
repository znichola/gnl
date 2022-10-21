/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:33 by znichola          #+#    #+#             */
/*   Updated: 2022/10/21 19:54:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

# define BUFFER_SIZE 13
# define DELIM '\n'

typedef enum
{
	error,
	malloc_error,
	success,
	file_end,
	full_buff,
	half_buff,
	line_complete,
	line_incomplete,
}		t_ret;

t_ret	process_chunk(char **chunk, char **split_chunk);
char	*get_next_line(int fd);
t_ret	process_buffer(char **strs, char **buff, char **ret, ssize_t r);
t_ret	fill_buffer(int fd, char *b, ssize_t *r);
t_ret	find_line(int fd, char **strs, char *buff, char **ret);

// utils
char	*ft_nextword(char **str, char const c);
size_t	ft_strlen(const char *s);
char	*ft_strpmerg(char *s1, char *s2, char *s3);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
char	*ft_strndup(const char *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif /* get_next_line*/
