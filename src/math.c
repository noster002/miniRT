/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:51:59 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/18 15:27:03 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	veclen(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vector	normalize(t_vector v)
{
	t_vector	res;
	double		len;

	len = veclen(v);
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

int	linear_independent(t_vector a, t_vector b)
{
	double	check;

	if (a.x == 0 && b.x == 0)
		check = 0;
	else if (a.x && b.x)
		check = a.x / b.x;
	else
		return (1);
	if (a.y == 0 && b.y == 0 && check == 0 && a.z && b.z)
		return (0);
	else if (a.y && b.y && check && check == a.y / b.y)
	{
		if ((a.z == 0 && b.z == 0) || (a.z && b.z && check == a.z / b.z))
			return (0);
		return (1);
	}
	else if (a.y && b.y && check == 0)
	{
		check = a.y / b.y;
		if ((a.z == 0 && b.z == 0) || (a.z && b.z && check == a.z / b.z))
			return (0);
		return (1);
	}
	return (1);
}
