/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:57:37 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/29 23:40:07 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	hit_plane(t_scene *scene, t_vector ray, int i, t_position *hit_p)
{
	double	a;
	double	b;

	a = dot(ray, scene->object[i].vector);
	b = dot(get_vector(scene->object[i].position, scene->camera.position), \
			scene->object[i].vector);
	if ((-1 * b / a < 0) || (dot(ray, scene->object[i].vector) == 0 && \
		dot(get_vector(scene->camera.position, scene->object[i].position), \
			scene->object[i].vector) != 0))
		return (0);
	else if ((-1 * b / a == 0) || (dot(ray, scene->object[i].vector) == 0 && \
		dot(get_vector(scene->camera.position, scene->object[i].position), \
			scene->object[i].vector) == 0))
		*hit_p = scene->camera.position;
	else
		*hit_p = shift_position(scene->camera.position, \
								scale_vector(ray, -1 * b / a));
	return (1);
}
