/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:20:24 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/04 16:41:36 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_ratio_sphere(t_position camera, t_vector shadow_ray, \
						t_object o_hit, t_position p_hit)
{
	t_vector	norm;
	t_vector	tangent;
	double		cos_a;

	if (pow(veclen(get_vector(o_hit.position, camera)), 2) < \
		pow(o_hit.diameter / 2, 2))
		return (0);
	norm = cross(get_vector(p_hit, o_hit.position), shadow_ray);
	tangent = cross(norm, get_vector(p_hit, o_hit.position));
	cos_a = (dot(tangent, shadow_ray)) / (veclen(tangent) * veclen(shadow_ray));
	return (acos(cos_a) * 2 / M_PI);
}

double	get_ratio_plane(t_vector ray, t_vector shadow_ray, t_object o_hit)
{
	t_vector	norm;
	t_vector	plane_v;
	t_vector	tangent;
	double		cos_a;

	ray = scale_vector(ray, -1);
	if (acos((dot(o_hit.vector, shadow_ray)) / \
		(veclen(o_hit.vector) * veclen(shadow_ray))) * 180 / M_PI < 90)
		norm = scale_vector(o_hit.vector, -1);
	else
		norm = o_hit.vector;
	if (acos((dot(ray, norm)) / (veclen(ray) * veclen(norm))) * 180 / M_PI \
		<= 90)
		return (0);
	plane_v = cross(norm, shadow_ray);
	tangent = cross(plane_v, norm);
	cos_a = (dot(tangent, shadow_ray)) / (veclen(tangent) * veclen(shadow_ray));
	return (acos(cos_a) * 2 / M_PI);
}

static int	cylinder_shadow(t_vector u, t_vector v, t_vector w)
{
	if (acos((dot(u, v)) / (veclen(u) * veclen(v))) * 180 / M_PI <= 90 && \
		acos((dot(u, w)) / (veclen(u) * veclen(w))) * 180 / M_PI >= 90)
		return (1);
	if (acos((dot(u, v)) / (veclen(u) * veclen(v))) * 180 / M_PI >= 90 && \
		acos((dot(u, w)) / (veclen(u) * veclen(w))) * 180 / M_PI <= 90)
		return (1);
	return (0);
}

double	get_ratio_cylinder(t_vector ray, t_vector shadow_ray, \
						t_object o_hit, t_position p_hit)
{
	double		scale;
	t_position	mid;
	t_vector	norm;
	t_vector	tangent;
	double		cos_a;

	ray = scale_vector(ray, -1);
	scale = -1 * dot(get_vector(p_hit, o_hit.position), o_hit.vector) / \
		pow(veclen(o_hit.vector), 2);
	mid = shift_position(o_hit.position, scale_vector(o_hit.vector, scale));
	if (cylinder_shadow(get_vector(p_hit, mid), ray, shadow_ray))
		return (0);
	norm = cross(get_vector(p_hit, mid), shadow_ray);
	tangent = cross(norm, get_vector(p_hit, mid));
	cos_a = (dot(tangent, shadow_ray)) / (veclen(tangent) * veclen(shadow_ray));
	return (acos(cos_a) * 2 / M_PI);
}
