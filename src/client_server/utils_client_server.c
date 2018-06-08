/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client_server.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 16:50:46 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:46:55 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool			recv_all(int socket, void *buffer, size_t length)
{
	int			size_of_message;
	char		*ptr;

	ptr = (char *)buffer;
	while (length > 0)
	{
		size_of_message = recv(socket, ptr, length, 0);
		if (size_of_message == 0)
			return (true);
		else if (size_of_message == -1)
			return (false);
		ptr += size_of_message;
		length -= size_of_message;
	}
	return (true);
}

bool			send_all(int socket, void *buffer, size_t length)
{
	int			size_of_message;
	char		*ptr;

	ptr = (char *)buffer;
	while (length > 0)
	{
		size_of_message = send(socket, ptr, length, 0);
		if (size_of_message == 0)
			return (true);
		else if (size_of_message == -1)
			return (false);
		ptr += size_of_message;
		length -= size_of_message;
	}
	return (true);
}

void			pack(unsigned char *buff, t_view *view)
{
	serialize_double(&buff, view->space->cam->o.x);
	serialize_double(&buff, view->space->cam->o.y);
	serialize_double(&buff, view->space->cam->o.z);
	serialize_double(&buff, view->space->cam->v.x);
	serialize_double(&buff, view->space->cam->v.y);
	serialize_double(&buff, view->space->cam->v.z);
}

void			unpack(unsigned char *buff, t_view *view)
{
	view->space->cam->o.x = deserialize_double(&buff);
	view->space->cam->o.y = deserialize_double(&buff);
	view->space->cam->o.z = deserialize_double(&buff);
	view->space->cam->v.x = deserialize_double(&buff);
	view->space->cam->v.y = deserialize_double(&buff);
	view->space->cam->v.z = deserialize_double(&buff);
}

void			fill_half_scr(unsigned int *half_scr, t_view *view)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		if (y >= HEIGHT / 2)
		{
			x = 0;
			while (x < WIDTH)
			{
				view->buff[y * WIDTH + x] = half_scr[y * WIDTH + x];
				x++;
			}
		}
		y++;
	}
}
