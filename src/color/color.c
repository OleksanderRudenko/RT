/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:45:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/17 12:45:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int				set_spectrum_brightness(int val, double brightness,
		double bbrightness)
{
	return ((int)(val * brightness + (255 - val) * bbrightness));
}

static unsigned char	limit_spectrum(int d, int min, int max)
{
	d = d > max ? max : d;
	d = d < min ? min : d;
	return ((unsigned char)d);
}

int						set_brightness(int color, double brightness,
		double bbrightness)
{
	t_color	color_t;

	brightness += bbrightness;
	brightness = brightness > 1 ? 1 : brightness;
	bbrightness = bbrightness > 1 ? 1 : bbrightness;
	color_t.color = color;
	color_t.spectrum.red = limit_spectrum(
			set_spectrum_brightness(color_t.spectrum.red, brightness,
					bbrightness), 0, 255);
	color_t.spectrum.green = limit_spectrum(
			set_spectrum_brightness(color_t.spectrum.green, brightness,
					bbrightness), 0, 255);
	color_t.spectrum.blue = limit_spectrum(
			set_spectrum_brightness(color_t.spectrum.blue, brightness,
					bbrightness), 0, 255);
	return (color_t.color);
}
