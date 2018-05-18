/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "libft.h"
# include "get_next_line.h"
# include "parson.h"
# include <errno.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "OpenCL/opencl.h"
# define WIDTH 1280
# define HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1
# define NUM_BUTTONS 2
# define MAX_TEXT_LEN 100
// # define NUM_PROP 3

// #ifdef cl_khr_byte_addressable_store
// 	#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
// #endif
// #ifdef cl_khr_fp64
// 	#pragma OPENCL EXTENSION cl_khr_fp64 : enable
// #elif defined(cl_amd_fp64)
// 	#pragma OPENCL EXTENSION cl_amd_fp64 : enable
// #endif

typedef union			u_color
{
	int					color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}					spectrum;
}						t_color;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_light
{
	char				type;
	double				inten;
	t_vector			o;
	struct s_light		*next;
}						t_light;

typedef struct			s_cl_light
{
	int					type;
	float				inten;
	cl_float3			origin;
	struct s_cl_light *next;
}						t_cl_light;
															/* OPEN CL STRUCT */
typedef struct			s_opencl
{
	cl_int 				result;
	cl_platform_id     *platforms;          //List of platforms IDs
	cl_uint             num_platforms;		//The actual number of returned platform IDs
	cl_device_id       *device_ids;         //List of device IDs
	cl_uint             num_devices;        //The actual number of returned device IDs returned
	cl_context 			context;
	cl_command_queue 	commands;
	cl_program 			program;
	cl_kernel 			kernel;
	size_t 				values_number;
	size_t 				buffers_size;
	cl_mem 				output_buffer;
	size_t    			global_work_size;  	//Number of values for each dimension we use
	size_t    			local_work_size;    //Size of a work-group in each dimension
	cl_event  			kernel_exec_event;
	cl_event    		read_results_event;
}						t_opencl;

/*
**	t_ray type represents origin of ray and his vector. Also for camera obj
**		this type setup coordinates of camera(o) and rotation angles(v).
**		In cylinder context this type represents start of cylinder axis(o)
**		and direction vector.
*/

typedef struct			s_ray
{
	t_vector			o;
	t_vector			v;
}						t_ray;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere,
	InfiniteCylinder,
	InfiniteCone,
	Triangle,
	Cube,
	Elipsoid,
	Tor
}						t_figure_type;


/* FIGURES */

typedef struct			s_iplane								 	 /* PLANE */
{
	t_vector			normale;
	t_vector			point;
}						t_iplane;

typedef struct   		s_capses 									/* CAPSES */
{
 	t_iplane 			*plane;
 	t_color  			color;
 	char  				enable_caps;
}      					t_capses;

typedef struct   		s_parabaloid 							/* PARABOLOID */
{
 t_vector  				position;
 t_vector  				rotation;
 double   				radius;

 t_capses  *caps;
}      					t_parabaloid;

typedef struct			s_sphere									/* SPHERE */
{
	t_vector			center;
	double				radius;
}						t_sphere;

typedef struct			s_icone										  /* CONE */
{
	t_vector			vertex;
	t_vector			vector;
	double				radius;
	t_capses  			*caps1;
  	t_capses  			*caps2;
}						t_icone;

typedef struct			s_icylinder							      /* CYLINDER */
{
	t_vector			start;
	t_vector			vector;
	double				radius;
  	t_capses  			*caps1;
  	t_capses  			*caps2;
}						t_icylinder;

typedef struct			s_triangle				 				  /* TRIANGLE */
{
	t_vector			points[3];
	t_vector			normale;
}						t_triangle;

typedef struct			s_squard						 		  /* QUADRATE */
{
	t_vector			points[4];
	t_vector			normale;
}						t_squard;

typedef struct			s_cube					    	  			  /* CUBE */
{
	t_vector			position;
	t_vector			rotation;
	t_vector			scale;
	t_squard			planes[6];
}						t_cube;

typedef struct   		s_elipsoid					              /* ELIPSOID */
{
	t_vector  			position;
	t_vector  			rotation;
	double				radius;
	double				rdistance;
}      					t_elipsoid;

typedef struct 			s_itor					                       /* TOR */
{
	double				r;
	double				r_b;
	t_vector			center;
}						t_itor;

/* END */

typedef struct			s_cubic
{
	double 				a;
	double 				b;
	double 				c;
	double 				d;
	double 				*ret;
	double 				p;
	double 				q;
	double 				s;
}						t_cubic;

