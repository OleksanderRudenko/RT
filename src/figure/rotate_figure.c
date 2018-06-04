
#include "rt.h"

typedef void func(cl_float3 *ps, cl_float3 *nul_dot, float l);

void	rotate_cl_x(cl_float3 *ps, float l)
{
	float ny;
	float nz;

	ny = ps->y * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->y * sin(l);
	ps->y = ny;
	ps->z = nz;
}

void	rotate_cl_y(cl_float3 *ps, float l)
{
	float nx;
	float nz;

	nx = ps->x * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->z = nz;
}

void	rotate_cl_z(cl_float3 *ps, float l)
{
	float ny;
	float nx;

	nx = ps->x * cos(l) + ps->y * sin(l);
	ny = ps->y * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->y = ny;
}

// void	rotate_p_cl_x(cl_float3 *ps, cl_float3 *nul_dot, float l)
// {
// 	float ny;
// 	float nz;
//
// 	ps->y = ny - nul_dot->y;
// 	ps->z = nz - nul_dot->z;
// 	ny = ps->y * cos(l) + ps->z * sin(l);
// 	nz = ps->z * cos(l) - ps->y * sin(l);
// 	ps->y = ny + nul_dot->y;
// 	ps->z = nz + nul_dot->z;
// }
//
// void	rotate_p_cl_y(cl_float3 *ps, cl_float3 *nul_dot, float l)
// {
// 	float nx;
// 	float nz;
//
// 	ps->x = nx - nul_dot->x;
// 	ps->z = nz - nul_dot->z;
// 	nx = ps->x * cos(l) + ps->z * sin(l);
// 	nz = ps->z * cos(l) - ps->x * sin(l);
// 	ps->x = nx + nul_dot->x;
// 	ps->z = nz + nul_dot->z;
// }
//
// void	rotate_p_cl_z(cl_float3 *ps, cl_float3 *nul_dot, float l)
// {
// 	float ny;
// 	float nx;
//
// 	ps->x = nx - nul_dot->x;
// 	ps->y = ny - nul_dot->y;
// 	nx = ps->x * cos(l) + ps->y * sin(l);
// 	ny = ps->y * cos(l) - ps->x * sin(l);
// 	ps->x = nx + nul_dot->x;
// 	ps->y = ny + nul_dot->y;
// }


void	rotate_p_cl_z(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.z = dot_rot->z;
	dot_buf.x = (dot_null->x + ((dot_rot->x - dot_null->x) * cos((angle))) -
		((dot_rot->y - dot_null->y) * sin((angle))));
	dot_buf.y = (dot_null->y + ((dot_rot->y - dot_null->y) * cos((angle))) +
		((dot_rot->x - dot_null->x) * sin((angle))));
	*dot_rot = dot_buf;
}

void	rotate_p_cl_x(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.x = dot_rot->x;
	dot_buf.y = (dot_null->y + ((dot_rot->y - dot_null->y) * cos((angle))) -
		((dot_rot->z - dot_null->z) * sin((angle))));
	dot_buf.z = (dot_null->z + ((dot_rot->z - dot_null->z) * cos((angle))) +
		((dot_rot->y - dot_null->y) * sin((angle))));
	*dot_rot = dot_buf;
}

void	rotate_p_cl_y(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.y = dot_rot->y;
	dot_buf.z = (dot_null->z + ((dot_rot->z - dot_null->z) * cos((angle))) -
		((dot_rot->x - dot_null->x) * sin((angle))));
	dot_buf.x = (dot_null->x + ((dot_rot->x - dot_null->x) * cos((angle))) +
		((dot_rot->z - dot_null->z) * sin((angle))));
	*dot_rot = dot_buf;
}












void calc_rot_sq(t_cl_figure *figure, float angle, func *rot_func)
{
	int i;
	cl_float3 null_vec;

	null_vec = (cl_float3){0, 0, 0};
	rot_func(&(figure->q_points[0]), &(figure->position), angle);
	rot_func(&(figure->q_points[1]), &(figure->position), angle);
	rot_func(&(figure->q_points[2]), &(figure->position), angle);
	rot_func(&(figure->q_points[3]), &(figure->position), angle);
	rot_func(&(figure->normale), &null_vec, angle);
}


void calc_rot_cube(t_cl_figure *figure, float angle, func *rot_func)
{
	int i;
	cl_float3 null_vec;

	null_vec = (cl_float3){0, 0, 0};
	i = 0;
	while (i < 6)
	{
		rot_func(&(figure->c_points[i * 4]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 1]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 2]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 3]), &(figure->position), angle);
		rot_func(&(figure->c_normale[i]), &null_vec, angle);
		i++;
	}
}


void rots(t_cl_figure *figure, float angle, func *rot_func)
{
	cl_float3 null_vec;

	null_vec = (cl_float3){0, 0, 0};
  if (figure->type == InfiniteCone || figure->type == InfiniteCylinder || figure->type == InfiniteCone)
    rot_func(&(figure->vector), &null_vec, angle);
  else if (figure->type == Elipsoid || figure->type == Parabaloid)
    rot_func(&(figure->rotation), &null_vec, angle);
  else if (figure->type == InfinitePlane)
    rot_func(&(figure->normale), &null_vec, angle);
	else if (figure->type == Cube)
		calc_rot_cube(figure, angle, rot_func);
	else if (figure->type == Quadrate)
		calc_rot_sq(figure, angle, rot_func);
	else
    printf("This figure cant rotate yet\n");
}

void rotate_figures(t_cl_figure *figure, float angle, int id)
{
  static func*  rot_arr[3] =
  {
    rotate_p_cl_x,
    rotate_p_cl_y,
    rotate_p_cl_z
  };
  if (id == 0 || id == 1 || id == 2)
  {
    rots(figure, angle * 3.14 / 180, rot_arr[id]);
  }
  else
  {
    ft_putstr("ERROR: file rotate_figures.c; id = ");
    ft_putnbr(id);
    ft_putchar('\n');
  }
}
