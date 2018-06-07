/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:06:45 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 11:06:47 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// unsigned int	texture_sphere(t_vector normal, SDL_Surface *texture)
// {
// 	t_color		col;
// 	Uint32		color;
// 	float		u;
// 	float		v;
// 	int x = 0;
// 	int y = 0;

// 	u = 0.5 + atan2(normal.z, normal.x) / (M_PI);
// 	v = 0.5 - asin(normal.y/2.0)/M_PI;
// 	v = v - floor(v);
// 	u = u - floor(u);
// 	SDL_LockSurface( texture );

// 	x = (int)(texture->w * u * 10.0 ) % texture->w;
// 	y = (int)(texture->h * v * 10.0 ) % texture->h;
// 	color = getcolor(texture, x ,y);

// 	SDL_GetRGB(color, texture->format, &col.r, &col.g, &col.b);

// 	SDL_UnlockSurface( texture );

// 	// color = (col.r << 16 | col.g << 8 | col.b);
// 	return (col.r << 16 | col.g << 8 | col.b);
// }

// Uint32		getcolor(SDL_Surface *texture, int x, int y)
// {
// 	Uint8			*pixel;
// 	unsigned int	sz;

// 	sz = sizeof(Uint32);
// 	pixel = (Uint8*)texture->pixels;
// 	pixel += ((Uint32)y * (Uint32)texture->pitch) + ((Uint32)x * texture->format->BytesPerPixel);
// 	return (*((Uint32*)pixel));
// }

// static float3 negative(float3 col)
// {
// 	return ((float3)(1,1,1) - cbrt(col));
// }