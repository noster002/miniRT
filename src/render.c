/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:55:21 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/23 02:13:16 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
	return (0);
}

int	render(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_height)
	{
		j = -1;
		while (++j < g_width)
			img_pixel_put(&data->img, j, i, raytracer(data, j, i));
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.mlx_img, \
		0, 0);
	return (0);
}
