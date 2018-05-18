
#ifndef FT_RTCL_H
# define FT_RTCL_H

# define WIDTH 1280
# define HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define WIDTH 1280
# define HEIGHT 720
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1

typedef union			u_color
{
	unsigned int		color;
	unsigned char 		chanel[4];
	//0 - r
	//1 - g
	//2 - b
	//4 = a
}						t_color;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere = 1,
	InfiniteCylinder = 2,
	InfiniteCone,
	Triangle,
	Cube,
	Elipsoid
}						t_figure_type;

typedef struct			s_icone
{
	float3				vertex;
	float3				vector;
	float				radius;
}						t_icone;

// /* FIGURES */
// typedef struct			s_cl_icylinder
// {
// 	float3				start;
// 	float3				vector;
// 	float				radius;
// }						t_cl_icylinder;
//
// typedef struct			s_cl_iplane
// {
// 	float3				normale;
// 	float3				point;
// }						t_cl_iplane;
//
// typedef struct			s_cl_sphere
// {
// 	float3				center;
// 	float				radius;
// }						t_cl_sphere;
// /* END */

typedef struct			s_cl_light
{
	int					type;
	float				inten;
	float3				origin;
}						t_cl_light;

typedef struct			s_ray
{
	float3				origin;
	float3				vector;
}						t_ray;

typedef struct			s_cl_figure
{
	int					color;
	float				reflection;
	float3				start;
	float3				vector;
	float3				normale;
	float3				point;
	float3				center;
	float				radius;
	t_figure_type		type;
}						t_cl_figure;

typedef	struct			s_lrt
{
	__global t_cl_light	*light;
	float3				intersection;
	float3				normale;
	float3				vlight;
	float3				buf_origin;
	float3				buf_vector;
	float				bright;
	float				reflected;
	float				nl_s;
}						t_lrt;

/* do_rt */
unsigned int			do_rt(unsigned int x,
					  	      unsigned int y,
					          unsigned int width,
					          unsigned int height,
					          __global t_cl_figure *figures,
					          __global t_cl_light *light,
							  __global float *cam_v,
							  __global float *cam_o,
							  size_t figures_num,
							  size_t lights_num);

unsigned int			rt(__global t_cl_light *lights,
						   __global t_cl_figure *figures,
						   float3 ray_origin, float3 ray_vector,
						   size_t lights_num, size_t figures_num);

unsigned int			do_lightrt(__global t_cl_light *lights,
						   __global t_cl_figure *figures,
						   t_cl_figure figure,
						   float3 ray_origin, float3 ray_vector, double k, size_t figures_num, size_t lights_num);

t_lrt					tlrt_init(__global t_cl_light *lights,
						  float3 ray_origin, float3 ray_vector, t_cl_figure figure, double k);
float					rt_lightr(float3 l, float3 normale, float3 view, float3 buf);

/* figure */
float					check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure);
int						check_intersections(float3 ray_origin, float3 ray_vector,
										__global t_cl_figure *figures, size_t figures_num, t_cl_figure figure);
float3					get_normale(float3 ray, t_cl_figure f);

/* space */
void					cam_rotate(float3 ray_vector, float3 vector);
void	  				rotate_x(float3 ps, float l);
void					rotate_y(float3 ps, float l);
void					rotate_z(float3 ps, float l);
float3 					get_intersection(float3 ray_origin, float3 ray_vector, float k);

/* vector */
float3					k_multiply(float3 vector, float k);
float3 					sum(float3 a, float3 b);
float3					subtraction(float3 a, float3 b);
float3					mult(float3 a, float3 b);


/* color */
unsigned int		 	set_brightness(unsigned int color, float brightness, float bbrightness);
unsigned int			limit_spectrum(int d, int min, int max);
unsigned int			set_spectrum_brightness(unsigned int val, float brightness, float bbrightness);

/*figures*/
float3					get_cylinder_normale(float3 p, t_cl_figure cylinder);
float3					get_plane_normale(t_cl_figure plane);
float3					get_sphere_normale(float3 p, t_cl_figure f);

float					check_sphere_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure);
float					check_plane_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure plane);
float					check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder);
float					get_sqr_solve(float a, float b, float d);


#endif
