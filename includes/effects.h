/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:51:33 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 14:51:35 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_CL_H
# define EFFECTS_CL_H

# include "rt.h"

# define X 0
# define Y 1

typedef struct 		s_perlin
{
	unsigned int 	*perlin_texture;
	t_color			color_t;
	double 			p_factor;
	int 			unit[3];
	double 			location[3];
	double 			faded[3];
	int 			hashed[8];
	double 			p[2];
	double 			frequency;
	double 			amplitude;
	double 			octaves;
	double 			persistence;
}					t_perlin;

double 				perlin2(int *hashed, double *faded, double *f);
double 				fade(double t);
void 				hash(int *p, int *unit, int *hashed);

#endif
