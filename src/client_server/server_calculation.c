/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 21:08:49 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:46:09 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		server_init_help(t_view *view)
{
	bool tmp;

	tmp = true;
	if (setsockopt(view->socket, SOL_SOCKET,
		SO_REUSEADDR, &tmp, sizeof(int)) < 0)
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, exit);
	if ((view->sock_for_connect = accept(view->socket,
		(struct sockaddr *)0, 0)) < 0)
	{
		close(view->socket);
		write(1, "Could not open a socket to accept data\n", 21);
		exit(EXIT_FAILURE);
	}
	if (setsockopt(view->sock_for_connect, SOL_SOCKET,
		SO_REUSEADDR, &tmp, sizeof(int)) < 0)
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}
}

void			server_init(t_view *view)
{
	memset(&view->addr, 0, sizeof(view->addr));
	view->addr.sin_family = AF_INET;
	view->addr.sin_port = htons(PORT);
	view->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((view->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		write(1, "Could not create listen socket\n", 31);
		exit(EXIT_FAILURE);
	}
	if ((bind(view->socket, (struct sockaddr *)&view->addr,
			sizeof(view->addr))) < 0)
	{
		write(1, "Could not bind socket\n", 22);
		exit(EXIT_FAILURE);
	}
	if (listen(view->socket, 1) < 0)
	{
		write(1, "Could not open socket for listening\n", 36);
		exit(EXIT_FAILURE);
	}
	server_init_help(view);
}

void			server_send_get_info(t_view *view)
{
	unsigned char	*serialize;

	serialize = malloc(sizeof(unsigned char) * SER_SIZE);
	while (view->exit_loop)
	{
		if (!poll_event(view))
			view->exit_loop = 0;
		SDL_UpdateWindowSurface(view->win[0]);
		if (recv_all(view->sock_for_connect, serialize, SER_SIZE) == false)
		{
			write(1, "No connection from client "
			"when receving data. Exiting...\n", 61);
			exit(EXIT_FAILURE);
		}
		unpack(serialize, view);
		opencl_init2(view);
		if (send_all(view->sock_for_connect, view->buff,
			view->cl.buffers_size) == false)
		{
			write(1, "No connection from client "
			"when sending data. Exiting...\n", 60);
			exit(EXIT_FAILURE);
		}
	}
	free(serialize);
}
