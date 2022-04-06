/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:21:34 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/31 18:07:38 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
/*
static double	get_vecratio_x_width_based(double half_fov, int x)
{
	return (tan(half_fov * M_PI / 180) - \
		(x + 0.5) * tan(half_fov * M_PI / 180) / (g_width * 0.5));
}

static double	get_vecratio_y_height_based(double half_hov, int y)
{
	return (tan(half_hov * 1.2 * M_PI / 180) - \
		(y + 0.5) * tan(half_hov * 1.2 * M_PI / 180) / (g_height * 0.5));
}*/

static double	get_vecratio_x_angle_based(double half_fov, int x)
{
	return (tan((half_fov - \
		(x + 0.5) * (half_fov / (g_width * 0.5))) * M_PI / 180));
}

static double	get_vecratio_y_angle_based(double half_hov, int y)
{
	return (tan((half_hov - \
		(y + 0.5) * (half_hov / (g_height * 0.5))) * M_PI / 180));
}

static void	set_picture(t_data *data, t_vector *vec_x, t_vector *vec_y)
{
	t_vector	vec_z;

	set_vector("0,0,1", &vec_z);
	if (linear_independent(data->scene->camera.vector, vec_z))
		*vec_x = normalize(cross(vec_z, data->scene->camera.vector));
	else
		set_vector("1,0,0", vec_x);
	*vec_y = normalize(cross(data->scene->camera.vector, *vec_x));
}

static t_position	set_pixel(t_data *data, t_vector *pic, int x, int y)
{
	t_position	pixel;
	double		width;
	double		height;

	width = get_vecratio_x_angle_based(data->scene->camera.fov * 0.5, x);
	height = get_vecratio_y_angle_based(data->scene->camera.fov * 0.5 * \
										g_height / g_width, y);
	pixel = shift_position(data->scene->camera.position, \
			add_vector(data->scene->camera.vector, \
			add_vector(scale_vector(pic[0], width), \
						scale_vector(pic[1], height))));
	return (pixel);
}

t_vector	get_ray(t_data *data, int x, int y)
{
	t_vector	ray;
	t_position	pixel;
	t_vector	pic[2];

	set_picture(data, &pic[0], &pic[1]);
	pixel = set_pixel(data, pic, x, y);
	ray = normalize(get_vector(data->scene->camera.position, pixel));
	return (ray);
}
