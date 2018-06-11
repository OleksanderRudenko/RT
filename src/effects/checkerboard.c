/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:41:22 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/11 20:41:04 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		fill_square(int sqr_x, int sqr_y, unsigned int *texture)
{
	int	y;
	int	x;
	int	sqr_x_size;
	int	sqr_y_size;

	y = 0;
	sqr_x_size = sqr_x * 256 / 100;
	sqr_y_size = sqr_y * 256 / 100;
	while (y < sqr_y_size)
	{
		x = 0;
		while (x < sqr_x_size)
		{
			if (sqr_x % 2 == sqr_y % 2)
				texture[y * 256 + x] = 0;
			else
				texture[y * 256 + x] = 0xffffff;
			x++;
		}
		y++;
	}
}

static void		checkerboard_fill(int ch_w, int ch_h, unsigned int *texture)
{
	int	y;
	int	x;

	y = 0;
	while (y < ch_h)
	{
		x = 0;
		while (x < ch_w)
		{
			fill_square(x, y, texture);
			x++;
		}
		y++;
	}
}

unsigned int	*checkerboard(void)
{
	unsigned int	*texture;

	texture = (unsigned int*)malloc(sizeof(unsigned int) * (256 * 256));
	checkerboard_fill(rand() % 10 + 1, rand() % 10 + 1, texture);
	return (texture);
}
