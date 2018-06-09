
#ifndef FT_RTCL_H
# define FT_RTCL_H

# define WIDTH 1280
# define HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1
# define LIGHT_TYPE_DIRECT 2

typedef union			u_color
{
	unsigned int		color;
	unsigned char 		chanel[4];
	// color_t.chanel[3] = 255; //A1
	// color_t.chanel[2] = 255; // R
	// color_t.chanel[1] = 0; G
	// color_t.chanel[0] = 0; B
}						t_color;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere,
	InfiniteCylinder,
	InfiniteCone,
	Triangle,
	Cube,
	Quadrate,
	Elipsoid,
	Parabaloid,
	Tor
}						t_figure_type;

typedef struct			s_cl_light
{
	int					type;
	float				inten;
	float3				origin;
	float3				direction;
}						t_cl_light;



typedef struct			s_cl_figure
{
	int					type;
	int					color;
	int					mirror;
	int					texture;
	float				reflection;

	float3				start;
	float3				vector;
	float3				normale;
	float3				point;
	float3				center;
	float3  			position;
	float3  			rotation;
	float3  			vertex;
	/*triangle*/ /* + capses points*/
	float3				t_points[3];
	/*quadrate*/
	float3				q_points[4];
	/*cube*/
	float3				c_points[24];
	float3 				c_normale[6];
	float3				scale;
	/*capses*/
	float 				caps1;
	float 				caps2;
	int 				color_c1;
	int 				color_c2;
	int 				color_f;

	float				radius;
	float				rdistance;
	float				radius_s;
	float				radius_b;

}						t_cl_figure;

typedef	struct			s_lrt
{
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
					  size_t width,
					  size_t height,
					  __global t_cl_figure *figures,
					  __constant t_cl_light *lights,
					  float3 cam_vector,
					  float3 cam_origin,
					  size_t figures_num,
					  size_t lights_num,
						int antialising,
						__global unsigned int *tex);

unsigned int			rt(__constant t_cl_light *lights, __global t_cl_figure *figures,
					float3 ray_origin, float3 ray_vector, size_t lights_num, size_t figures_num, int iters, __global unsigned int *tex);

unsigned int			do_lightrt(__constant t_cl_light *lights,
						   __global t_cl_figure *figures,
						   t_cl_figure figure,
						   float3 ray_origin, float3 ray_vector, double k,
						   size_t figures_num, size_t lights_num, int iters, float3 normale, __global unsigned int *tex);

t_lrt					tlrt_init(float3 ray_origin, float3 ray_vector, t_cl_figure figure, double k, float3 normale);
float					rt_lightr(float3 l, float3 normale, float3 view, float3 buf);

/* figure */
float					check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *figure, float min, float3 *normale);
int						check_intersections(float3 ray_origin, float3 ray_vector,
										__global t_cl_figure *figures, size_t figures_num, t_cl_figure figure);
float3					get_normale(float3 ray, t_cl_figure f);
int						figure_equal(t_cl_figure figure1, t_cl_figure figure2);

/* space */
float3					cam_rotate(float3 ray_vector, float3 vector);
float3	  				rotate_x(float3 ps, float l);
float3					rotate_y(float3 ps, float l);
float3					rotate_z(float3 ps, float l);
float3 					get_intersection(float3 ray_origin, float3 ray_vector, float k);

/* vector */
float3					k_multiply(float3 vector, float k);
float3 					sum(float3 a, float3 b);
float3					subtraction(float3 a, float3 b);
float3					mult(float3 a, float3 b);
int							is_equal(float3 vector1, float3 vector2);
float3  				cross_vec(float3 a, float3 b);
float3					vnormalize(float3 v);


/* color */
unsigned int		 	set_brightness(unsigned int color, float brightness, float bbrightness);
unsigned int			limit_spectrum(int d, int min, int max);
unsigned int			set_spectrum_brightness(unsigned int val, float brightness, float bbrightness);

/*figures*/
float3					get_cylinder_normale(float3 p, t_cl_figure cylinder);
float3					get_plane_normale(t_cl_figure plane);
float3					get_sphere_normale(float3 p, t_cl_figure f);
float3					get_cone_normale(float3 p, t_cl_figure cone);
float3					get_elipsoid_normale(float3 p, t_cl_figure elips);
float3					get_paraboloid_normale(float3 p, t_cl_figure parab);
float3  				get_triangle_normale(float3 p, t_cl_figure triangle);
float3  				get_cube_normale(float3 p, t_cl_figure triangle);
float3  				get_squad_normale(float3 p, t_cl_figure q);


float					check_sphere_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure, float min, float3 *normale);
float					check_plane_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure plane, float min, float3 *normale);
float					check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder, float min, float3 *normale);
float					check_cone_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *cone, float min, float3 *normale);
float					check_elipsoid_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *elips, float min, float3 *normale);
float					check_paraboloid_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *parab, float min, float3 *normale);
float					check_triangle_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *triangle, float min, float3 *normale);
float					check_cube_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *cube, float min, float3 *normale);
float     		check_intersection_squad(float3 ray_origin, float3 ray_vector, float3 *c_points, float3 normale);
float					check_sq_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *q, float min, float3 *normale);


float					get_sqr_solve(float a, float b, float d, float min);
float 				q_rsqrt( float number );
char	     		inside_squad(float3 *c_points, float3 p);

unsigned int		calc_middle_color(unsigned int *colors, int antialising);
float3					calc_reflect_ray(float3 ray_vector, float3 normale, float3 p);
unsigned	int		add_colors(unsigned	int	color1, unsigned	int	color2);

unsigned int	texture_sphere(float3 normal, __global unsigned int *texture,t_cl_figure closest);
unsigned int	getcolor(__global unsigned int *texture, int x, int y, int w);
unsigned int	texture_plane(float3 normal, __global unsigned int *texture, t_cl_figure plane);
unsigned int	texture_cone(float3 p_c, float3 normal, __global unsigned int *texture, t_cl_figure closest);
unsigned int	global_texture(float3 normal, __global unsigned int *texture, t_cl_figure closest,
		float len, float3 ray_origin, float3 ray_vector);

float			dot_my(float3 v1, float3 v2);
float		pow_my(float d, char del);
float		len_my(float3 v);


#endif
