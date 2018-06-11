/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:51:33 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/11 21:05:34 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

# include "rt.h"

# define X 0
# define Y 1

typedef struct		s_perlin
{
	unsigned int	*perlin_texture;
	t_color			color_t;
	double			p_factor;
	int				unit[3];
	double			location[3];
	double			faded[3];
	int				hashed[8];
	double			p[2];
	double			frequency;
	double			amplitude;
	double			octaves;
	double			persistence;
}					t_perlin;

double				perlin2(int *hashed, double *faded, double *f);
double				fade(double t);
void				hash(int *p, int *unit, int *hashed);

#endif
