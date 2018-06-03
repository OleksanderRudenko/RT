
#include "rt.h"

// t_figure			quadrate_init(t_vector vector[2], int color, double reflection)
// {
//   t_figure  *new_figure;
//   t_quadric *squad;
//
//   new_figure = (t_figure*)malloc(sizeof(t_figure));
//   squad = (t_quadric*)malloc(sizeof(t_quadric));
//   new_figure->type = Quadrate;
// 	new_figure->figure = squad;
//
// }

t_squard *find_q_dots(t_squard *q)
{
	t_vector	tmp_x;
	t_vector	tmp_y;
	t_vector	tmp_z;

	// tmp_x = vk_multiple(get_default_vector('x'), k_x * cube->scale.x);
  tmp_x = (t_vector){0, 0, 0};
	tmp_y = vsum(tmp_x, vk_multiple(get_default_vector('y'), q->scale[0]));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[0] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[1] = tmp_z;
	tmp_y = vsub(tmp_x, vk_multiple(get_default_vector('y'), q->scale[0]));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[3] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[2] = tmp_z;
	return (q);
}

t_squard *calc_quadrate_params(t_squard *q)
{
  int i;

  i = 0;
  q = find_q_dots(q);
  q->rotation = vk_multiple(q->rotation, 3.14f / 180);
  while (i < 4)
  {
    rotate_x(&q->points[i], q->rotation.x);
    rotate_y(&q->points[i], q->rotation.y);
    rotate_z(&q->points[i], q->rotation.z);
    q->points[i] = vsum(q->points[i], q->position);
    ++i;
  }
  q->normale = count_triangle_normale(q->points);
	return (q);
}

t_figure 	*quadrate_init(t_vector rotation, t_vector position, double scale[2])
{
	t_figure *quadr;
	t_squard *q;

	quadr = (t_figure*)malloc(sizeof(t_figure));
	q = (t_squard*)malloc(sizeof(t_squard));
  q->rotation = rotation;
  q->position = position;
  q->scale[0] = scale[0];
  q->scale[1] = scale[1];
  q = calc_quadrate_params(q);
	// printf("%f, %f, %f-t_points0\n", figures[n].t_points[0].x, figures[n].t_points[0].y, figures[n].t_points[0].z);
	// printf("%f, %f, %f-t_points1\n", figures[n].t_points[1].x, figures[n].t_points[1].y, figures[n].t_points[1].z);
	// printf("%f, %f, %f-t_points2\n", figures[n].t_points[2].x, figures[n].t_points[2].y, figures[n].t_points[2].z);
	// printf("%f, %f, %f-normale\n", figures[n].normale.x, figures[n].normale.y, figures[n].normale.z);
	// q->points[0] = (t_vector){0, 0, 0};
	// q->points[1] = (t_vector){1, 1, 1};
	// q->points[2] = (t_vector){2, 2, 2};
	// q->points[3] = (t_vector){3, 3, 3};
	// q->scale[0] = scale[0];
	// q->scale[1] = scale[1];
	// q->normale = normale;
	quadr->figure = q;
	quadr->type = Quadrate;
	quadr->next = NULL;
	return (quadr);
}
// t_figure	*cube_init(t_ray *pnr, t_vector scale, int color, double reflection)
// {
// 	t_figure	*new_figure;
// 	t_cube		*cube;
//
// 	new_figure = (t_figure*)malloc(sizeof(t_figure));
// 	cube = (t_cube*)malloc(sizeof(t_cube));
// 	new_figure->type = Cube;
// 	new_figure->figure = cube;
// 	cube->position = pnr->o;
// 	cube->rotation = pnr->v;
// 	cube->scale = scale;
// 	count_planes(cube);
// 	new_figure->color = color;
// 	new_figure->reflection = reflection;
// 	new_figure->next = NULL;
// 	free(pnr);
// 	return (new_figure);
// }
