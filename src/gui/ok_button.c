/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:00:35 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/15 15:00:38 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ok_button_init(t_view *s)
{
	s->ok = (t_ok *)malloc(sizeof(t_ok));

	s->ok->b_ok = get_tex("img/ok.bmp", s->rr.rend[2]);
	s->ok->ok_rect = make_rect(100, 800, 100, 50);
}

void		xxx(int num, t_view *s)
{
	// t_figure	*fig;

	// fig = detect_figure(s);
	// num == 0 ? fig->center.x = par_input(s) : 0;
	// num == 1 ? fig->center.y = par_input(s) : 0;
	// num == 2 ? fig->center.z = par_input(s) : 0;
	// init_sphere_prop(s, fig->figure, fig);
}

static void	apply_params_sphere(t_view *s, t_figure *fig, t_sphere *sphere)
{
	fig->color = color_unite(s->sl[0]->clr.red, s->sl[1]->clr.green, s->sl[2]->clr.blue);
	// sphere->center.x = s->data->center.x;
	// sphere->center.y = s->data->center.y;
}

double		par_input()
{
	const char	*input;
	float		num;

	input = tinyfd_inputBox("", "Click something", "0");
	num = atof(input);
	printf("input num: %f\n", num);
	return (num);
}

void	ok_button_function(t_view *s, SDL_Event e)
{
	t_figure	*fig;

	if (is_in_rect(s->ok->ok_rect, e))
	{
		fig = detect_figure(s);
		if (fig->type == Sphere)
			apply_params_sphere(s, fig, fig->figure);
		// else if ()
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		do_rt(s);
		ft_putendl("here");
	}
}

t_figure	*detect_figure(t_view *s)
{
	t_figure	*fig;
	int			i;

	fig = s->space->figures;
	if (fig == NULL)
		return (NULL);
	i = -1;
	while (++i < s->rr.fl.y)
			fig = fig->next;
	return (fig);
}
