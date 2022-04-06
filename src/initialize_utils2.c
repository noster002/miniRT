/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:14:23 by nosterme          #+#    #+#             */
/*   Updated: 2022/04/05 21:13:34 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	set_sphere(t_scene *scene, char **argv, int argc)
{
	t_object	*object;
	int			count;
	int			ret;

	if (argc != 4)
		return (1);
	object = (t_object *)malloc((scene->object_count + 1) * sizeof(*object));
	if (!object)
		return (1);
	count = -1;
	while (++count < scene->object_count)
		object[count] = scene->object[count];
	object[count].identifier = sphere;
	ret = set_position(argv[1], &object[count].position);
	ret += set_double(argv[2], &object[count].diameter);
	if (object[count].diameter < 0)
		ret++;
	ret += set_color(argv[3], &object[count].color);
	free(scene->object);
	scene->object = object;
	scene->object_count++;
	return (ret);
}

int	set_plane(t_scene *scene, char **argv, int argc)
{
	t_object	*object;
	int			count;
	int			ret;

	if (argc != 4)
		return (1);
	object = (t_object *)malloc((scene->object_count + 1) * sizeof(*object));
	if (!object)
		return (1);
	count = -1;
	while (++count < scene->object_count)
		object[count] = scene->object[count];
	object[count].identifier = plane;
	ret = set_position(argv[1], &object[count].position);
	ret += set_vector(argv[2], &object[count].vector);
	if (veclen(object[count].vector) != 1)
		ret++;
	ret += set_color(argv[3], &object[count].color);
	free(scene->object);
	scene->object = object;
	scene->object_count++;
	return (ret);
}

int	set_cylinder(t_scene *scene, char **argv, int argc)
{
	t_object	*object;
	int			count;
	int			ret;

	if (argc != 6)
		return (1);
	object = (t_object *)malloc((scene->object_count + 1) * sizeof(*object));
	if (!object)
		return (1);
	count = -1;
	while (++count < scene->object_count)
		object[count] = scene->object[count];
	object[count].identifier = cylinder;
	ret = set_position(argv[1], &object[count].position);
	ret += set_vector(argv[2], &object[count].vector);
	ret += set_double(argv[3], &object[count].diameter);
	ret += set_double(argv[4], &object[count].height);
	if (veclen(object[count].vector) != 1 || object[count].diameter < 0 || \
		object[count].height < 0)
		ret++;
	ret += set_color(argv[5], &object[count].color);
	free(scene->object);
	scene->object = object;
	scene->object_count++;
	return (ret);
}
