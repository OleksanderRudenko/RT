#include "rt.h"

cl_float3  mult_vec_cl(cl_float3 v, float k)
{
  v.x *= k;
  v.y *= k;
  v.z *= k;
  return (v);
}

cl_float3  sub_vec_cl(cl_float3 v1, cl_float3 v2)
{
  v1.x -= v2.x;
  v1.y -= v2.y;
  v1.z -= v2.z;
  return (v1);
}

cl_float3  sum_vec_cl(cl_float3 v1, cl_float3 v2)
{
  v1.x += v2.x;
  v1.y += v2.y;
  v1.z += v2.z;
  return (v1);
}

void  new_normal_triangle(t_cl_figure *figure)
{
  t_vector  dots[3];
  t_vector  normale;
  int i;

  i = 0;
  while (i < 3)
  {
    dots[i].x = figure->t_points[i].x;
    dots[i].y = figure->t_points[i].y;
    dots[i].z = figure->t_points[i].z;
  }
  normale = count_triangle_normale(dots);
  figure->normale = copy_vector(normale);
}

void  change_pos_cube(t_cl_figure *figure, cl_float3 new_value)
{
  cl_float3 delta_move;
  int i;

  i = 0;
  delta_move = sub_vec_cl(new_value, figure->position);
  // delta_move = sub_vec_cl(figure->position, new_value);
  while (i < 24)
  {
    figure->c_points[i] = sum_vec_cl(delta_move, figure->c_points[i]);
    i++;
  }
  figure->position = sum_vec_cl(delta_move, figure->position);
}

void  change_pos_sq(t_cl_figure *figure, cl_float3 new_value)
{
  cl_float3 delta_move;
  int i;

  i = 0;
  delta_move = sub_vec_cl(figure->position, new_value);
  while (i < 4)
  {
    figure->q_points[i] = sum_vec_cl(delta_move, figure->c_points[i]);
    i++;
  }
  figure->position = sum_vec_cl(delta_move, figure->position);
}

void  change_pos(t_cl_figure *figure, float new_value, int id)
{
  static cl_float3  def_arr[3] =
  {
    (cl_float3){1, 0, 0},
    (cl_float3){0, 1, 0},
    (cl_float3){0, 0, 1},
  };
  cl_float3 this_def;

  this_def = mult_vec_cl(def_arr[id], new_value);
  if (figure->type == Cube)
    change_pos_cube(figure, this_def);
  else if (figure->type == Quadrate)
    change_pos_sq(figure, this_def);
}
