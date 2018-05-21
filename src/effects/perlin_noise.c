/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/11 12:50:44 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float 		interpolate(float a, float b, float x)
{
	return (a * (1 - x) + b * x);
}

float 		noise(int x)
{
	x = pow((x << 13), x);
	return (1.0 - (x * (x * x * 15731 + 789221) + 1376312589) & 7fffffff) / 1073741824.0);
}

float 		smoothed_noise(float x)
{
	return (noise(x) / 2 + noise(x - 1) / 4 + noise(x + 1) / 4);
}

float 		interpolated_noise(float x)
{
	int 	integer_x = (int)x;
	float 	fractional_x = x - integer_x;

	float v1 = smoothed_noise(integer_x);
	float v2 = smoothed_noise(integer_x + 1);
	return interpolate(v1, v2, fractional_x);
}

float 		perlin_noise(float x)
{
	float 	total;
	float 	persistence;
	float 	frequency;
	float 	amplitude;
	int 	n;
	int 	i;

	total = 0;
	persistence = 1/4;
	n = 10;
	i = 0;
	while (i < n) {
		frequency = pow(2, i);
		amplitude = pow(persistence, i);
		total = total + interpolated_noise(x, * frequency) * amplitude;
	}
	return (total);
}
