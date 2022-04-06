/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosterme <nosterme@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:21:38 by nosterme          #+#    #+#             */
/*   Updated: 2021/12/07 12:52:44 by nosterme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_search_char(const char *s, int c)
{
	while (*s != 0)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	count;
	int		i;

	count = ft_strlen(s);
	i = 0;
	d = (char *)malloc(count + 1);
	if (d != 0)
	{
		while (count > 0)
		{
			d[i] = s[i];
			i++;
			count--;
		}
		d[i] = 0;
	}
	return (d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	count;

	count = 0;
	if (s == 0)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	substr = (char *)malloc((len + 1) * sizeof(*s));
	if (substr != 0)
	{
		while (count < len)
		{
			substr[count] = s[start + count];
			count++;
		}
		substr[count] = 0;
	}
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)malloc(len_s1 + len_s2 + 1);
	len_s1 = 0;
	len_s2 = 0;
	if (new_str != 0)
	{
		while (s1[len_s1] != 0)
		{
			new_str[len_s1] = s1[len_s1];
			len_s1++;
		}
		while (s2[len_s2] != 0)
		{
			new_str[len_s1 + len_s2] = s2[len_s2];
			len_s2++;
		}
		new_str[len_s1 + len_s2] = 0;
	}
	return (new_str);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}
