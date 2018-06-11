/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 18:08:49 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/26 18:08:51 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "rt.h"

typedef struct s_figure	t_figure;
typedef struct s_light	t_light;
typedef struct s_view	t_view;
typedef enum e_figure_type	t_figure_type;
typedef void	(*t_pr)(t_view *s);
typedef void	(*t_init)(t_view *s);
typedef void	(*t_read_prop)(t_view *s, int num);

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_col;

typedef struct		s_ok
{
	SDL_Texture		*b_ok;
	SDL_Rect		ok_rect;
}					t_ok;

typedef struct		s_slider
{
	t_col			clr;
	SDL_Texture		*line;
	SDL_Texture		*slider_but;
	SDL_Rect		slider_rect;
	SDL_Rect		line_rect;
}					t_slider;

typedef struct		s_select
{
	SDL_Texture		**sel_tex_on;
	SDL_Rect		*sel_rect;
}					t_select;

typedef struct		s_text
{
	TTF_Font		*font;
	SDL_Surface		*message;
	SDL_Texture		*tex;
	SDL_Color		color;
}					t_text;

typedef struct		s_list_light
{
	SDL_Texture		**light_tex;
	SDL_Rect		*light_rect;
	int				l_flag;
	t_figure		*f;
}					t_list_light;

typedef struct		s_list_obj
{
	SDL_Texture		**obj_tex;
	SDL_Rect		*obj_rect;
	SDL_Texture		*def_tex;
	SDL_Rect		def_rect;
	int				d_flag;
}					t_list_obj;

typedef struct		s_sp_prop
{
	SDL_Texture		**tex;
	SDL_Rect		*rect;
	SDL_Texture		**prop;
	SDL_Rect		*pr_rect;
}					t_sp_prop;

typedef struct		s_ic_prop
{
	SDL_Texture		**ic_tex;
	SDL_Rect		*ic_rect;
	SDL_Texture		**ic_prop;
	SDL_Rect		*ic_pr_rect;
}					t_ic_prop;

typedef struct		s_pl_prop
{
	SDL_Texture		**pl_tex;
	SDL_Rect		*pl_rect;
	SDL_Texture		**pl_prop;
	SDL_Rect		*pl_pr_rect;
}					t_pl_prop;

typedef struct		s_tria_prop
{
	SDL_Texture		**tri_tex;
	SDL_Rect		*tri_rect;
	SDL_Texture		**tri_prop;
	SDL_Rect		*tri_pr_rect;
}					t_trial_prop;

typedef struct		s_cone_prop
{
	SDL_Texture		**cn_tex;
	SDL_Rect		*cn_rect;
	SDL_Texture		**cn_prop;
	SDL_Rect		*cn_pr_rect;
}					t_cone_prop;

typedef struct		s_cube_prop
{
	SDL_Texture		**cu_tex;
	SDL_Rect		*cu_rect;
	SDL_Texture		**cu_pr;
	SDL_Rect		*cu_pr_rect;
}					t_cube_prop;

typedef struct		s_quad_prop
{
	SDL_Texture		**qu_tex;
	SDL_Rect		*qu_rect;
	SDL_Texture		**qu_prop;
	SDL_Rect		*qu_pr_rect;
}					t_quad_prop;

typedef struct		s_elips_prop
{
	SDL_Texture		**el_tex;
	SDL_Rect		*el_rect;
	SDL_Texture		**el_prop;
	SDL_Rect		*el_pr_rect;
}					t_elips_prop;

typedef struct		s_par_prop
{
	SDL_Texture		**pr_tex;
	SDL_Rect		*pr_rect;
	SDL_Texture		**pr_prop;
	SDL_Rect		*pr_pr_rect;
}					t_par_prop;

typedef struct		s_light_prop
{
	SDL_Texture		**li_tex;
	SDL_Rect		*li_rect;
	SDL_Texture		**li_prop;
	SDL_Rect		*li_pr_rect;
}					t_light_prop;

