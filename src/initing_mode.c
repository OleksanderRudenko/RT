/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 00:50:07 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 03:37:11 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initing_mode(t_view *view)
{
	if (view->server_client == Server)
	{
		poll_event(view);
		// button_staff(view);
		// what_to_print(view);
		server_init(view);
		server_send_get_info(view);
	}
	else if (view->server_client == Client)
	{
		client_init(view);
		while (view->exit_loop == 1)
		{
			if (!poll_event(view))
				view->exit_loop = 0;
			client_send_get_info(view);
			button_staff(view);
			what_to_print(view);
			SDL_UpdateWindowSurface(view->win[0]);
		}
		cl_releasing(view);
		clean_staff(view);
	}
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
	system("leaks RT");
}
