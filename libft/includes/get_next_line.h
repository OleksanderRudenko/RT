/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 07:50:35 by abutok            #+#    #+#             */
/*   Updated: 2017/11/28 16:00:23 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <errno.h>
# define BUFF_SIZE 2000
# define IS_EOL(x) (x == '\n' || x == '\0')

typedef struct	s_buff
{
	int				owner;
	char			buff[BUFF_SIZE];
	size_t			i;
	int				is_readed;
	struct s_buff	*next;
}				t_buff;

int				get_next_line(const int fd, char **line);

#endif
