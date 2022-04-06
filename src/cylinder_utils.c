/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:50:19 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/02 16:52:10 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static double	get_scale(t_scene *scene, t_vector ray, int i, double pq)
{
	return (((pq * (pow(veclen(scene->object[i].vector), 2))) - \
			(dot(scene->object[i].vector, get_vector(scene->object[i].position, \
			scene->camera.position)))) / \
			(dot(scene->object[i].vector, ray)));
}

static int	check_height(double height, double pq)
{
	if (pq >= 0 && pq < height)
		return (1);
	return (0);
}

static double	pq_formula(double min_half_p, double q, char root)
{
	if (root == '+')
		return (min_half_p + sqrt(pow(min_half_p, 2) - q));
	else if (root == '-')
		return (min_half_p - sqrt(pow(min_half_p, 2) - q));
	return (0);
}

double	check_hit(t_scene *scene, t_vector ray, int i, double *pq)
{
	double	scale1;
	double	scale2;

	if ((pow(pq[0], 2) - pq[1] == 0) && \
		check_height(scene->object[i].height, pq[0]))
		return (get_scale(scene, ray, i, pq[0]));
	else if (pow(pq[0], 2) - pq[1] > 0)
	{
		scale1 = get_scale(scene, ray, i, pq_formula(pq[0], pq[1], '+'));
		scale2 = get_scale(scene, ray, i, pq_formula(pq[0], pq[1], '-'));
		if (scale1 < 0.0001 && scale2 < 0.0001)
			return (NAN);
		else if (scale1 >= 0.0001 && check_height(scene->object[i].height, \
			pq_formula(pq[0], pq[1], '+')) && ((scale1 < scale2 || \
			scale2 <= 0.0001) || (check_height(scene->object[i].height, \
			pq_formula(pq[0], pq[1], '-')) == 0)))
			return (scale1);
		else if (scale2 >= 0.0001 && check_height(scene->object[i].height, \
			pq_formula(pq[0], pq[1], '-')) && ((scale2 < scale1 || \
			scale1 <= 0.0001) || (check_height(scene->object[i].height, \
			pq_formula(pq[0], pq[1], '+')) == 0)))
			return (scale2);
	}
	return (NAN);
}