typedef struct		s_amblight_prop
{
	SDL_Texture		**aml_tex;
	SDL_Rect		*aml_rect;
	SDL_Texture		**aml_prop;
	SDL_Rect		*aml_pr_rect;
}					t_amblight_prop;

typedef struct		s_direct_prop
{
	SDL_Texture		**dir_tex;
	SDL_Rect		*dir_rect;
	SDL_Texture		**dir_prop;
	SDL_Rect		*dir_pr_rect;
}					t_direct_prop;

typedef struct		s_numbers
{
	int				x;
	int				y;
	int				z;
	int				a;
	int				b;
	int				c;
}					t_num;

typedef struct		s_gui
{
	SDL_Rect		*but_rect;
	SDL_Renderer	*rend[3];
	SDL_Texture		**but_on;
	SDL_Texture		**but_off;
	Uint32			select_flag;
	t_num			fl;
	SDL_Surface		*logo;
}					t_gui;

void				sdl_init_err(void);
void				sdl_ttf_err(void);
void				init_sdl(t_view *s);
int					poll_event(t_view *s);
char				*name_of_file(char *str, int num);
void				set_things_up(t_view *s);
void				button_staff(t_view *s);
SDL_Texture			*get_tex(char *file, SDL_Renderer *ren_tar);
void				init_rect(t_gui *r);
void				mouse_key_down(t_view *s, SDL_Event e);
void				mouse_key_up(t_view *s);
void				select_button_up(t_view *s, SDL_Event e, int num);
int					button_off_on(SDL_Rect *rect, int num, SDL_Event	e);
SDL_Texture			*create_text(t_view *s, char *name, int i, int font_size);
void				init_buttons(t_view *s);
void				object_init(t_view *s);
void				objects_draw(t_view *s);
void				obj_highlight(t_view *s, SDL_Event e, SDL_Rect *rect);
SDL_Rect			make_rect(int x, int y, int w, int h);
int					text_width(TTF_Font *f, char *str);
void				print_sph_prop(t_view *s);
void				sphere_prop(t_view *s);
char				*figure_type(t_figure_type num);
int					select_figure(SDL_Rect *rect, SDL_Event e, int num);
void				object_default_init(t_view *s);
void				print_default_text(t_view *s);
void				what_to_print(t_view *s);
void				camera_move(t_view *s, SDL_Scancode key);
void				camera_rot(t_view *s, SDL_Scancode key);
int					is_in_rect(SDL_Rect rect, SDL_Event e);
void				select_init(t_view *s);
void				draw_select_button(t_view *s);
char				*light_type(char num);
void				light_list_init(t_view *s);
void				light_list_highlight(t_view *s,
						SDL_Event e, SDL_Rect *rect);
void				set_const_highlight(t_view *s, int id);
void				detect_type_of_figure(t_view *s);
char				*ft_ftoa(double value);
SDL_Texture			*tf(t_view *s, float num, int i, int font_size);
void				clean_staff(t_view *s);
void				clean_sphere_prop(t_view *s);
void				clean_buttons(t_view *s);
void				clean_list_obj(t_view *s);
void				clean_light(t_view *s);
void				init_slider(t_view *s);
void				display_colored_rect(t_view *s);
void				slider_click_event(SDL_Keycode key, t_view *s, SDL_Event e);
void				slider_motion_event(SDL_Keycode key,
						t_view *s, SDL_Event e);
