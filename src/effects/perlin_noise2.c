/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/11 12:50:44 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

double 	fade(double t)
{
	//for smoothing final output
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

// Linear Interpolation
double 	linterpolation(double t, double a, double b)
{
	return (a + t * (b - a));
}

double 	grad(int hash, double x, double y, double z)
{
	int 	h;
	double 	u;
	double 	v;

	h = hash & 15;										  // Take the hashed value and take the first 4 bits of it (15 == 0b1111)
	u = y;
	if (h < 8 /* 0b1000 */)								  // If the most significant bit (MSB) of the hash is 0 then set u = x.  Otherwise y.
		u = x;
	if(h < 4 /* 0b0100 */)                                // If the first and second significant bits are 0 set v = y
	    v = y;
	else if(h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/)  // If the first and second significant bits are 1 set v = x
	    v = x;
	else                                                  // If the first and second significant bits are not equal (0/1, 1/0) set v = z
	    v = z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void 	hash(int *p, int *unit, int *hashed)
{
	/*function that can be used to map data of arbitrary size to data of fixed size,
	with slight differences in input data producing very big differences in output data.*/
	hashed[0] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[1] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[2] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[3] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[4] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[5] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[6] = p[p[p[unit[0]] + unit[1]] + unit[2]];
	hashed[7] = p[p[p[unit[0]] + unit[1]] + unit[2]];
}

double 	perlin2(int *hashed, double *faded, double *f)
{
	double 	ret[4];

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
