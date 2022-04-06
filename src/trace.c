/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:53:51 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/31 15:18:37 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	intersect(t_scene *scene, t_vector ray, int i, t_position *hit_p)
{
	int	hit;

	hit = 0;
	if (scene->object[i].identifier == sphere)
		hit = hit_sphere(scene, ray, i, hit_p);
	else if (scene->object[i].identifier == plane)
		hit = hit_plane(scene, ray, i, hit_p);
	else if (scene->object[i].identifier == cylinder)
		hit = hit_cylinder(scene, ray, i, hit_p);
	return (hit);
}

int	trace_shadow_ray(t_scene *scene, t_vector shadow_ray, t_object o_hit)
{
	double		distance_pp;
	double		distance_lp1;
	double		distance_lp2;
	t_position	point;
	int			i;

	i = -1;
	while (++i < scene->object_count)
	{
		if (intersect(scene, shadow_ray, i, &point))
		{
			distance_pp = veclen(get_vector(scene->camera.position, point));
			distance_lp1 = veclen(get_vector(point, scene->light.position));
			distance_lp2 = veclen(get_vector(scene->camera.position, \
							scene->light.position));
			if (o_hit.identifier == plane && scene->object[i].identifier \
				== plane && distance_pp < 0.000000000001)
				distance_pp = INFINITY;
			if (distance_pp <= distance_lp2 && distance_lp1 < distance_lp2)
				return (1);
		}
	}
	return (0);
}

int	trace_ray(t_scene *scene, t_vector ray, t_object *object, t_position *hit_p)
{
	double		min_distance;
	double		distance;
	t_position	point;
	int			i;
	int			hit;

	min_distance = INFINITY;
	i = -1;
	hit = 0;
	while (++i < scene->object_count)
	{
		if (intersect(scene, ray, i, &point))
		{
			distance = veclen(get_vector(scene->camera.position, point));
			if (distance < min_distance)
			{
				*object = scene->object[i];
				*hit_p = point;
				min_distance = distance;
				hit = 1;
			}
		}
	}
	return (hit);
}
