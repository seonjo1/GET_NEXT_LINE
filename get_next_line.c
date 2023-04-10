/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:39 by seonjo            #+#    #+#             */
/*   Updated: 2023/04/10 22:15:51 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_end(char *tmp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tmp[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	change_tmp(char *tmp, int end, int size)
{
	int	i;

	i = 0;
	while (end <= size)
	{
		tmp[i] = tmp[end];
		i = i + 1;
		end = end + 1;
	}
}

char	*ft_strnstr(char *src, char *tmp, int tmp_size)
{
	char	*dest;
	int		i;
	int		j;
	int		end;

	end = get_end(tmp, tmp_size);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + end + 1));
	if (dest == NULL)
		return (free_str(src));
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i = i + 1;
	}
	j = 0;
	while (j < end)
		dest[i++] = tmp[j++];
	dest[i] = '\0';
	change_tmp(tmp, end, tmp_size);
	free(src);
	return (dest);
}

char	*make_dest(char *tmp, int fd)
{
	char	*dest;
	int		read_num;

	dest = (char *)malloc(sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	if (tmp[0] != '\0')
		dest = ft_strnstr(dest, tmp, ft_strlen(tmp));
	if (dest == NULL)
		return (NULL);
	while (dest[0] == '\0' || dest[ft_strlen(dest) - 1] != '\n')
	{
		read_num = read(fd, tmp, BUFFER_SIZE);
		if (read_num == -1)
			return (free_str(dest));
		tmp[read_num] = '\0';
		if (read_num == 0)
			break ;
		dest = ft_strnstr(dest, tmp, read_num);
		if (dest == NULL)
			return (NULL);
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX + 1][BUFFER_SIZE + 1];
	char		tmp[BUFFER_SIZE + 1];
	char		*dest;
	int			i;

	if (fd > OPEN_MAX || fd < 0)
		return (NULL);
	i = -1;
	while (buffer[fd][++i] != '\0')
		tmp[i] = buffer[fd][i];
	tmp[i] = '\0';
	dest = make_dest(tmp, fd);
	if (dest == NULL)
	{
		buffer[fd][0] = '\0';
		return (NULL);
	}
	i = -1;
	while (tmp[++i] != '\0')
		buffer[fd][i] = tmp[i];
	buffer[fd][i] = '\0';
	if (dest[0] == '\0')
		return (free_str(dest));
	return (dest);
}
