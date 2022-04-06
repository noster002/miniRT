/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:28:28 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/22 14:15:03 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	get_element(char *identifier)
{
	int	len;

	len = ft_strlen(identifier);
	if (len == 1)
	{
		if (identifier[0] == 'A')
			return (ambience);
		else if (identifier[0] == 'C')
			return (camera);
		else if (identifier[0] == 'L')
			return (light);
	}
	else if (len == 2)
	{
		if (identifier[0] == 's' && identifier[1] == 'p')
			return (sphere);
		else if (identifier[0] == 'p' && identifier[1] == 'l')
			return (plane);
		else if (identifier[0] == 'c' && identifier[1] == 'y')
			return (cylinder);
	}
	return (0);
}

static int	set_ambience(t_scene *scene, char **argv, int argc)
{
	int	ret;

	if (scene->ambience.exists || argc != 3)
		return (1);
	ret = set_double(argv[1], &scene->ambience.ratio);
	if (scene->ambience.ratio < 0.0 || scene->ambience.ratio > 1.0)
		ret++;
	ret += set_color(argv[2], &scene->ambience.color);
	scene->ambience.exists = 1;
	return (ret);
}

static int	set_camera(t_scene *scene, char **argv, int argc)
{
	int	ret;

	if (scene->camera.exists || argc != 4)
		return (1);
	ret = set_position(argv[1], &scene->camera.position);
	ret += set_vector(argv[2], &scene->camera.vector);
	if (veclen(scene->camera.vector) != 1)
		ret++;
	ret += set_double(argv[3], &scene->camera.fov);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		ret++;
	scene->ambience.exists = 1;
	return (ret);
}

static int	set_light(t_scene *scene, char **argv, int argc)
{
	int	ret;

	if (scene->light.exists || argc != 3)
		return (1);
	ret = set_position(argv[1], &scene->light.position);
	ret += set_double(argv[2], &scene->light.ratio);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		ret++;
	scene->light.exists = 1;
	return (ret);
}

int	set_scene(t_scene *scene, char **argv, int argc)
{
	int	element;
	int	status;

	if (argc < 1)
		return (1);
	element = get_element(argv[0]);
	status = 1;
	if (element == ambience)
		status = set_ambience(scene, argv, argc);
	else if (element == camera)
		status = set_camera(scene, argv, argc);
	else if (element == light)
		status = set_light(scene, argv, argc);
	else if (element == sphere)
		status = set_sphere(scene, argv, argc);
	else if (element == plane)
		status = set_plane(scene, argv, argc);
	else if (element == cylinder)
		status = set_cylinder(scene, argv, argc);
	return (status);
}
