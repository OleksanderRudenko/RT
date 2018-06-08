/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 23:21:56 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:46:36 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		client_init_help(t_view *view)
{
	bool tmp;

	if ((view->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		write(1, "Could not create socket\n", 24);
		exit(EXIT_FAILURE);
	}
	tmp = true;
	if (setsockopt(view->socket, SOL_SOCKET,
		SO_REUSEADDR, &tmp, sizeof(int)) < 0)
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}
}

void			client_init(t_view *view)
{
	client_init_help(view);
	memset(&view->addr, 0, sizeof(view->addr));
	view->addr.sin_family = AF_INET;
	if (inet_addr(view->server_ip) == INADDR_NONE)
	{
		ft_putstr("Wrong server ip\n");
		exit(EXIT_FAILURE);
	}
	view->addr.sin_addr.s_addr = inet_addr(view->server_ip);
	view->addr.sin_port = htons(PORT);
	if (connect(view->socket, (struct sockaddr*)&view->addr,
		sizeof(view->addr)) < 0)
	{
		write(1, "Connection refused from server\n", 31);
		exit(EXIT_FAILURE);
	}
}

void			client_send_get_info(t_view *view)
{
	unsigned char	*serialize;
	unsigned int	*half_scr;

	serialize = malloc(sizeof(unsigned char) * SER_SIZE);
	pack(serialize, view);
	if (send_all(view->socket, serialize, SER_SIZE) == false)
	{
		write(1, "No connection from server "
			"when sending data. Exiting...\n", 60);
		exit(EXIT_FAILURE);
	}
	half_scr = malloc(view->cl.buffers_size);
	if (recv_all(view->socket, half_scr, view->cl.buffers_size) == false)
	{
		write(1, "No connection from server "
			"when receving data. Exiting...\n", 61);
		exit(EXIT_FAILURE);
	}
	fill_half_scr(half_scr, view);
	free(half_scr);
	free(serialize);
}
