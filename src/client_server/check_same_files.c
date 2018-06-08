/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_same_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:52:06 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:44:17 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*get_file_content(const char *const filename)
{
	int			fd;
	size_t		len;
	char		*file_content;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		write(1, "Wrong filename\n", 15);
		exit(EXIT_FAILURE);
	}
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(file_content = (char *)malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	read(fd, file_content, len);
	file_content[len] = 0;
	close(fd);
	return (file_content);
}

void		check_server(t_view *view, const char *const filename)
{
	char			*file_content;
	int				len;

	file_content = get_file_content(filename);
	len = ft_strlen(file_content) + 1;
	if (send_all(view->sock_for_connect, &len, sizeof(int)) == false)
	{
		write(1, "No connection from server "
			"when sending data. Exiting...\n", 60);
		exit(EXIT_FAILURE);
	}
	if (send_all(view->sock_for_connect, file_content, len) == false)
	{
		write(1, "No connection from server "
			"when sending data. Exiting...\n", 60);
		exit(EXIT_FAILURE);
	}
	ft_strdel(&file_content);
}

static void	check_client_help(t_view *view, char *file_content_c, int len_s)
{
	char	*file_content_s;

	file_content_s = malloc(sizeof(char) * (len_s));
	if (recv_all(view->socket, file_content_s, len_s) == false)
	{
		write(1, "No connection from server "
			"when sending data. Exiting...\n", 60);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(file_content_s, file_content_c) != 0)
	{
		write(1, "Not the same file\n", 18);
		exit(EXIT_FAILURE);
	}
	ft_strdel(&file_content_c);
	ft_strdel(&file_content_s);
}

void		check_client(t_view *view, const char *const filename)
{
	char	*file_content_c;
	int		len_c;
	int		len_s;

	file_content_c = get_file_content(filename);
	len_c = ft_strlen(file_content_c) + 1;
	if (recv_all(view->socket, &len_s, sizeof(int)) == false)
	{
		write(1, "No connection from server "
			"when sending data. Exiting...\n", 60);
		exit(EXIT_FAILURE);
	}
	if (len_s != len_c)
	{
		write(1, "Not the same file\n", 18);
		exit(EXIT_FAILURE);
	}
	check_client_help(view, file_content_c, len_s);
}
