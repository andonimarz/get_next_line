/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:45:04 by amarzana          #+#    #+#             */
/*   Updated: 2022/05/31 17:17:01 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_cut_save(char *save)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		temp[j++] = save[i++];
	temp[j] = '\0';
	free(save);
	return (temp);
}

static char	*ft_get_line(char *save)
{
	int		i;
	char	*temp;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = -1;
	while (save[++i] && save[i] != '\n')
		temp[i] = save[i];
	if (save[i] == '\n')
	{
		temp[i] = save[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

static char	*ft_read(int fd, char *save, char *buffer)
{
	ssize_t	len;

	len = 1;
	while (len > 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[len] = '\0';
		save = ft_strjoin(save, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*save[4096];
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	save[fd] = ft_read(fd, save[fd], buffer);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_cut_save(save[fd]);
	free(buffer);
	return (line);
}
