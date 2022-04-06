/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:03:26 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/29 23:37:37 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	get_vector(t_position p, t_position q)
{
	t_vector	v;

	v.x = q.x - p.x;
	v.y = q.y - p.y;
	v.z = q.z - p.z;
	return (v);
}

t_vector	scale_vector(t_vector v, double scale)
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return (v);
}

t_position	shift_position(t_position p, t_vector v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return (p);
}

t_vector	add_vector(t_vector u, t_vector v)
{
	t_vector	res;

	res.x = u.x + v.x;
	res.y = u.y + v.y;
	res.z = u.z + v.z;
	return (res);
}
