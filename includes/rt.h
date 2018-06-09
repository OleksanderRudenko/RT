/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/06/09 19:49:29 by vvinogra         ###   ########.fr       */
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
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "OpenCL/opencl.h"
# include "tinyfiledialogs.h"
# include "open_cl.h"
# include "gui.h"

# define WIDTH 1024
# define HEIGHT 768
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1
# define LIGHT_TYPE_DIRECT 2
# define NUM_BUTTONS 14
# define NUM_SP_PR 7
# define NUM_IC_PR 10
# define NUM_PL_PR 9
# define NUM_TR_PR 11
# define NUM_CN_PR 10
# define NUM_CU_PR 11
# define NUM_QUA_PR 5
# define NUM_EL_PR 10
# define NUM_PR_PR 9
# define NUM_LI_PR 4
# define NUM_AM_PR 1
# define NUM_DIR_PR 4
# define MAX_TEXT_LEN 150

# define PORT 50000
# define SER_SIZE 48

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

typedef union			u_double
{
	double			value;
	unsigned char	bytes[sizeof(double)];
}						t_double;

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

typedef enum			e_server_client
{
	Server = -1,
	Normal,
	Client
}						t_server_client;

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
	t_vector			d;
	struct s_light		*next;
}						t_light;

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
 	t_vector  			position;
 	t_vector  			rotation;
 	double   			radius;
	t_vector 			capses[1];
	double 				c_distances[1];
	int 				c_color[1];

	t_capses  			*caps;
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
	t_vector 			capses[2];
	double 				c_distances[2];
	int 				c_color[2];
}						t_icone;

typedef struct			s_icylinder							      /* CYLINDER */
{
	t_vector			start;
	t_vector			vector;
	double				radius;
	t_vector 			capses[2];
	double 				c_distances[2];
	int 				c_color[2];
}						t_icylinder;

typedef struct			s_triangle				 				  /* TRIANGLE */
{
	t_vector			points[3];
	t_vector			normale;
}						t_triangle;

typedef struct			s_squard						 		  /* QUADRATE */
{
	 // t_vector   points[4];
 // t_vector   normale;

 	t_vector			position; // !!!
 	t_vector			rotation; // !!!

 	double				scale[2];
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
	int					mirror;
	t_figure_type		type;
	struct s_figure		*next;
}						t_figure;

