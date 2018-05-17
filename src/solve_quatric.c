/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quatric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:40:12 by vvinogra          #+#    #+#             */
/*   Updated: 2018/05/10 16:48:18 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double					*find_sqrt(double a, double b, double c)
{
	double des;
	double y1;
	double y2;
	double *ret;

	ret = (double *)malloc(sizeof(double) * (2));
	if (!ret)
		exit(1);
	des = pow(b, 2) - 4 * a * c;
	if (des < 0)
	{
		y1 = NAN;
		y2 = NAN;
	}
	else
	{
		y1 = (-b + sqrt(des)) / (2 * a);
		y2 = (-b - sqrt(des)) / (2 * a);
	}
	ret[0] = y1;
	ret[1] = y2;
	return (ret);
}

static t_quadric		init_quadric(const double (*nums)[5])
{
	t_quadric	quad;

	quad.a = (*nums)[0];
	quad.b = (*nums)[1];
	quad.c = (*nums)[2];
	quad.d = (*nums)[3];
	quad.e = (*nums)[4];
	quad.b /= quad.a;
	quad.c /= quad.a;
	quad.d /= quad.a;
	quad.e /= quad.a;
	quad.a /= quad.a;
	quad.ret = (double *)malloc(sizeof(double) * 4);
	if (!quad.ret)
		exit(1);
	quad.p = quad.c - ((3 * pow(quad.b, 2)) / 8);
	quad.q = pow(quad.b, 3) / 8 - quad.b * quad.c / 2 + quad.d;
	quad.r = -3 * pow(quad.b, 4) / 256 + pow(quad.b, 2) *
		quad.c / 16 - quad.d * quad.b / 4 + quad.e;
	quad.cub = find_cube_sqrt(2, -quad.p, -2 * quad.r,
		quad.r * quad.p - pow(quad.q, 2) / 4);
	return (quad);
}

double					*quadric_solver(const double (*nums)[5])
{
	t_quadric	quad;
	double		c_root;
	int			cub_roots;

	cub_roots = 2;
	quad = init_quadric(nums);
	while (cub_roots >= 0)
	{
		if (quad.cub[cub_roots] != NAN)
			c_root = quad.cub[cub_roots];
		cub_roots--;
	}
	quad.sqr = find_sqrt(1, -sqrt(2 * c_root - quad.p),
		quad.q / (2 * sqrt(2 * c_root - quad.p)) + c_root);
	quad.ret[0] = quad.sqr[0] - quad.b / 4;
	quad.ret[1] = quad.sqr[1] - quad.b / 4;
	free(quad.sqr);
	quad.sqr = find_sqrt(1, sqrt(2 * c_root - quad.p),
		-quad.q / (2 * sqrt(2 * c_root - quad.p)) + c_root);
	quad.ret[2] = quad.sqr[0] - quad.b / 4;
	quad.ret[3] = quad.sqr[1] - quad.b / 4;
	free(quad.sqr);
	free(quad.cub);
	return (quad.ret);
}
