/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 19:12:01 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 19:12:07 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		delete_init_cl(t_view *s)
{
	free(s->space->cl_figures);
	free(s->space->cl_lights);
	free(s->space->cl_figtmp);
	free(s->space->cl_ligtmp);
}

void		del_list(t_view *s)
{
	t_figure	*fig;
	t_figure	*lol;
	t_light		*lit;
	t_light		*tmp;

	fig = s->space->figures;
	lit = s->space->lights;
	while (fig)
	{
		free(fig->figure);
		lol = fig->next;
		free(fig);
		fig = lol;
	}
	while (lit)
	{
		tmp = lit->next;
		free(lit);
		lit = tmp;
	}
	s->space->figures = NULL;
	s->space->lights = NULL;
	free(s->space->cam);
	free(s->space);
}

int			select_num(t_view *s)
{
	int			type;

	type = s->space->cl_figures[s->rr.fl.y].type;
	if (type == InfinitePlane)
		return (NUM_PL_PR);
	else if (type == Sphere)
		return (NUM_SP_PR);
	else if (type == InfiniteCylinder)
		return (NUM_IC_PR);
	else if (type == InfiniteCone)
		return (NUM_CN_PR);
	else if (type == Triangle)
		return (NUM_TR_PR);
	else if (type == Cube)
		return (NUM_CU_PR);
	else if (type == Quadrate)
		return (NUM_QUA_PR);
	else if (type == Elipsoid)
		return (NUM_EL_PR);
	else if (type == Parabaloid)
		return (NUM_PR_PR);
	return (-1);
}

char		*ft_ftoa(double value)
{
	int			nb;
	char		*arr;
	char		*arr2;
	int			point_part;
	char		*tmp;

	nb = (int)value;
	arr = ft_itoa(nb);
	ft_strcat(arr, ".");
	point_part = (value - nb) * 100;
	point_part = point_part < 0 ? point_part * -1 : point_part;
	arr2 = ft_itoa(point_part);
	tmp = arr;
	arr = ft_strjoin(arr, arr2);
	free(arr2);
	free(tmp);
	return (arr);
}

SDL_Rect	*select_rect(t_view *s)
{
	int			type;

	type = s->space->cl_figures[s->rr.fl.y].type;
	if (type == InfinitePlane)
		return (s->pl.pl_pr_rect);
	else if (type == Sphere)
		return (s->prop.pr_rect);
	else if (type == InfiniteCylinder)
		return (s->ic.ic_pr_rect);
	else if (type == InfiniteCone)
		return (s->con.cn_pr_rect);
	else if (type == Triangle)
		return (s->tri.tri_pr_rect);
	else if (type == Cube)
		return (s->cub.cu_pr_rect);
	else if (type == Quadrate)
		return (s->qua.qu_pr_rect);
	else if (type == Elipsoid)
		return (s->elp.el_pr_rect);
	else if (type == Parabaloid)
		return (s->par.pr_pr_rect);
	return (NULL);
}
