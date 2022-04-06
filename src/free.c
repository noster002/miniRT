/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:21:01 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/11 17:27:00 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_double_ptr(char **freeable)
{
	int	e;

	e = -1;
	while (freeable[++e])
		free(freeable[e]);
	free(freeable);
}
