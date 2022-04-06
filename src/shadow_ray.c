/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:24:46 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/02 21:16:54 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	pixel_color(t_scene *scene, t_color color_o, double ratio)
{
	int		ambient_c;
	t_color	light_color;
	t_color	ambient_color;

	light_color = add_ratio(color_o, ratio);
	ambient_color.r = scene->ambience.color.r - light_color.r;
	ambient_color.g = scene->ambience.color.g - light_color.g;
	ambient_color.b = scene->ambience.color.b - light_color.b;
	ambient_c = get_color(add_ratio(ambient_color, scene->ambience.ratio));
	return (ambient_c + get_color(light_color));
}

int	shadow_ray(t_scene *scene, t_vector ray, t_object o_hit, t_position p_hit)
{
	t_vector	shadow_ray;
	t_scene		new_scene;
	double		ratio;

	new_scene = *scene;
	new_scene.camera.position = p_hit;
	ratio = scene->light.ratio;
	shadow_ray = normalize(get_vector(p_hit, scene->light.position));
	if (trace_shadow_ray(&new_scene, shadow_ray, o_hit))
		return (pixel_color(scene, o_hit.color, 0));
	if (o_hit.identifier == sphere)
		ratio *= get_ratio_sphere(scene->camera.position, shadow_ray, \
									o_hit, p_hit);
	else if (o_hit.identifier == plane)
		ratio *= get_ratio_plane(ray, shadow_ray, o_hit);
	else if (o_hit.identifier == cylinder)
		ratio *= get_ratio_cylinder(ray, shadow_ray, o_hit, p_hit);
	return (pixel_color(scene, o_hit.color, ratio));
}
