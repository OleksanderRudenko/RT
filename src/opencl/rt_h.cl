
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
	unsigned int 		chanel[4];
}						t_color;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere,
	InfiniteCylinder,
	InfiniteCone,
	Triangle,
	Cube,
	Elipsoid
}						t_figure_type;

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct 			s_itor
{
	float				r;
	float				r_b;
	float3			    center;
}						t_itor;

typedef struct			s_icone
{
	float3				vertex;
	float3				vector;
	float				radius;
}						t_icone;

typedef struct			s_icylinder
{
	float3				start;
	float3				vector;
	float				radius;
}						t_icylinder;

typedef struct			s_iplane
{
	float3				normale;
	float3				point;
}						t_iplane;

typedef struct			s_sphere
{
	float3				center;
	float				radius;
}						t_sphere;

typedef struct			s_cl_light
{
	int					type;
	float				inten;
	float3			origin;
}						t_cl_light;

typedef struct			s_ray
{
	float3				origin;
	float3				vector;
}						t_ray;

typedef struct			s_figure
{
	void				*figure;
	int					color;
	float				reflection;
	t_figure_type		type;
	__global struct s_figure		*next;
}						t_figure;

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
					          __global t_figure *figures,
					          __global t_cl_light *light,
										__global float *cam_v,
									 __global float *cam_o);

unsigned int			rt(__global t_cl_light *lights, __global t_figure *figures,
							float3 ray_origin, float3 ray_vector);

unsigned int			do_lightrt(__global t_cl_light *lights,
						   __global t_figure *figures,
						   __global t_figure *figure, float3 ray_origin, float3 ray_vector, double k);

t_lrt					tlrt_init(__global t_cl_light *lights,
						  float3 ray_origin, float3 ray_vector, __global t_figure *figure, double k);
float					rt_lightr(float3 l, float3 normale, float3 view, float3 buf);

/* figure */
float					check_intersection(float3 ray_origin, float3 ray_vector, __global t_figure *figure);
int						check_intersections(float3 ray_origin, float3 ray_vector, __global t_figure *figures);
float3					get_normale(float3 ray, __global t_figure *f);

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
float3					get_cone_normale(float3 p, t_icone *cone);
float3					get_cylinder_normale(float3 p, t_icylinder *cylinder);
float3					get_plane_normale(t_iplane *plane);
float3					get_sphere_normale(float3 p, t_sphere *f);

float					check_sphere_intersection(float3 ray_origin, float3 ray_vector, t_sphere *figure);
float					check_plane_intersection(float3 ray_origin, float3 ray_vector, t_iplane *plane);
float					check_cone_intersection(float3 ray_origin, float3 ray_vector, t_icone *cone);
float					check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_icylinder *cylinder);
float					get_sqr_solve(float a, float b, float d);
float3				    count_triangle_normale(float3 a);


#endif