typedef struct			s_space
{
	t_figure			*figures;
	t_light				*lights;
	t_ray				*cam;
	t_cl_figure 		*cl_figures;
	t_cl_light			*cl_lights;
	t_cl_figure			*cl_figtmp;
	t_cl_light			*cl_ligtmp;

	int					antialiasing;
	int					sepia;
	int					cartoon;
	int					grayscale;
	int					inversion;
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

typedef struct		s_view
{
	int				exit_loop;
	size_t 			figures_num;
	size_t 			lights_num;
	SDL_Window		*win[4];
	SDL_Event		event;
	SDL_Surface		*win_surface;
	unsigned int	*buff;
	t_gui			rr;
	t_select		select;
	t_list_obj		l_obj;
	t_sp_prop		prop;
	t_ic_prop		ic;
	t_pl_prop		pl;
	t_trial_prop	tri;
	t_cone_prop		con;
	t_cube_prop		cub;
	t_quad_prop		qua;
	t_elips_prop	elp;
	t_par_prop		par;
	t_light_prop	lp;
	t_amblight_prop	am;
	t_direct_prop	dir;
	unsigned int 	*array;
	t_list_light	l_light;
	t_space			*space;
	t_slider		**sl;
	t_opencl 		cl;
	t_ok			*ok;
	int				flag;

	struct sockaddr_in	addr;
	int					socket;
	int 				server_client;
	int					sock_for_connect;
	char				*server_ip;
}					t_view;

/*End*/

//copy1
void 		copy_plane(t_cl_figure *figure, t_figure *tmp);
void 		copy_sphere(t_cl_figure *figure, t_figure *tmp);
void 		copy_cylinder(t_cl_figure *figure, t_figure *tmp);
void 		copy_cone(t_cl_figure *figure, t_figure *tmp);
void 		copy_cube(t_cl_figure *figure, t_figure *tmp);

//copy2
void 		copy_triangle(t_cl_figure *figure, t_figure *tmp);
void 		copy_quadrate(t_cl_figure *figure, t_figure *tmp);
void 		copy_elipsoid(t_cl_figure *figure, t_figure *tmp);
void 		copy_paraboloid(t_cl_figure *figure, t_figure *tmp);
void 		copy_tor(t_cl_figure *figure, t_figure *tmp);

//effects/color_effects
void				color_effects(t_view *view);

//effects/checkerdoard
void 	 	checkerboard_effect(t_view *v, int color);

//effects/perlin_noise
unsigned int 		*perlin_noise(t_view *view);

//effects/normal_disruption
unsigned int 		*normal_disruption(t_view *view);

//main
int						exit_x(t_view *view);

//openCL/opencl_init
void					opencl_init(t_view *v);
void					opencl_init2(t_view *v);
void					opencl_errors(const char *msg);
// void					opencl_errors(cl_uint result, const char *msg);

//openCL/cl_wrapper
void 					cl_info(t_view *v);
void					cl_releasing(t_view *v);
void 					cl_set_arg(t_view *v, void *arg, size_t arg_size,
																cl_uint id);
void 					cl_set_mem_arg(t_view *v, void *arg, size_t arg_size,
																cl_uint id);
//openCL/cl_set_args
void 					set_arguments(t_view *v);


//openCL/cl_copy_data
void 					init_cam(t_view *v, cl_float3 *cam_o, cl_float3 *cam_v);
t_cl_light 				*copy_light(t_view *v);
t_cl_figure 			*copy_figures(t_view *v);
cl_float3 				copy_vector(t_vector vector);

// //button_functions
// void					mouse_key_down(t_view *s, SDL_Event e);
// void					mouse_key_up(t_view *s);
// void					button_off_on(SDL_Rect *rect, SDL_Event e, t_view *s);

// //create_text
// SDL_Texture				*create_text(t_view *s, char *name, int i);

//do_rt
double					rt_lightr(t_vector l, t_vector normale,
										t_vector view, t_vector buf);
t_lrt					tlrt_init(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						do_lightrt(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						rt(t_space *space, t_ray *ray);
void					do_rt(t_view *view);

// //init_buttons
// SDL_Texture 			*get_tex(char *file, SDL_Renderer *ren_tar);
// void					init_rect(t_gui *r);
// void					init_buttons(t_view *s);
// void					set_things_up(t_view *s);
// void					button_staff(t_view *s);

// //list_properties
// void					sphere_prop(t_view *s);
// void					print_shper_prop(t_view *s);

// //print_list_obj
// SDL_Rect				make_rect(int x, int y, int w, int h);
// int						text_width(TTF_Font *f, char *str);
// void					object_init(t_view *s);
// void					button_highlight(t_view *s, SDL_Event e, SDL_Rect *rect);

// //sdl_errors
// void					sdl_init_err(void);
// void					sdl_ttf_err(void);

// //sdl_init
// void					init_sdl(t_view *s);
// int						poll_event(t_view *s);

//space
void					add_light(t_light *light, t_view *view);
void					add_figure(t_figure *figure, t_view *view);
t_vector				get_intersection(t_ray *ray, double k);
void					space_init(const char *filename, t_view *view);
void					cam_rotate(t_ray *ray, t_vector vector);

// //utils1
// int						num_figures(t_view *s);
// char					*figure_type(t_figure_type num);

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
t_vector				get_default_vector(char ch);

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
void					parse_scene(const char *filename, t_view *view);

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
int						check_quadr_points(t_vector vector[5]);
t_squard				*calc_quadrate_params(t_squard *q);

//parse/perror
void					root_parse_error(t_view *view);

//parse/plight
void					parse_point(JSON_Object *light, t_view *view);
void					parse_ambient(JSON_Object *light, t_view *view);
void					parse_directional(JSON_Object *light, t_view *view);

//parse/pvector
t_vector				parse_vector(JSON_Array *vector, t_vector def);

//parse/preflection
void					parse_color_reflection(JSON_Object *sphere,
															t_figure *figure);

//parse//parse_effects
void 					parse_effects(JSON_Object *root, t_view *view);

void 					check_parse(JSON_Object *figure, t_view * view, char *type);

//light/light
t_light					*light_init(char type, t_vector o, t_vector d, double inten);

//figure/fcone
double					check_cone_intersection(t_ray *ray, t_icone *cone);
t_vector				get_cone_normale(t_vector p, t_icone *cone);
t_figure				*cone_init(t_ray *axis, double k, int color,
															double reflection);

//figure/fcube
t_figure				*cube_init(t_vector vector[3], int color,
															double reflection);

t_figure 	*quadrate_init(t_vector rotation, t_vector position, double scale[2]);
void		count_planes(t_cube *cube);

//figure/ftor
t_figure				*tor_init(t_vector center, const double radiuses[2],
												int color, double reflection);
double					check_tor_intersection(t_ray *ray, t_itor *tor);

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
t_figure				*triangle_init(t_vector point[3], int color,
															double reflection);

//figure/felipsoid
t_figure				*elipsoid_init(t_vector position, t_vector rotation,
												 int color, double reflection);

//color/color
int						set_brightness(int color, double brightness,
														double bbrightness);

//server_client_part

void					server_init(t_view	*view);
void					server_send_get_info(t_view *view);

void					client_init(t_view *view);
void					client_send_get_info(t_view *view);

bool					recv_all(int socket, void *buffer, size_t length);
bool					send_all(int socket, void *buffer, size_t length);
void					pack(unsigned char *buff, t_view *view);
void					unpack(unsigned char *buff, t_view *view);
void					fill_half_scr(unsigned int *half_scr, t_view *view);

void					serialize_char(unsigned char **buffer, char value);
void					serialize_int(unsigned char **buffer, int value);
void					serialize_double(unsigned char **buffer, double value);

char					deserialize_char(unsigned char **buffer);
int						deserialize_int(unsigned char **buffer);
double					deserialize_double(unsigned char **buffer);

char					*get_file_content(const char *const filename);
void					check_server(t_view *view, const char *const filename);
void					check_client(t_view *view, const char *const filename);

//server_client_part

void					usage(t_view *view, int argc, char **argv);
void					initing_mode(t_view *view, const char *const filename);
void					choose_mode(t_view *view);


/*SDL FUNCTIONS (and other by arudenko)*/
// void			sdl_init_err(void);
// void			sdl_ttf_err(void);
// void			init_sdl(t_view *s);
// int				poll_event(t_view *s);
// char			*name_of_file(char *str, int num);
// void			set_things_up(t_view *s);
// void			button_staff(t_view *s);
// SDL_Texture		*get_tex(char *file, SDL_Renderer *ren_tar);
// void			init_rect(t_gui *r);
// void			mouse_key_down(t_view *s, SDL_Event e);

// void			mouse_key_up(t_view *s);
// void			select_button_up(t_view *s, SDL_Event e, int num);

// int				button_off_on(SDL_Rect *rect, int *flag, int num, SDL_Event	e);

// SDL_Texture		*create_text(t_view *s, char *name, int i, int font_size);
// void			init_buttons(t_view *s);
// void			object_init(t_view *s);
// void			objects_draw(t_view *s);
// void			obj_highlight(t_view *s, SDL_Event e, SDL_Rect *rect);
// SDL_Rect		make_rect(int x, int y, int w, int h);
// int				text_width(TTF_Font *f, char *str);

// void			print_prop(t_view *s);
// void			sphere_prop(t_view *s);/*sphere prop*/

// int				num_figures(t_view *s);
// char			*figure_type(t_figure_type num);
// int				select_figure(SDL_Rect *rect, SDL_Event e, int num);
// void			object_default_init(t_view *s);
// void			print_default_text(t_view *s);
// void			what_to_print(t_view *s);
// void			camera_move(t_view *s, SDL_Scancode key);
// void			camera_rot(t_view *s, SDL_Scancode key);
// int				is_in_rect(SDL_Rect rect, SDL_Event e);
// void			select_init(t_view *s);
// // void			draw_select_button(t_view *s, SDL_Event e);
// void			draw_select_button(t_view *s);
// int				num_lights(t_view *s);
// char			*light_type(char num);
// void			light_list_init(t_view *s);
// void			light_list_highlight(t_view *s, SDL_Event e, SDL_Rect *rect);
// void			set_const_highlight(t_view *s, int id);
// void			detect_type_of_figure(t_view *s);
// char			*ft_ftoa(double value);
// SDL_Texture		*create_text_ftoa(t_view *s, float num, int i, int font_size);
// void			clean_staff(t_view *s);
// void			clean_sphere_prop(t_view *s);
// void			clean_buttons(t_view *s);
// void			clean_list_obj(t_view *s);
// void			clean_light(t_view *s);

// void			init_red_slider(t_view *s);
// void			init_green_slider(t_view *s);
// void			init_slider(t_view *s);
// void			display_colored_rect(t_view *s);
// void			slider_click_event(SDL_Keycode key, t_view *s, SDL_Event e);
// void			slider_motion_event(t_view *s, SDL_Event e);
// void			init_sphere_prop(t_view *s, t_sphere *f, t_figure *fig);
// int				color_unite(int r, int g, int b);
// void			ok_button_init(t_view *s);
// void			ok_button_function(t_view *s, SDL_Event e);
// void			open_scene(t_view *s);
// /*16.05.18*/
// double			par_input();
// void			xxx(int num, t_view *s);
// t_figure		*detect_figure(t_view *s);
// t_col			col_parse(int col);
// void			data_init(t_view *s);
// void			init_incyl_prop(t_view *s, t_icylinder *cyl, t_figure *fig);
// void			p_sp_prop(t_view *s, int num, SDL_Texture **t, SDL_Rect *r);
/*END*/

#endif
