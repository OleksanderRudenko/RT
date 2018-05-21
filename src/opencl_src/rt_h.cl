
#ifndef FT_RTCL_H
# define FT_RTCL_H

# define WIDTH 1280
# define HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1

typedef union			u_color
{
	unsigned int		color;
	unsigned char 		chanel[4];
	// color_t.chanel[3] = 255; //A1
	// color_t.chanel[2] = 255; // R
	// color_t.chanel[1] = 0;
	// color_t.chanel[0] = 0;
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
}						t_cl_light;



typedef struct			s_cl_figure
{
	int					type;
	int					color;
	float				reflection;

	float3				start;
	float3				vector;
	float3				normale;
	float3				point;
	float3				center;
	float3  			position;
	float3  			rotation;
	float3  			vertex;
	/*triangle*/
	float3				t_points[3];
	/*quadrate*/
	float3				q_points[4];
	/*cube*/
	float3				c_points[24];
	float3 				c_normale[6];
	float3				scale;
	/*capses*/
	// float 				caps1;
	// float 				caps2;
	// int 				color_c1;
	// int 				color_c2;
	// int 				color_f;

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
					  __constant t_cl_figure *figures,
					  __constant t_cl_light *lights,
					  float3 cam_vector,
					  float3 cam_origin,
					  size_t figures_num,
					  size_t lights_num);

unsigned int			rt(__constant t_cl_light *lights,
						   __constant t_cl_figure *figures,
						   float3 ray_origin, float3 ray_vector,
						   size_t lights_num, size_t figures_num);

unsigned int			do_lightrt(__constant t_cl_light *lights,
						   __constant t_cl_figure *figures,
						   t_cl_figure figure,
						   float3 ray_origin, float3 ray_vector, double k, size_t figures_num, size_t lights_num);

t_lrt					tlrt_init(float3 ray_origin, float3 ray_vector, t_cl_figure figure, double k);
float					rt_lightr(float3 l, float3 normale, float3 view, float3 buf);

/* figure */
float					check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure);
int						check_intersections(float3 ray_origin, float3 ray_vector,
										__constant t_cl_figure *figures, size_t figures_num, t_cl_figure figure);
float3					get_normale(float3 ray, t_cl_figure f);
int						figure_equal(t_cl_figure figure1, t_cl_figure figure2);

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
int						is_equal(float3 vector1, float3 vector2);


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
