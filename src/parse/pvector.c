/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:46:09 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/08 12:46:19 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	parse_vector(JSON_Array *vector, t_vector def)
{
	size_t i;
	size_t c;

	c = json_array_get_count(vector);
	if (c != 3)
	{
		ft_putendl_fd("Wrong vector size. Default applied", STDERR_FILENO);
		return (def);
	}
	i = 0;
	while (i < c)
	{
		if (json_value_get_type(json_array_get_value(vector, i)) != JSONNumber)
		{
			ft_putendl_fd("Wrong vector format. Default applied",
					STDERR_FILENO);
			return (def);
		}
		i++;
	}
	return (vector_init(json_array_get_number(vector, 0),
			json_array_get_number(vector, 1),
			json_array_get_number(vector, 2)));
}
