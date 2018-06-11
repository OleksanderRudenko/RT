/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:23:37 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 12:23:42 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	par_input(void)
{
	const char	*input;
	float		num;

	num = 0.0;
	input = tinyfd_inputBox("", "Click something", "0");
	if (input == NULL)
		return (num);
	num = atof(input);
	return (num);
}

int		mirror_val(void)
{
	const char	*input;
	int			num;

	input = tinyfd_inputBox("", "Mirror or not ?", "0");
	if (input == NULL)
		return (0.0);
	num = atof(input);
	if (num > 1)
		return (1);
	else if (num < 0)
		return (0);
	return (num);
}

int		texture_val(void)
{
	const char	*input;
	int			num;

	input = tinyfd_inputBox("", "Texture or not ?", "0");
	if (input == NULL)
		return (0.0);
	num = atof(input);
	if (num > 5)
		return (1);
	else if (num < 0)
		return (0);
	return (num);
}

int		refract_val(void)
{
	const char	*input;
	int			num;

	input = tinyfd_inputBox("", "Refract or not ?", "0");
	if (input == NULL)
		return (0.0);
	num = atof(input);
	if (num > 100 && num < -100)
		return (0);
	return (num);
}