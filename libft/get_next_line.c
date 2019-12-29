/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:49:32 by fgeruss           #+#    #+#             */
/*   Updated: 2019/08/23 15:43:52 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line.h"

/*
** Записываем в переменную line содержимое file
** file очищаем полностью
** и выделяем для него память под размер предыдущего file
** только без строчки line
*/

int	create_line(int fd, char **ptr, char **line)
{
    size_t	len;
    char	*buffer;

    len = 0;
    if (*ptr[fd] == '\0')
        return (0);
    while (ptr[fd][len] != '\n' && ptr[fd][len] != '\0')
        len++;
    if (!(*line = ft_strsub(ptr[fd], 0, len)))
        return (-1);
    if (!(buffer = ft_strdup(ptr[fd] + len + 1)))
        return (-1);
    free(ptr[fd]);
    if (!(ptr[fd] = ft_strdup(buffer)))
        return (-1);
    free(buffer);
    return (1);
}

int	ft_check_slash(char *buffer, char **ptr, int fd)
{
    buffer = ptr[fd];
    if (!(ptr[fd] = ft_strjoin(buffer, "\n")))
        return (-1);
    free(buffer);
    return (0);
}

int	readfile(const int fd, char **line, char **ptr, char *buff)
{
    char	*buffer;
    char	*first;
    int		ret;

    while ((first = ft_strchr(ptr[fd], '\n')) == NULL)
    {
        if ((ret = read(fd, buff, BUFF_SIZE)) == 0 && *ptr[fd] != '\0')
            if (ft_check_slash(buffer, ptr, fd) < 0)
                return (-1);
        if (ret == 0)
            break ;
        buff[ret] = '\0';
        buffer = ptr[fd];
        if (!(ptr[fd] = ft_strjoin(buffer, buff)))
            return (-1);
        free(buffer);
        free(first);
    }
    free(buff);
    return (create_line(fd, ptr, line));
}

int	get_next_line(const int fd, char **line)
{
    static char	*ptr[MAX_FD + 1];
    char		*buff;

    if ((buff = (char*)malloc(BUFF_SIZE + 1)) == NULL)
        return (-1);
    if (fd == -1 || (read(fd, buff, 0) == -1) || fd > MAX_FD)
    {
        free(buff);
        return (-1);
    }
    if (ptr[fd] == NULL)
        ptr[fd] = ft_strnew(1);
    return (readfile(fd, line, ptr, buff));
}
