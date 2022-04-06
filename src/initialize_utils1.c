/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:13:05 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/17 17:30:10 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	set_int(char *str, int *i)
{
	int	count;

	count = -1;
	*i = 0;
	if (str[0] == '-' || str[0] == '+')
		count++;
	while (str[++count])
	{
		if (!ft_isdigit(str[count]))
			return (1);
	}
	*i = ft_atoi(str);
	return (0);
}

int	set_double(char *str, double *d)
{
	int	count;

	count = -1;
	*d = 0;
	if (str[0] == '-' || str[0] == '+')
		count++;
	while (str[++count])
	{
		if (!ft_isdigit(str[count]))
			break ;
	}
	if (str[count] == '.' && count > 0 && ft_isdigit(str[count - 1]))
	{
		while (str[++count])
		{
			if (!ft_isdigit(str[count]))
				return (1);
		}
	}
	else if (str[count])
		return (1);
	*d = ft_atod(str);
	return (0);
}

int	set_position(char *coordinates, t_position *position)
{
	char	**xyz;
	int		ret;

	xyz = ft_split(coordinates, ',');
	if (!xyz)
		return (1);
	if (ft_ptrnbr(xyz) != 3)
	{
		free_double_ptr(xyz);
		return (1);
	}
	ret = set_double(xyz[0], &position->x);
	ret += set_double(xyz[1], &position->y);
	ret += set_double(xyz[2], &position->z);
	free_double_ptr(xyz);
	return (ret);
}

int	set_vector(char *coordinates, t_vector *vector)
{
	char	**xyz;
	int		ret;

	xyz = ft_split(coordinates, ',');
	if (!xyz)
		return (1);
	if (ft_ptrnbr(xyz) != 3)
	{
		free_double_ptr(xyz);
		return (1);
	}
	ret = set_double(xyz[0], &vector->x);
	if (vector->x < -1 || vector->x > 1)
		ret++;
	ret += set_double(xyz[1], &vector->y);
	if (vector->y < -1 || vector->y > 1)
		ret++;
	ret += set_double(xyz[2], &vector->z);
	if (vector->z < -1 || vector->z > 1)
		ret++;
	free_double_ptr(xyz);
	return (ret);
}

int	set_color(char *code, t_color *color)
{
	char	**rgb;
	int		ret;

	rgb = ft_split(code, ',');
	if (!rgb)
		return (1);
	if (ft_ptrnbr(rgb) != 3)
	{
		free_double_ptr(rgb);
		return (1);
	}
	ret = set_int(rgb[0], &color->r);
	if (color->r < 0 || color->r > 255)
		ret++;
	ret += set_int(rgb[1], &color->g);
	if (color->g < 0 || color->g > 255)
		ret++;
	ret += set_int(rgb[2], &color->b);
	if (color->b < 0 || color->b > 255)
		ret++;
	free_double_ptr(rgb);
	return (ret);
}
