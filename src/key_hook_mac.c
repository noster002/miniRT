/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_mac.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:02:28 by bkrebs            #+#    #+#             */
/*   Updated: 2022/03/22 14:37:19 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	destroy_hook(t_data *data)
{
	free(data->scene->object);
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		destroy_hook(data);
	return (0);
}
