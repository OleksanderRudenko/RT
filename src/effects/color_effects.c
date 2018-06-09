/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:49:43 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/09 17:51:02 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int	sepia(t_color *color)
{
	int	new_colors_blue;
	int	new_colors_green;
	int	new_colors_red;

	new_colors_red = (color->spectrum.red * 0.393) +
			(color->spectrum.green * 0.769) + (color->spectrum.blue * 0.189);
	new_colors_green = (color->spectrum.red * 0.349) +
			(color->spectrum.green * 0.686) + (color->spectrum.blue * 0.168);
	new_colors_blue = (color->spectrum.red * 0.272) +
			(color->spectrum.green * 0.534) + (color->spectrum.blue * 0.131);
	color->spectrum.red = new_colors_red <= 255 ? new_colors_red : 255;
	color->spectrum.green = new_colors_green <= 255 ? new_colors_green : 255;
	color->spectrum.blue = new_colors_blue <= 255 ? new_colors_blue : 255;
	return ((unsigned int)color->color);
}

static unsigned int	grayscale(t_color *color)
{
	int	new_colors_blue;
	int	new_colors_green;
	int	new_colors_red;

	new_colors_red = (color->spectrum.red * 0.21) +
				(color->spectrum.green * 0.71) + (color->spectrum.blue * 0.071);
	new_colors_green = (color->spectrum.red * 0.21) +
				(color->spectrum.green * 0.71) + (color->spectrum.blue * 0.071);
	new_colors_blue = (color->spectrum.red * 0.21) +
				(color->spectrum.green * 0.71) + (color->spectrum.blue * 0.071);
	color->spectrum.red = new_colors_red <= 255 ? new_colors_red : 255;
	color->spectrum.green = new_colors_green <= 255 ? new_colors_green : 255;
	color->spectrum.blue = new_colors_blue <= 255 ? new_colors_blue : 255;
	return ((unsigned int)color->color);
}

static unsigned int	cartoon(t_color *color)
{
	if (color->spectrum.red >= 0 && color->spectrum.red < 50)
		color->spectrum.red = 25;
	else if (color->spectrum.red >= 50 && color->spectrum.red < 100)
		color->spectrum.red = 75;
	else if (color->spectrum.red >= 100 && color->spectrum.red < 200)
		color->spectrum.red = 150;
	else if (color->spectrum.red >= 200 && color->spectrum.red < 250)
		color->spectrum.red = 225;
	if (color->spectrum.green >= 0 && color->spectrum.green < 50)
		color->spectrum.green = 25;
	else if (color->spectrum.green >= 50 && color->spectrum.green < 100)
		color->spectrum.green = 75;
	else if (color->spectrum.green >= 100 && color->spectrum.green < 200)
		color->spectrum.green = 150;
	else if (color->spectrum.green >= 200 && color->spectrum.green < 250)
		color->spectrum.green = 225;
	if (color->spectrum.blue >= 0 && color->spectrum.blue < 50)
		color->spectrum.blue = 25;
	else if (color->spectrum.blue >= 50 && color->spectrum.blue < 100)
		color->spectrum.blue = 75;
	else if (color->spectrum.blue >= 100 && color->spectrum.blue < 200)
		color->spectrum.blue = 150;
	else if (color->spectrum.blue >= 200 && color->spectrum.blue < 250)
		color->spectrum.blue = 225;
	return ((unsigned int)color->color);
}

static unsigned int	inversion(t_color *color)
{
	color->spectrum.red = 255 - color->spectrum.red;
	color->spectrum.green = 255 - color->spectrum.green;
	color->spectrum.blue = 255 - color->spectrum.blue;
	return ((unsigned int)color->color);
}

void				color_effects(t_view *view)
{
	t_color	color;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color.color = (int)view->buff[y * WIDTH + x];
			if (view->space->sepia == 1)
				view->buff[y * WIDTH + x] = sepia(&color);
			if (view->space->grayscale == 1)
				view->buff[y * WIDTH + x] = grayscale(&color);
			if (view->space->cartoon == 1)
				view->buff[y * WIDTH + x] = cartoon(&color);
			if (view->space->inversion == 1)
				view->buff[y * WIDTH + x] = inversion(&color);
			x++;
		}
		y++;
	}
}
