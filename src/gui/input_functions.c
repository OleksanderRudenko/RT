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

double		par_input()
{
	const char	*input;
	float		num;

	input = tinyfd_inputBox("", "Click something", "0");
	if (input == NULL)
		return (0.0);
	num = atof(input);
	printf("input num: %f\n", num);/*for debug*/
	return (num);
}

int		mirror_val()
{
	const char	*input;
	int		num;

	input = tinyfd_inputBox("", "Mirror or not ?", "0");
	if (input == NULL)
		return (0.0);
	num = atof(input);
	if (num > 1)
		return (1);
	else if (num < 0)
		return (0);
	printf("mirror input num: %d\n", num);/*for debug*/
	return (num);
}

// int		rot_input()
// {
// 	const char	*input;
// 	int		num;

// 	input = tinyfd_inputBox("", "Mirror or not ?", "0");
// 	if (input == NULL)
// 		return (0.0);
// 	num = atof(input);
	
// 	printf("mirror input num: %d\n", num);/*for debug*/
// 	return (num);
// }