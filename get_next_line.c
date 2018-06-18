/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tluzing <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:17:26 by tluzing           #+#    #+#             */
/*   Updated: 2018/06/18 09:54:17 by tluzing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"

int		read_line(char **stock_buff, char **line)
{
	char	*tmp;

	if ((tmp = ft_strchr(*stock_buff, '\n')))
	{
		*line = ft_strsub(*stock_buff, 0, tmp - *stock_buff);
		ft_strcpy(*stock_buff, tmp + 1);
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	int			bytes_size;
	char		buff[BUFF_SIZE + 1];
	static char	*stock_buff = NULL;

	if (stock_buff && read_line(&stock_buff, line))
		return (1);
	while ((bytes_size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes_size] = '\0';
		stock_buff = str_join(stock_buff, buff);
		if (read_line(&stock_buff, line))
			return (1);
	}
	if (bytes_size < 0)
		return (-1);
	if (stock_buff && *stock_buff)
	{
		*line = ft_strdup(stock_buff);
		ft_strdel(&stock_buff);
		return (1);
	}
	if (bytes_size)
		return (1);
	return (0);
}

char	*str_join(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*join;

	len1 = (str1) ? ft_strlen(str1) : 0;
	len2 = ft_strlen(str2);
	join = ft_strnew(len1 + len2);
	if (join)
	{
		if (str1)
			ft_memcpy(join, str1, len1);
		ft_memcpy(join + len1, str2, len2);
	}
	if (str1)
		ft_strdel(&str1);
	return (join);
}
