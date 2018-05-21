/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/16 17:48:13 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 	 	checkerboard_effect(t_view *v, int color)
{
	int 	x;
	int 	y;
	int 	i;
	int 	size = WIDTH * HEIGHT;
	int 	scale = 5;
	int 	checker = 0;
	int 	line = 0;
	int 	j;

	y = -1;
	while (++y < HEIGHT)
	{
		if (line == 0)
		{
			x = -1;
			line = 1;
		}
		else
		{
			x = scale;
			line = 0;
		}
		printf("line->%i\n", line);
		while (++x < WIDTH)
		{
			if (y == 0)
				i = y * WIDTH + x;
			else
				i = y * WIDTH + x - 1;
			if (checker == 0)
			{
				int g;
				j = -1;
				while (++j <= scale)
				{
					g = -1;
					while (++g <= scale && (i + g) % WIDTH < WIDTH)
							v->buff[i + g] = 0;
					i += WIDTH;
				}
				checker = 1;
				x += scale * 2;
			}
			else
				checker = 0;
			// x += scale * 2;
			// }
		}
		// if (y == scale * 2)
		//  	break ;
		y += (scale - 1);
		// if (checker == 1)
		// 	checker = 0;
		// else
		// 	checker = 1;
	}

}
