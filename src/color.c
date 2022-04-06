/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:23:48 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/28 20:21:18 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	add_ratio(t_color color, double ratio_d)
{
	t_color	rgb;
	int		ratio_i;

	ratio_i = (int)(ratio_d * 1000000);
	rgb.r = ((color.r * ratio_i) / 1000000) & 0xff;
	rgb.g = ((color.g * ratio_i) / 1000000) & 0xff;
	rgb.b = ((color.b * ratio_i) / 1000000) & 0xff;
	return (rgb);
}

int	get_color(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
