/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:21:01 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:43:59 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				view_init(t_view *view, const char *filename)
{
	space_init(filename, view);
	init_rect(&view->rr);
	set_things_up(view);
	object_init(view);
	init_slider(view);
	sphere_prop(view);
	ic_prop(view);
	plane_prop(view);
	triangle_prop(view);
	cone_prop(view);
	cube_prop(view);
	quadraate_prop(view);
	elips_prop(view);
	parab_prop(view);
	light_properties(view);
	light_am_properties(view);
	light_dir_properties(view);
	object_default_init(view);
	select_init(view);
	light_list_init(view);
}

int					exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

inline static void	usage_exit(void)
{
	ft_putstr("Usage: ./RT scene_filename [server,client server_ip]\n");
	exit(EXIT_FAILURE);
}

void				usage(t_view *view, int argc, char **argv)
{
	if (argc == 2)
		view->server_client = Normal;
	else if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "server"))
			view->server_client = Server;
		else
			usage_exit();
	}
	else if (argc == 4)
	{
		if (!ft_strcmp(argv[2], "client"))
			view->server_client = Client;
		else
			usage_exit();
		view->server_ip = ft_strdup(argv[3]);
	}
	else
		usage_exit();
}

int					main(int argc, char **argv)
{
	t_view	view;

	view.array = array_ret();
	usage(&view, argc, argv);
	init_sdl(&view);
	view_init(&view, argv[1]);
	opencl_init(&view);
	initing_mode(&view, argv[1]);
	choose_mode(&view);
	SDL_FreeSurface(view.rr.logo);
	free(view.array);
	return (0);
}
