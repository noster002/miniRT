/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:54:55 by bkrebs            #+#    #+#             */
/*   Updated: 2022/03/23 18:26:14 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	start_raytracing(t_scene *scene)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, g_width, g_height, "miniRT");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, g_width, g_height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, \
									&data.img.line_len, &data.img.endian);
	data.scene = scene;
	render(&data);
	mlx_hook(data.mlx_win, 17, 0L, destroy_hook, &data);
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return ;
}
