/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cubic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:40:17 by vvinogra          #+#    #+#             */
/*   Updated: 2018/05/10 16:45:01 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_cubic		init_cubic(double a, double b, double c, double d)
{
	t_cubic cubic;

	cubic.ret = (double *)malloc(sizeof(double) * 3);
	if (!cubic.ret)
		exit(1);
	cubic.p = (3 * a * c - pow(b, 2)) / (3 * pow(a, 2));
	cubic.q = (2 * pow(b, 3) - 9 * a * b * c + 27 *
		pow(a, 2) * d) / (27 * pow(a, 3));
	cubic.s = pow(cubic.q, 2) / 4 + pow(cubic.p, 3) / 27;
	cubic.a = a;
	cubic.b = b;
	cubic.c = c;
	cubic.d = d;
	return (cubic);
}

static void			first_case_cubic(t_cubic cub)
{
	double f;

	if (cub.q < 0)
		f = atan(-2 * sqrt(-cub.s) / cub.q);
	else if (cub.q > 0)
		f = atan(-2 * sqrt(-cub.s) / cub.q) + M_PI;
	else
		f = M_PI / 2;
	cub.ret[0] = 2 * sqrt(-cub.p / 3) * cos(f / 3) - cub.b / cub.a / 3;
	cub.ret[1] = 2 * sqrt(-cub.p / 3) *
		cos((f + 2 * M_PI) / 3) - cub.b / cub.a / 3;
	cub.ret[2] = 2 * sqrt(-cub.p / 3) *
		cos((f + 4 * M_PI) / 3) - cub.b / cub.a / 3;
	if (cub.q == 0)
		cub.ret[2] = -cub.b / cub.a / 3;
}

static void			second_case_cubic(t_cubic cub)
{
	double f;

	if (cub.q < 0)
		f = exp(log(fabs(cub.q / 2)) / 3);
	else if (cub.q > 0)
		f = -exp(log(fabs(cub.q / 2)) / 3);
	else
		f = 0;
	cub.ret[0] = 2 * f - cub.b / cub.a / 3;
	cub.ret[1] = -f - cub.b / cub.a / 3;
	cub.ret[2] = -f - cub.b / cub.a / 3;
}

static void			third_case_cubic(t_cubic cub)
{
	double f1;
	double f2;

	if (-cub.q / 2 + sqrt(cub.s) > 0)
		f1 = exp(log(fabs(-cub.q / 2 + sqrt(cub.s))) / 3);
	else if (-cub.q / 2 + sqrt(cub.s) < 0)
		f1 = -exp(log(fabs(-cub.q / 2 + sqrt(cub.s))) / 3);
	else
		f1 = 0;
	if (-cub.q / 2 - sqrt(cub.s) > 0)
		f2 = exp(log(fabs(-cub.q / 2 - sqrt(cub.s))) / 3);
	else if (-cub.q / 2 - sqrt(cub.s) < 0)
		f2 = -exp(log(fabs(-cub.q / 2 - sqrt(cub.s))) / 3);
	else
		f2 = 0;
	cub.ret[0] = f1 + f2 - cub.b / cub.a / 3;
	cub.ret[1] = NAN;
	cub.ret[2] = NAN;
}

double				*find_cube_sqrt(double a, double b, double c, double d)
{
	t_cubic cubic;

	cubic = init_cubic(a, b, c, d);
	if (cubic.s < 0)
		first_case_cubic(cubic);
	else if (cubic.s == 0)
		second_case_cubic(cubic);
	else
		third_case_cubic(cubic);
	return (cubic.ret);
}
