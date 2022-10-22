/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:33 by znichola          #+#    #+#             */
/*   Updated: 2022/10/22 12:29:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 13
# define DELIM '\n'

typedef enum e_ret
{
	error2,
	malloc_error,
	success,
	file_end,
	stor_end,
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
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);

#endif /* get_next_line*/