typedef struct			s_quadric
{
	double 				a;
	double 				b;
	double 				c;
	double 				d;
	double 				e;
	double 				*sqr;
	double 				*cub;
	double 				*ret;
	double 				p;
	double 				q;
	double 				r;
}						t_quadric;

typedef struct			s_figure
{
	void				*figure;
	int					color;
	float				reflection;
	t_figure_type		type;
	struct s_figure		*next;
}						t_figure;

typedef struct			s_space
{
	t_figure			*figures;
	t_light				*lights;
	t_ray				*cam;
}						t_space;

typedef	struct			s_lrt
{
	t_light				*light;
	t_vector			intersection;
	t_vector			normale;
	t_vector			vlight;
	t_ray				*buf;
	double				bright;
	double				reflected;
	double				nl_s;
}						t_lrt;

typedef struct			s_text
{
	TTF_Font			*font;
	SDL_Surface			*message;
	SDL_Texture			*tex;
	SDL_Rect			text_rect;
	SDL_Color			color;
}						t_text;

typedef struct			s_list_obj
{
	SDL_Texture			**obj_tex;
	SDL_Rect			*obj_rect;
}						t_list_obj;

typedef struct			s_list_prop
{
	SDL_Texture			**prop_tex;
	SDL_Rect			*prop_rect;
}						t_list_prop;

typedef struct			s_gui
{
	SDL_Rect			*but_rect;
	SDL_Renderer		*rend[3];
	SDL_Texture			**but_on;
	SDL_Texture			**but_off;
	Uint32				*flag;
}						t_gui;

typedef struct			s_view
{
	int					exit_loop;
	size_t 				figures_num;
	size_t 				lights_num;
	SDL_Window			*win[4];
	SDL_Event			event;
	SDL_Surface			*win_surface[3]; /*will be neede only one*/
	unsigned int		*buff;
	t_gui				rr;
	t_list_obj			l_obj;
	t_list_prop			l_prop;
	t_space				*space;
	t_ray				*ray;
	t_opencl 			cl;
}						t_view;

//main
int						exit_x(t_view *view);

//opencl_init
void					opencl_init(t_view *v);

//button_functions
void					mouse_key_down(t_view *s, SDL_Event e);
void					mouse_key_up(t_view *s);
void					button_off_on(SDL_Rect *rect, SDL_Event e, t_view *s);

//create_text
SDL_Texture				*create_text(t_view *s, char *name, int i);

//do_rt
double					rt_lightr(t_vector l, t_vector normale,
										t_vector view, t_vector buf);
