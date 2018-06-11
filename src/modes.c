/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 01:29:30 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/11 20:44:59 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_mode(t_view *view)
{
	if (view->server_client == Server)
		server_send_get_info(view);
	else
	{
		while (view->exit_loop == 1)
		{
			if (!poll_event(view))
				view->exit_loop = 0;
			button_staff(view);
			what_to_print(view);
			SDL_UpdateWindowSurface(view->win[0]);
		}
		cl_releasing(view);
		clean_staff(view);
	}
}

void	initing_mode(t_view *view, const char *const filename)
{
	if (view->server_client == Server)
	{
		poll_event(view);
		button_staff(view);
		what_to_print(view);
		server_init(view);
		check_server(view, filename);
	}
	else if (view->server_client == Client)
	{
		client_init(view);
		check_client(view, filename);
		client_send_get_info(view);
	}
}
