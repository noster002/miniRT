/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:13:17 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/31 15:45:43 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static double	get_pq(t_scene *scene, t_vector ray, int i, char pq)
{
	double	a;
	double	half_b;
	double	c;

	a = pow(veclen(ray), 2);
	half_b = dot(ray, get_vector(scene->object[i].position, \
		scene->camera.position));
	c = pow(veclen(get_vector(scene->object[i].position, \
		scene->camera.position)), 2) - \
		pow(scene->object[i].diameter / 2, 2);
	if (pq == 'p')
		return (-1 * half_b / a);
	else if (pq == 'q')
		return (c / a);
	return (0);
}

static double	check_hit_sphere(double *pq)
{
	double		root;
	double		scale1;
	double		scale2;

	root = pow(pq[0], 2) - pq[1];
	if (root == 0)
		return (pq[0]);
	else if (root > 0)
	{
		scale1 = pq[0] + sqrt(root);
		scale2 = pq[0] - sqrt(root);
		if (scale1 < 0.00000000001 && scale2 < 0.00000000001)
			return (NAN);
		else if (scale1 >= 0 && (scale1 < scale2 || scale2 < 0.00000000001))
			return (scale1);
		else if (scale2 >= 0 && (scale2 < scale1 || scale1 < 0.00000000001))
			return (scale2);
	}
	return (NAN);
}

int	hit_sphere(t_scene *scene, t_vector ray, int i, t_position *hit_p)
{
	double	pq[2];
	double	scale;

	pq[0] = get_pq(scene, ray, i, 'p');
	pq[1] = get_pq(scene, ray, i, 'q');
	scale = NAN;
	if (pow(pq[0], 2) - pq[1] < 0)
		return (0);
	scale = check_hit_sphere(pq);
	if (scale == NAN)
		return (0);
	*hit_p = shift_position(scene->camera.position, scale_vector(ray, scale));
	return (1);
}
