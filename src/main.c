/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 01:11:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/14 15:50:41 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	view_init(t_view *view, const char *filename)
{
	printf("A\n");
	space_init(filename, view);
	printf("B\n");
	init_rect(&view->rr);
	printf("C\n");
	set_things_up(view);
	printf("D\n");
	object_init(view);
	printf("E\n");
	init_slider(view);
	printf("F\n");
	sphere_prop(view);
	printf("G\n");
	object_default_init(view);
	printf("H\n");
	select_init(view);
	printf("I\n");
	light_list_init(view);
	printf("J\n");
	ok_button_init(view);
	printf("K\n");
	// data_init(view);
	// do_rt(view);
}


int			exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_view	view;

	if (argc != 2)
	{
		ft_putstr("usage: RT scene_filename\n");
		return (0);
	}
	init_sdl(&view);
	view_init(&view, argv[1]);
	opencl_init(&view);
	while (view.exit_loop == 1)
	{
		if (!poll_event(&view))
			view.exit_loop = 0;
		// button_staff(&view);
		// print_default_text(&view);
		// what_to_print(&view);
		SDL_UpdateWindowSurface(view.win[0]);
	}
	cl_releasing(&view);
	// clean_staff(&view); /*TODO: make it good w/o segfault*/
	// system("leaks RT");

	/*destroy texture..., cleaning staff HERE*/
	return (0);
}