t_lrt					tlrt_init(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						do_lightrt(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						rt(t_space *space, t_ray *ray);
void					do_rt(t_view *view);

//init_buttons
SDL_Texture 			*get_tex(char *file, SDL_Renderer *ren_tar);
void					init_rect(t_gui *r);
void					init_buttons(t_view *s);
void					set_things_up(t_view *s);
void					button_staff(t_view *s);

//list_properties
void					sphere_prop(t_view *s);
void					print_shper_prop(t_view *s);

//print_list_obj
SDL_Rect				make_rect(int x, int y, int w, int h);
int						text_width(TTF_Font *f, char *str);
void					object_init(t_view *s);
void					button_highlight(t_view *s, SDL_Event e, SDL_Rect *rect);

//sdl_errors
void					sdl_init_err(void);
void					sdl_ttf_err(void);

//sdl_init
void					init_sdl(t_view *s);
int						poll_event(t_view *s);

//space
void					add_light(t_light *light, t_view *view);
void					add_figure(t_figure *figure, t_view *view);
t_vector				get_intersection(t_ray *ray, double k);
void					space_init(char *filename, t_view *view);
void					cam_rotate(t_ray *ray, t_vector vector);

//utils1
int						num_figures(t_view *s);
char					*figure_type(t_figure_type num);

//solve_cubic
double					*find_cube_sqrt(double a, double b, double c, double d);

//solve_quatric
double					*quadric_solver(const double (*nums)[5]);

//vector/rotate
void					rotate_x(t_vector *ps, double l);
void					rotate_y(t_vector *ps, double l);
void					rotate_z(t_vector *ps, double l);

//vector/vector
t_vector				vector_init(double x, double y, double z);
double					vscalar_multiple(t_vector a, t_vector b);
t_vector				vk_multiple(t_vector vector, double k);
int						vis_equal(t_vector vector1, t_vector vector2);

//vector/vector2
t_vector				vmultiple(t_vector a, t_vector b);
t_vector				vsum(t_vector a, t_vector b);
t_vector				vsub(t_vector a, t_vector b);
double					vlen(t_vector a);
t_vector				vnormalize(t_vector a);

//parse/ft_hexatoi
int						check_hex(const char *str);
int						ft_hexatoi(const char *str);

//parse/parse
void					parse_scene(char *filename, t_view *view);

//parse/pcam
void					parse_cam(JSON_Object *root, t_view *view);

//parse/pcon
void					parse_cone(JSON_Object *cone, t_view *view);

//parse/pcube
void					parse_cube(JSON_Object *cube, t_view *view);

//parse/pcylinder
void					parse_cylinder(JSON_Object *cylinder, t_view *view);

//parse/pplane
void					parse_plane(JSON_Object *plane, t_view *view);

//parse/psphere
void					parse_sphere(JSON_Object *sphere, t_view *view);

//parse/ptriangle
int						check_array(JSON_Array *array, JSON_Value_Type type,
																  size_t len);
int						check_triangle_points(t_vector vector[3]);
void					parse_triangle(JSON_Object *triangle, t_view *view);

//parse/pelipsoid
void					parse_elipsoid(JSON_Object *elipsoid, t_view *view);

//parse/pparaboloid
void					parse_paraboloid(JSON_Object *paraboloid, t_view *view);

//parse/ptor
void					parse_tor(JSON_Object *elipsoid, t_view *view);

//parse/pcut_plane
void					parse_cut_plane(t_iplane *fplane, t_capses *caps,
									JSON_Object *paraboloid, const char *name);
t_capses 				*init_cut_plane(void);

//parse/pquadrate
void 					parse_quadrate(JSON_Object *quadrate, t_view *view);

//parse/perror
void					root_parse_error(t_view *view);

//parse/plight
void					parse_point(JSON_Object *light, t_view *view);
void					parse_ambient(JSON_Object *light, t_view *view);

//parse/pvector
t_vector				parse_vector(JSON_Array *vector, t_vector def);

//parse/preflection
void					parse_color_reflection(JSON_Object *sphere,
															t_figure *figure);

//light/light
t_light					*light_init(char type, t_vector o, double inten);

//figure/fcone
double					check_cone_intersection(t_ray *ray, t_icone *cone);
t_vector				get_cone_normale(t_vector p, t_icone *cone);
t_figure				*cone_init(t_ray *axis, double k, int color,
															double reflection);

//figure/fcube
t_figure				*cube_init(t_ray *pnr, t_vector scale, int color,
															double reflection);

//figure/ftor
t_figure				*tor_init(t_vector center, const double radiuses[2],
												int color, double reflection);
double			check_tor_intersection(t_ray *ray, t_itor *tor);

//figure/fcylinder
double					check_cylinder_intersection(t_ray *ray,
														t_icylinder *cylinder);
t_vector				get_cylinder_normale(t_vector p, t_icylinder *cylinder);
t_figure				*cylinder_init(t_ray *axis, double radius, int color,
															double reflection);

//figure/figure
t_ray					*ray_init(t_vector origin, t_vector vector);
t_vector				get_normale(t_vector ray, t_figure *f);
double					check_intersection(t_ray *ray, t_figure *figure);
int						check_intersections(t_ray *ray, t_figure *figures);

//figure/fplane
double					check_plane_intersection(t_ray *ray, t_iplane *plane);
t_vector				get_plane_normale(t_iplane *plane);
t_figure				*plane_init(t_vector normale, t_vector point, int color,
															double reflection);

//figure/fsphere
double					get_sqr_solve(double a, double b, double d);
double					check_sphere_intersection(t_ray *ray, t_sphere *figure);
t_vector				get_sphere_normale(t_vector p, t_sphere *f);
t_figure				*sphere_init(t_vector center, double r, int color,
															double reflection);

//figure/ftriangle
t_vector				count_triangle_normale(t_vector a[3]);
t_figure				*triangle_init(t_ray *ray, t_vector third_point,
												 int color, double reflection);

//figure/felipsoid
t_figure				*elipsoid_init(t_vector position, t_vector rotation,
												 int color, double reflection);

//color/color
int						set_brightness(int color, double brightness,
														double bbrightness);

#endif
