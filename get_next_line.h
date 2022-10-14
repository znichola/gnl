/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:33 by znichola          #+#    #+#             */
/*   Updated: 2022/10/14 16:02:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEST_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 2024

char	*get_next_line(int fd);

#endif /* get_next_line*/