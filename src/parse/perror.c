/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:02:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/04/17 14:08:56 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	root_parse_error(t_view *view)
{
	if (errno)
		perror("File reading error");
	else
		ft_putendl("Invalid JSON file");
	exit_x(view);
}
