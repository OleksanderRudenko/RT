/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 00:49:44 by abutok            #+#    #+#             */
/*   Updated: 2017/12/11 12:52:08 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff	*get_buff(int fd)
{
	static t_buff	*buffer_list;
	t_buff			*srch_result;

	srch_result = buffer_list;
	while (srch_result != NULL)
	{
		if (srch_result->owner == fd)
			return (srch_result);
		srch_result = srch_result->next;
	}
	srch_result = (t_buff*)malloc(sizeof(*srch_result));
	srch_result->owner = fd;
	ft_bzero(srch_result->buff, sizeof(char) * BUFF_SIZE);
	srch_result->i = 0;
	srch_result->next = buffer_list;
	srch_result->is_readed = 1;
	buffer_list = srch_result;
	return (srch_result);
}

void	ft_strnjoin(char **line, const char *str, size_t n)
{
	char *buff_str;

	if (str == NULL || line == NULL)
		return ;
	if (*line == NULL)
	{
		*line = ft_strsub(str, 0, n);
		return ;
	}
	buff_str = *line;
	*line = ft_strnew(n + ft_strlen(*line));
	ft_strcat(*line, buff_str);
	ft_strncat(*line, str, n);
	ft_strdel(&buff_str);
	return ;
}

size_t	copy_buff(t_buff *buff, char **line)
{
	size_t	i;

	buff->i += !buff->is_readed ? 1 : 0;
	i = -1;
	while (buff->i + ++i < BUFF_SIZE)
		if (buff->buff[buff->i + i] == '\n' || buff->buff[buff->i + i] == '\0')
			break ;
	ft_strnjoin(line, &(buff->buff[buff->i]), i);
	buff->is_readed = buff->i + i == BUFF_SIZE ? 1 : 0;
	buff->i = buff->is_readed ? 0 : buff->i + i;
	if (buff->is_readed)
		ft_bzero(buff->buff, sizeof(char) * BUFF_SIZE);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	t_buff	*buff;
	size_t	rv;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	buff = get_buff(fd);
	rv = 0;
	if (!buff->is_readed)
		rv += copy_buff(buff, line);
	while (buff->is_readed)
	{
		errno = 0;
		read(buff->owner, buff->buff, BUFF_SIZE);
		if (errno != 0)
			return (-1);
		rv += copy_buff(buff, line);
	}
	return (rv || buff->buff[buff->i] ? 1 : 0);
}
