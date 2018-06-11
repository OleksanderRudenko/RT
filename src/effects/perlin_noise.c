/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/11 19:20:35 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

double			perlin(t_perlin *p, double x, double y, double z)
{
	static int	*permutation = NULL;
	int			i;

	srand(time(0));
	if (!(permutation))
	{
		permutation = (int*)malloc(sizeof(int) * 512);
		i = -1;
		while (++i < 512)
			permutation[i] = rand() % 256;
	}
	p->unit[0] = (int)x & 255;
	p->unit[1] = (int)y & 255;
	p->unit[2] = (int)z & 255;
	p->location[0] = x - (int)x;
	p->location[1] = y - (int)y;
	p->location[2] = z - (int)z;
	p->faded[0] = fade(p->location[0]);
	p->faded[1] = fade(p->location[1]);
	p->faded[2] = fade(p->location[2]);
	hash(permutation, p->unit, p->hashed);
	return (perlin2(p->hashed, p->faded, p->location));
}

double			octave_perlin(t_perlin *p, double x, double y, double z)
{
	double	total;
	double	max_value;
	int		i;

	p->persistence = 1;
	p->octaves = 4;
	p->frequency = 8;
	p->amplitude = 128;
	total = 0;
	max_value = 0;
	i = -1;
	while (++i < p->octaves)
	{
		total += perlin(p, x * p->frequency, y * p->frequency,
							z * p->frequency) * p->amplitude;
		max_value += p->amplitude;
		p->amplitude *= p->persistence;
		p->frequency *= 2;
	}
	return (total / max_value);
}

unsigned int	*perlin_noise(void)
{
	t_perlin	p;
	int			y;
	int			x;

	y = -1;
	p.perlin_texture =
			(unsigned int*)malloc(sizeof(unsigned int) * (256 * 256));
	while (++y < 256)
	{
		x = -1;
		while (++x < 256)
		{
			p.p[X] += (double)x / 256.0;
			p.p_factor = 20 * octave_perlin(&p, p.p[X], p.p[Y], 0.8);
			p.color_t.spectrum.red = (255 * p.p_factor);
			p.color_t.spectrum.green = (255 * p.p_factor);
			p.color_t.spectrum.blue = (255 * p.p_factor);
			p.perlin_texture[y * 256 + x] = p.color_t.color;
		}
		p.p[Y] += (double)y / 256.0;
	}
	return (p.perlin_texture);
}
