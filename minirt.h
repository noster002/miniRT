/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:53:21 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/04 16:34:30 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "mlx_linux/mlx.h"

/*
 * Enums
 */

enum	e_screen
{
	g_width = 1280,
	g_height = 720
};

enum	e_element
{
	ambience = 1,
	camera,
	light,
	sphere,
	plane,
	cylinder
};

/*
 * Structs
 */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct s_position
{
	double	x;
	double	y;
	double	z;
}			t_position;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_object
{
	int			identifier;
	t_position	position;
	t_vector	vector;
	double		diameter;
	double		height;
	t_color		color;
}				t_object;

typedef struct s_light
{
	t_position	position;
	double		ratio;
	int			exists;
}				t_light;

typedef struct s_camera
{
	t_position	position;
	t_vector	vector;
	double		fov;
	int			exists;
}				t_camera;

typedef struct s_ambience
{
	double	ratio;
	t_color	color;
	int		exists;
}			t_ambience;

typedef struct s_scene
{
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	t_object	*object;
	int			object_count;
}				t_scene;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	img;
	t_scene	*scene;
}			t_data;

/*
 * Minilibx
 */

void			start_raytracing(t_scene *scene);
int				key_hook(int keycode, t_data *data);
int				destroy_hook(t_data *data);

/*
 * Input
 */

t_scene			get_input(char *file);
int				set_scene(t_scene *scene, char **argv, int argc);
int				set_int(char *str, int *i);
int				set_double(char *str, double *d);
int				set_position(char *coordinates, t_position *position);
int				set_vector(char *coordinates, t_vector *vector);
int				set_color(char *code, t_color *color);
int				set_sphere(t_scene *scene, char **argv, int argc);
int				set_plane(t_scene *scene, char **argv, int argc);
int				set_cylinder(t_scene *scene, char **argv, int argc);

/*
 * Render
 */

int				render(t_data *data);
int				raytracer(t_data *data, int x, int y);
t_vector		get_ray(t_data *data, int x, int y);
int				trace_ray(t_scene *scene, t_vector ray, \
					t_object *object, t_position *hit_p);
int				hit_sphere(t_scene *scene, t_vector ray, \
					int i, t_position *hit_p);
int				hit_plane(t_scene *scene, t_vector ray, \
					int i, t_position *hit_p);
int				hit_cylinder(t_scene *scene, t_vector ray, \
					int i, t_position *hit_p);
double			check_hit(t_scene *scene, t_vector ray, int i, double *pq);
int				shadow_ray(t_scene *scene, t_vector ray, t_object o_hit, \
					t_position p_hit);
int				trace_shadow_ray(t_scene *scene, t_vector shadow_ray, \
					t_object o_hit);
double			get_ratio_sphere(t_position camera, t_vector shadow_ray, \
					t_object o_hit, t_position p_hit);
double			get_ratio_plane(t_vector ray, t_vector shadow_ray, \
					t_object o_hit);
double			get_ratio_cylinder(t_vector ray, t_vector shadow_ray, \
					t_object o_hit, t_position p_hit);

/*
 * Math
 */

double			dot(t_vector a, t_vector b);
t_vector		cross(t_vector a, t_vector b);
double			veclen(t_vector v);
t_vector		normalize(t_vector v);
int				linear_independent(t_vector a, t_vector b);
t_vector		get_vector(t_position p, t_position q);
t_vector		ptov(t_position p);
t_vector		scale_vector(t_vector v, double scale);
t_position		shift_position(t_position p, t_vector v);
t_vector		add_vector(t_vector u, t_vector v);

/*
 * Utils
 */

double			ft_atod(char *str);
int				ft_ptrnbr(char **argv);
void			free_double_ptr(char **freeable);
int				get_color(t_color color);
t_color			add_ratio(t_color color, double ratio);

#endif