/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_prop2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 10:34:03 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 10:34:05 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cube_prop3(t_view *s)
{
	s->cub.cu_rect[8] = make_rect(10, 600, 70, 32);
	s->cub.cu_tex[8] = create_text(s, "Scale-Y", 2, 32);
	s->cub.cu_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->cub.cu_pr[8] = tf(s, 0, 2, 32);
	s->cub.cu_rect[9] = make_rect(10, 650, 70, 32);
	s->cub.cu_tex[9] = create_text(s, "Scale-Z", 2, 32);
	s->cub.cu_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->cub.cu_pr[9] = tf(s, 0, 2, 32);
	s->cub.cu_rect[10] = make_rect(10, 700, 60, 32);
	s->cub.cu_tex[10] = create_text(s, "Mirror", 2, 32);
	s->cub.cu_pr_rect[10] = make_rect(120, 700, 60, 32);
	s->cub.cu_pr[10] = tf(s, 0, 2, 32);
	s->cub.cu_rect[11] = make_rect(10, 750, 100, 32);
	s->cub.cu_tex[11] = create_text(s, "Texture-id", 2, 32);
	s->cub.cu_pr_rect[11] = make_rect(120, 750, 60, 32);
	s->cub.cu_pr[11] = tf(s, 0, 2, 32);
}
