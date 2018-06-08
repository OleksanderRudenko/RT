/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 00:50:07 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:22:41 by vvinogra         ###   ########.fr       */
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
	// system("leaks RT");
}

void	initing_mode(t_view *view, const char * const filename)
{
	if (view->server_client == Server)
	{
		poll_event(view);
		// button_staff(view);
		// what_to_print(view);
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
