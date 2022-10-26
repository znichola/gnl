/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:33 by znichola          #+#    #+#             */
/*   Updated: 2022/10/26 06:26:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

// #define MAIN

// # ifdef MAIN
// #  define PRINT
// #  define BUFFER_SIZE 13
// # endif /* main */

# define DELIM '\n'

typedef enum e_action
{
	initialise,
	liberate
}		t_action;

# define LINE_FOUND 1U
# define END_OF_FILE 2U
# define LINE_INCOMPLETE 4U
# define MALLOC_ERROR 8U

typedef struct s_rest
{
	char	*root;
	char	*seek;
}	t_rest;

/* get_net_line */
char	*get_next_line(int fd);

/* gnl_utils */
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
char	*ft_strmerg(char *rest, char *buff);

char	*ft_buffmerg(char *s, char *buff);

#endif /* get_next_line*/
