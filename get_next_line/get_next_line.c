/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:21:33 by nosterme          #+#    #+#             */
/*   Updated: 2021/06/17 10:43:34 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fill_lines(char **line, char *stat_line)
{
	int		len;
	char	*tmp;

	len = 0;
	while (stat_line[len] != '\n' && stat_line[len] != '\0')
		len++;
	if (stat_line[len] == '\n')
	{
		*line = ft_substr(stat_line, 0, len);
		tmp = ft_strdup(&stat_line[len + 1]);
		free(stat_line);
		stat_line = tmp;
	}
	else
	{
		*line = stat_line;
		stat_line = 0;
	}
	return (stat_line);
}

int	ft_return(char **line, char **stat_line, int ret)
{
	if (ret < 0)
		return (-1);
	else if (*stat_line == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
	{
		*stat_line = ft_fill_lines(line, *stat_line);
		if (*stat_line == 0)
			return (0);
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*stat_line[1024];
	char		*buf;
	char		*tmp;
	int			ret;

	if (fd < 0 || line == 0 || BUFFER_SIZE < 0)
		return (-1);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == 0)
		return (-1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = 0;
		if (stat_line[fd] == 0)
			stat_line[fd] = ft_strdup("");
		tmp = ft_strjoin(stat_line[fd], buf);
		free(stat_line[fd]);
		stat_line[fd] = tmp;
		while (!(ft_str_search_char(buf, '\n')))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (ft_return(line, &stat_line[fd], ret));
}
