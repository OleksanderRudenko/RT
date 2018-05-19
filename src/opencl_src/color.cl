
#include "rt_h.cl"

unsigned int	set_spectrum_brightness(unsigned int val, float brightness, float bbrightness)
{
	return ((unsigned int)(val * brightness + (255 - val) * bbrightness));
}

unsigned int	limit_spectrum(int d, int min, int max)
{
	d = d > max ? max : d;
	d = d < min ? min : d;
	return ((unsigned int)d);
}

unsigned int	set_brightness(unsigned int color, float brightness, float bbrightness)
{
	t_color	color_t;

	brightness += bbrightness;
	if (brightness > 1.0f)
		brightness = 1.0f;
	if (bbrightness > 1.0f)
		bbrightness = 1.0f;
	color_t.color = color;
	color_t.chanel[2] = limit_spectrum(
			set_spectrum_brightness(color_t.chanel[2], brightness,
					bbrightness), 0, 255);
	color_t.chanel[1] = limit_spectrum(
			set_spectrum_brightness(color_t.chanel[1], brightness,
					bbrightness), 0, 255);
	color_t.chanel[0] = limit_spectrum(
			set_spectrum_brightness(color_t.chanel[0], brightness,
					bbrightness), 0, 255);
	return (color_t.color);
}
