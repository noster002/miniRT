/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:40:43 by bkrebs            #+#    #+#             */
/*   Updated: 2022/03/29 19:06:30 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	check_filetype(char *argv[])
{
	int	len;

	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 't' && argv[1][len - 2] != 'r' &&
			argv[1][len - 3] != '.')
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc == 2 && check_filetype(argv))
	{
		scene = get_input(argv[1]);
		printf("good job!\n");
		start_raytracing(&scene);
	}
	else
		printf("Error\nWrong filetype.\n");
}
