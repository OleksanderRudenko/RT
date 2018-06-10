/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 13:49:17 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	linterpolation(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = y;
	if (h < 8)
		u = x;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void	hash(int *p, int *unit, int *hashed)
{
	hashed[0] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[1] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[2] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[3] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[4] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[5] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[6] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[7] = p[p[p[unit[0]] + unit[1]] + unit[2]];
}

double	perlin2(int *hashed, double *faded, double *f)
{
	double	ret[4];

	ret[0] = linterpolation(grad(hashed[0], f[0], f[1], f[2]),
			grad(hashed[4], f[0] - 1, f[1], f[2]), faded[0]);
	ret[1] = linterpolation(grad(hashed[1], f[0], f[1] - 1, f[2]),
			grad(hashed[5], f[0] - 1, f[1] - 1, f[2]), faded[0]);
	ret[2] = linterpolation(ret[0], ret[1], faded[1]);
	ret[0] = linterpolation(grad(hashed[2], f[0], f[1], f[2] - 1),
			grad(hashed[6], f[0] - 1, f[1], f[2] - 1), faded[0]);
	ret[1] = linterpolation(grad(hashed[3], f[0], f[1] - 1, f[2] - 1),
			grad(hashed[7], f[0] - 1, f[1] - 1, f[2] - 1), faded[0]);
	ret[3] = linterpolation(ret[0], ret[1], faded[1]);
	return (linterpolation(ret[2], ret[3], faded[2]));
}
