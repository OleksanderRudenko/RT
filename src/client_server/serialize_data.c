/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 12:45:15 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:16:36 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			serialize_int(unsigned char **buffer, int value)
{
	(*buffer)[0] = value >> 24;
	(*buffer)[1] = value >> 16;
	(*buffer)[2] = value >> 8;
	(*buffer)[3] = value;
	*buffer += 4;
}

void			serialize_char(unsigned char **buffer, char value)
{
	(*buffer)[0] = value;
	*buffer += 1;
}

void			serialize_double(unsigned char **buffer, double value)
{
	int			i;
	t_double	u;

	i = 0;
	u.value = value;
	while (i < 8)
	{
		(*buffer)[i] = u.bytes[i];
		i++;
	}
	*buffer += 8;
}
