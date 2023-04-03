/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:39 by seonjo            #+#    #+#             */
/*   Updated: 2023/04/03 23:00:22 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len = len + 1;
	return (len);
}

int	get_end(char *src2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (src2[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	change_buffer(char *src2, int end, int n)
{
	int	i;

	i = 0;
	while (end <= n)
	{
		src2[i] = src2[end];
		i = i + 1;
		end = end + 1;
	}
}

char	*ft_strnstr(char *src1, char *src2, int n)
{
	char	*dest;
	int		i;
	int		j;
	int		end;

	i = 0;
	end = get_end(src2, n);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src1) + end + 1));
	if (dest == NULL)
	{
		free(src1);
		return (NULL);
	}
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i = i + 1;
	}
	j = 0;
	while (j < end)
	{
		dest[i++] = src2[j++];
		if (dest[i - 1] == '\n')
			break ;
	}
	dest[i] = '\0';
	change_buffer(src2, end, n);
	free(src1);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX + 1][BUFFER_SIZE + 1];
	char		tmp[BUFFER_SIZE + 1];
	char		*dest;
	int			read_num;
	int			i;

	if (fd > OPEN_MAX || fd < 0)
		return (NULL);
	i = 0;
	while (buffer[fd][i] != '\0')
	{
		tmp[i] = buffer[fd][i];
		i++;
	}
	tmp[i] = '\0';
	dest = (char *)malloc(sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	if (tmp[0] != '\0')
		dest = ft_strnstr(dest, tmp, ft_strlen(tmp));
	while (dest[0] == '\0' || dest[ft_strlen(dest) - 1] != '\n')
	{
		read_num = read(fd, &tmp, BUFFER_SIZE);
		if (read_num == -1)
		{
			buffer[fd][0] = '\0';
			free(dest);
			return (NULL);
		}
		tmp[read_num] = '\0';
		if (read_num == 0)
			break ;
		dest = ft_strnstr(dest, tmp, read_num);
	}
	i = 0;
	while (tmp[i] != '\0')
	{
		buffer[fd][i] = tmp[i];
		i = i + 1;
	}
	buffer[fd][i] = '\0';
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}
