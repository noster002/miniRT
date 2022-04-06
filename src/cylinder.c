/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:35:40 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/27 19:52:54 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static double	get_half_b(t_scene *scene, t_vector ray, int i)
{
	return ((-1 * (pow(veclen(scene->object[i].vector), 2) * \
			pow(veclen(ray), 2) * dot(scene->object[i].vector, \
			get_vector(scene->object[i].position, scene->camera.position))) / \
			pow(dot(scene->object[i].vector, ray), 2)) + \
		((dot(scene->object[i].vector, get_vector(scene->object[i].position, \
			scene->camera.position)) * dot(ray, scene->object[i].vector)) / \
			dot(scene->object[i].vector, ray)) + \
		((pow(veclen(scene->object[i].vector), 2) * dot(ray, \
			get_vector(scene->object[i].position, scene->camera.position))) / \
			dot(scene->object[i].vector, ray)) - \
		(dot(scene->object[i].vector, get_vector(scene->object[i].position, \
			scene->camera.position))));
}

static double	get_c(t_scene *scene, t_vector ray, int i)
{
	return (((pow(veclen(ray), 2) * pow(dot(scene->object[i].vector, \
			get_vector(scene->object[i].position, scene->camera.position)), 2)) \
			/ (pow(dot(scene->object[i].vector, ray), 2))) - \
		((dot(scene->object[i].vector, get_vector(scene->object[i].position, \
			scene->camera.position)) * 2 * dot(ray, \
			get_vector(scene->object[i].position, scene->camera.position))) / \
			(dot(scene->object[i].vector, ray))) + \
		(pow(veclen(get_vector(scene->object[i].position, \
			scene->camera.position)), 2)) - \
		(pow(scene->object[i].diameter / 2, 2)));
}

static double	get_pq(t_scene *scene, t_vector ray, int i, char pq)
{
	double	a;
	double	half_b;
	double	c;

	a = ((pow(veclen(scene->object[i].vector), 4) * pow(veclen(ray), 2)) / \
			pow(dot(scene->object[i].vector, ray), 2)) - \
		((pow(veclen(scene->object[i].vector), 2) * 2 * \
			dot(ray, scene->object[i].vector)) / \
			dot(scene->object[i].vector, ray)) + \
		pow(veclen(scene->object[i].vector), 2);
	half_b = get_half_b(scene, ray, i);
	c = get_c(scene, ray, i);
	if (pq == 'p')
		return (-1 * half_b / a);
	else if (pq == 'q')
		return (c / a);
	return (0);
}

int	hit_cylinder(t_scene *scene, t_vector ray, int i, t_position *hit_p)
{
	double	pq[2];
	double	scale;

	pq[0] = get_pq(scene, ray, i, 'p');
	pq[1] = get_pq(scene, ray, i, 'q');
	if (pow(pq[0], 2) - pq[1] < 0)
		return (0);
	scale = check_hit(scene, ray, i, pq);
	if (scale == NAN)
		return (0);
	*hit_p = shift_position(scene->camera.position, scale_vector(ray, scale));
	return (1);
}
