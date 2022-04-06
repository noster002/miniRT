/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:56:26 by nosterme          #+#    #+#             */
/*   Updated: 2022/03/22 14:39:27 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	err_open(char *file)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Neither a directory nor a file\n", 2);
	exit(1);
}

static int	err_read(int fd, t_scene *scene)
{
	close(fd);
	free(scene->object);
	ft_putstr_fd("Error\nCould not read file\n", 2);
	exit(1);
}

static int	err_process(int fd, char *line, t_scene *scene)
{
	int	i;

	i = 1;
	free(line);
	while (i)
	{
		i = get_next_line(fd, &line);
		free(line);
	}
	close(fd);
	free(scene->object);
	ft_putstr_fd("Error\nCould not process file\n", 2);
	exit(1);
}

static int	process_line(char *line, t_scene *scene)
{
	char	**argv;
	int		argc;
	int		ret;

	if (line[0] == '\0')
		return (0);
	argv = ft_split(line, ' ');
	argc = ft_ptrnbr(argv);
	ret = set_scene(scene, argv, argc);
	free_double_ptr(argv);
	return (ret);
}

t_scene	get_input(char *file)
{
	char	*line;
	t_scene	scene;
	int		fd;
	int		i;

	ft_memset(&scene, 0, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_open(file);
	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			err_read(fd, &scene);
		if (process_line(line, &scene))
			err_process(fd, line, &scene);
		free(line);
	}
	close(fd);
	return (scene);
}
