/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:29:46 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/02 17:03:09 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	raytracer(t_data *data, int x, int y)
{
	t_object	object;
	t_position	hit_point;
	t_vector	ray;
	int			rgb;

	rgb = 0;
	ray = get_ray(data, x, y);
	if (trace_ray(data->scene, ray, &object, &hit_point))
		rgb = shadow_ray(data->scene, ray, object, hit_point);
	return (rgb);
}