int					color_unite(int r, int g, int b);
void				open_scene(t_view *s);
float				par_input();
void				xxx(int num, t_view *s);
t_figure			*detect_figure(t_view *s);
t_col				col_parse(int col);
void				data_init(t_view *s);
void				init_prop(t_view *s);
void				get_properties(t_view *s);
void				get_init_prop(t_view *s);
void				clean_ic_prop(t_view *s);
void				print_ic_prop(t_view *s);
void				init_ic_prop(t_view *s);
void				ic_prop(t_view *s);
void				plane_prop(t_view *s);
void				init_plane_prop(t_view *s);
void				print_pl_prop(t_view *s);
void				clean_plane_prop(t_view *s);
void				clean_triangle_prop(t_view *s);
void				print_triangle_prop(t_view *s);
void				triangle_init_prop(t_view *s);
void				triangle_prop(t_view *s);
void				cone_prop(t_view *s);
void				init_cone_prop(t_view *s);
void				print_cone_prop(t_view *s);
void				clean_cone_prop(t_view *s);
void				cube_prop(t_view *s);
void				init_cube_prop(t_view *s);
void				print_cube_prop(t_view *s);
void				clean_cube_prop(t_view *s);
void				quadraate_prop(t_view *s);
void				init_quadraate_prop(t_view *s);
void				print_quadraate_prop(t_view *s);
void				clean_quadraate_prop(t_view *s);
void				elips_prop(t_view *s);
void				init_elips_prop(t_view *s);
void				print_elips_prop(t_view *s);
void				clean_elips_prop(t_view *s);
void				parab_prop(t_view *s);
void				init_parab_prop(t_view *s);
void				print_parab_prop(t_view *s);
void				clean_parab_prop(t_view *s);
SDL_Rect			*select_rect(t_view *s);
int					select_num(t_view *s);
void				save_sphere(t_view *s, int num);
t_read_prop			*read_apply_prop();
void				save_triangle(t_view *s, int num);
void				save_cylinder(t_view *s, int num);
void				save_plane(t_view *s, int num);
void				save_cube(t_view *s, int num);
void				save_cone(t_view *s, int num);
void				save_parab(t_view *s, int num);
void				save_quadr(t_view *s, int num);
void				save_elips(t_view *s, int num);
int					rt_figure(t_view *s, int x, int y);
void				light_properties(t_view *s);
void				init_light_prop(t_view *s);
void				print_light_prop(t_view *s);
void				clean_light_prop(t_view *s);
void				xxx_light(int num, t_view *s);
SDL_Rect			*select_rect_light(t_view *s);
int					select_li_num(t_view *s);
void				delete_init_cl(t_view *s);
void				view_init(t_view *view, const char *filename);
void				del_list(t_view *s);
void				light_am_properties(t_view *s);
void				init_am_light_prop(t_view *s);
void				print_am_light_prop(t_view *s);
void				clean_am_light_prop(t_view *s);
void				light_dir_properties(t_view *s);
void				init_dir_light_prop(t_view *s);
void				print_dir_light_prop(t_view *s);
void				clean_dir_light_prop(t_view *s);
void				default_sphere_init(t_view *view);
void				default_plane_init(t_view *view);
void				default_cylinder_init(t_view *view);
void				default_helper_figures(t_view *view, t_figure *figure);
void				default_cone_init(t_view *view);
void				default_elipsoid_init(t_view *view);
void				default_paraboloid_init(t_view *view);
void				default_cube_init(t_view *view);
void				default_quadrate_init(t_view *view);
void				default_triangle_init(t_view *view);
int					mirror_val();
void				default_helper_lights(t_view *view, t_light *light);
void				default_am_light(t_view *view);
void				default_point_light(t_view *view);
void				default_dir_light(t_view *view);
void				screenshot(t_view *s);
unsigned int		*array_ret();
void				redraw(t_view *s);
int					texture_val();
void				scroll_down(t_view *s, SDL_Event e);
void				cube_prop3(t_view *s);
void				ligit_type_prop(t_view *s, int num);
void				sdl_img_err(void);
void				triangle_init_prop2(t_view *s);
SDL_Surface			*get_valid_texture(char *file);
void				sdl_texture_valid_error(void);
int					refract_val(void);
void				triangle_prop3(t_view *s);

#endif
