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

#ifndef RTV1_H
# define RTV1_H
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
# define WIDTH 1280
# define HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1

typedef union			u_color
{
	int				color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}				spectrum;
}						t_color;

typedef struct			s_vector
{
	double			x;
	double			y;
	double			z;
}						t_vector;

typedef struct			s_light
{
	char			type;
	double			inten;
	t_vector		o;
	struct s_light	*next;
}						t_light;

/*
**	t_ray type represents origin of ray and his vector. Also for camera obj
**		this type setup coordinates of camera(o) and rotation angles(v).
**		In cylinder context this type represents start of cylinder axis(o)
**		and direction vector.
*/

typedef struct			s_ray
{
	t_vector		o;
	t_vector		v;
}						t_ray;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere = 1,
	InfiniteCylinder = 2,
	InfiniteCone = 3,
	Triangle = 4,
	Cube = 5
}						t_figure_type;

typedef struct			s_iplane
{
	t_vector		normale;
	t_vector		point;
}						t_iplane;

typedef struct			s_sphere
{
	t_vector		center;
	double			radius;
}						t_sphere;

typedef struct			s_icone
{
	t_vector		vertex;
	t_vector		vector;
	double			radius;
}						t_icone;

typedef struct			s_icylinder
{
	t_vector		start;
	t_vector		vector;
	double			radius;

}						t_icylinder;

typedef struct			s_triangle
{
	t_vector		points[3];
	t_vector		normale;
}						t_triangle;

typedef struct			s_squard
{
	t_vector		points[4];
	t_vector		normale;
}					t_squard;

typedef struct		s_cube
{
	t_vector		position;
	t_vector		rotation;
	t_vector		scale;
	t_squard		planes[6];
}					t_cube;

typedef struct			s_figure
{
	void			*figure;
	int				color;
	double			reflection;
	t_figure_type	type;
	struct s_figure	*next;
}						t_figure;

typedef struct			s_space
{
	t_figure		*figures;
	t_light			*lights;
	t_ray			*cam;
}						t_space;

typedef	struct			s_lrt
{
	t_light			*light;
	t_vector		intersection;
	t_vector		normale;
	t_vector		vlight;
	t_ray			*buf;
	double			bright;
	double			reflected;
	double			nl_s;
}						t_lrt;

typedef struct		s_gui
{
	SDL_Rect		*button;
	SDL_Renderer	*rend;
	SDL_Texture		**but_on;
	SDL_Texture		**but_off;
	Uint32			*flag;
}					t_gui;

typedef struct			s_view
{
	int				exit_loop;
	SDL_Window		*win[4];
	SDL_Event		event;
	SDL_Surface		*win_surface[3];/*will be neede only one*/
	unsigned int	*buff;
	t_gui			rr;
	t_space			*space;
}						t_view;

int						exit_x(t_view *view);
void					do_rt(t_view *view);
int						set_brightness(int color, double brightness,
		double bbrightness);
t_vector				vector_init(double x, double y, double z);
double					vscalar_multiple(t_vector a, t_vector b);
t_vector				vk_multiple(t_vector vector, double k);
t_vector				vmultiple(t_vector a, t_vector b);
t_vector				vsum(t_vector a, t_vector b);
t_vector				vsub(t_vector a, t_vector b);
t_vector				vnormalize(t_vector a);
double					vlen(t_vector a);
int						vis_equal(t_vector vector1, t_vector vector2);
t_light					*light_init(char type, t_vector o, double intencity);
double					check_sphere_intersection(t_ray *ray, t_sphere *sphere);
double					get_sqr_solve(double a, double b, double d);
t_vector				get_normale(t_vector ray, t_figure *f);

t_vector				get_sphere_normale(t_vector p, t_sphere *f);
t_figure				*sphere_init(t_vector center, double r, int color,
		double reflection);

t_figure				*plane_init(t_vector normale, t_vector point, int color,
		double reflection);
t_vector				get_plane_normale(t_iplane *plane);
double					check_plane_intersection(t_ray *ray, t_iplane *plane);

double					check_intersection(t_ray *ray, t_figure *figure);
int						check_intersections(t_ray *ray, t_figure *figures);
t_vector				get_intersection(t_ray *ray, double k);
t_ray					*ray_init(t_vector start, t_vector end);
void					space_init(char *filename, t_view *view);
void					cam_rotate(t_ray *ray, t_vector vector);
void					rotate_x(t_vector *ps, double l);
void					rotate_y(t_vector *ps, double l);
void					rotate_z(t_vector *ps, double l);

double					check_cylinder_intersection(t_ray *ray,
		t_icylinder *cylinder);
t_figure				*cylinder_init(t_ray *axis, double radius, int color,
		double reflection);
t_vector				get_cylinder_normale(t_vector p, t_icylinder *cylinder);

double					check_cone_intersection(t_ray *ray, t_icone *cone);
t_vector				get_cone_normale(t_vector p, t_icone *cone);
t_figure				*cone_init(t_ray *axis, double k, int color,
		double reflection);

t_figure				*triangle_init(t_ray *ray, t_vector third_point, int color,
		double reflection);

void					parse_scene(char *filename, t_view *view);
void					root_parse_error(t_view *view);
void					parse_sphere(JSON_Object *sphere, t_view *view);
t_vector				parse_vector(JSON_Array *vector, t_vector def);
int						check_hex(const char *str);
int						ft_hexatoi(const char *str);
void					add_figure(t_figure *figure, t_view *view);
void					add_light(t_light *light, t_view *view);
void					parse_color_reflection(JSON_Object *sphere,
		t_figure *figure);
void					parse_plane(JSON_Object *plane, t_view *view);
void					parse_cylinder(JSON_Object *cylinder, t_view *view);
void					parse_cone(JSON_Object *cone, t_view *view);
void					parse_ambient(JSON_Object *light, t_view *view);
void					parse_point(JSON_Object *light, t_view *view);
void					parse_cam(JSON_Object *root, t_view *view);
void					parse_triangle(JSON_Object *triangle, t_view *view);
t_figure				*cube_init(t_ray *pnr, t_vector scale, int color,
		double reflection);

/*SDL FUNCTIONS (and other by arudenko)*/
void			sdl_init_err(void);
void			sdl_ttf_err(void);
void			init_sdl(t_view *s);
int				poll_event(t_view *s);
char			*name_of_file(char *str, int num);
void			set_things_up(t_view *s);
void			button_staff(t_view *s);
SDL_Texture		*get_tex(char *file, SDL_Renderer *ren_tar);
void			init_rect(t_gui *r);
void			key_down(SDL_Scancode key, t_view *s);
void			button_off_on(SDL_Rect *rect, SDL_Event e, t_view *s);

/*END*/

#endif
