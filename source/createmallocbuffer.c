/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createmallocbuffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:51:20 by fschuh            #+#    #+#             */
/*   Updated: 2024/03/24 19:55:50 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	getdictlength(const char *filename)
{
	int		fd;
	int		bytecount;
	char	buffer[1024];
	ssize_t	bytesread;

	fd = open(filename, O_RDONLY);
	bytecount = 0;
	if (fd == -1) 
	{
		perror("Error opening file");
		return (-1);
	}
	while ((bytesread = read(fd, buffer, sizeof(buffer))) > 0)
	{
	//	bytesread = read(fd, buffer, sizeof(buffer));
		bytecount += bytesread;
	}
	close(fd);
	return (bytecount);
}

int	createmallocbuffer(int dictsize, char *buffer, int fd)
{
	ssize_t	bytesread;

	bytesread = read(fd, buffer, dictsize);
	if (bytesread == -1)
	{
		write(2, "Dict Error\n", 11);
		close(fd);
		return (-1);
	}
	buffer[dictsize] = '\0';
	return (1);
}
