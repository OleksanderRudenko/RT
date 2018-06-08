/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unserialize_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 00:35:59 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/08 22:16:20 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				deserialize_int(unsigned char **buffer)
{
	int value;

	value = 0;
	value |= (*buffer)[0] << 24;
	value |= (*buffer)[1] << 16;
	value |= (*buffer)[2] << 8;
	value |= (*buffer)[3];
	*buffer += sizeof(int);
	return (value);
}

char			deserialize_char(unsigned char **buffer)
{
	*buffer += 1;
	return (*buffer)[0];
}

double			deserialize_double(unsigned char **buffer)
{
	int			i;
	t_double	u;

	i = 0;
	while (i < 8)
	{
		u.bytes[i] = (*buffer)[i];
		i++;
	}
	*buffer += 8;
	return (u.value);
}
