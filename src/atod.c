/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:07:23 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/17 17:31:27 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static double	get_sign(char sign)
{
	if (sign == '-')
		return (-1);
	return (1);
}

double	ft_atod(char *str)
{
	double	d;
	int		count;
	double	power;
	int		flag;

	d = 0;
	count = 0;
	power = 0;
	flag = 0;
	if (str[count] == '-' || str[count] == '+')
		count++;
	while (str[count] && ft_isdigit(str[count]))
	{
		d = d * 10 + (str[count] - '0');
		if (flag == 1)
			power--;
		if (str[++count] == '.')
		{
			if (flag == 0)
				count++;
			flag = 1;
		}
	}
	return (d * pow(10, power) * get_sign(str[0]));
}
