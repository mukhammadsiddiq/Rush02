/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:46:40 by fschuh            #+#    #+#             */
/*   Updated: 2024/03/24 21:12:03 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	fillwithnull(char dictionary[60][2][45]);
void 	printrows(char dictionary[60][2][45]);
int		ft_importdict(char	*dictname, char	*searchstring);
int		getdictlength(const char *filename);
int		createmallocbuffer(int dictsize, char *buffer, int fd);
void	ft_putstr(char *string);
void	ft_searchdict(char	*searchstring, char ***dictionary);
void	fillDictionaryArray(char *buffer, char dictionary[60][2][45], char *searchstring);
char	**ft_inputcheck(int argc, char **argv);
int	ft_strcmp(char *s1, char *s2);

int	main(int argc, char	**argv)
{
	// TODO check the argv and process it 
	ft_inputcheck(argc, argv);
	if (argc == 1)
		write(2, "No input args\n", 14);
	ft_importdict(argv[1], argv[2]); // and return the array
	

	
	// TODO check against dictionary
	// ft_seach(0)

}

int		ft_importdict(char	*dictname, char	*searchstring)
{
	int		dictsize;
	int		fd;
	char	*buffer;
	char	dictionary[60][2][45];
	
	fd = open(dictname, O_RDONLY);
	if (fd == -1)
		return (-1);
	dictsize = getdictlength(dictname);
	buffer = (char *)malloc(dictsize + 1);
	if (buffer == NULL)
	{
		write(2, "Dict Error\n", 12);
		close(fd);
		return (-1);
	}
	createmallocbuffer (dictsize, buffer, fd);
	buffer[dictsize] = '\0'; 
    fillwithnull(dictionary);
	fillDictionaryArray(buffer, dictionary, searchstring);
	free(buffer); 
	close(fd);
	return (1);
} 


void	fillDictionaryArray(char *buffer, char dictionary[60][2][45], char *searchstring)
{
	int i = 0;
	int row = 0, col = 0;
	int j = 0;
	int printed = 0;
	// ERROR HANDLING OF FAULTY DICT
	while (buffer[i] != '\0') {
		if (buffer[i] == ':') {
			strcpy(dictionary[row][col], "\0");
			col = 1;
			i += 2;
		} else if (buffer[i] == '\n') {
			strcpy(dictionary[row][col], "\0");
			row++;
			col = 0;
			i++;
		} else {
			while (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != ':' && buffer[i] != '\0') {
				dictionary[row][col][j] = buffer[i];
				i++;
				j++;
				printed = 1;
			}
			j = 0;
			if (printed == 1) {
				col++;
				printed = 0;
			}
		}
		
	}
	ft_searchdict(searchstring, (char ***)dictionary);
}

void fillwithnull(char dictionary[60][2][45])
{
	int i = 0, j = 0, k = 0;

	while (i < 60)
	{
		j = 0;
		while (j < 2)
		{
			k = 0;
			while (k < 45)
			{
				dictionary[i][j][k] = '\0'; // Assign null character to each element
				k++;
			}
			j++;
		}
		i++;
	}
}

char **ft_inputcheck(int argc, char **argv)
	{
	if (argc == 3)
	{
		char *arg = argv[2];
		while (*arg)
		{
			if (*arg < '0' || *arg > '9')
			{
				write(2, "Error\n", 7);
				return NULL;
			}
			arg++;
		}
		return argv;
	}
	else if (argc == 2)
	{
		char *arg = argv[1];
		while (*arg)
		{
			if (*arg < '0' || *arg > '9')
			{
				write(2, "Error\n", 7);
				return NULL;
			}
			arg++;
		}
		char *temp = argv[1];
		argv[1] = "numbers.dict";
		argv[2] = temp;
		return argv;
	}
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 38);
		return NULL;
	}
}



void	printrows(char dictionary[60][2][45])
{
	char newline = '\n';
	int i = 0;

	while (i < 80)
	{
		int j = 0;
		while (dictionary[0][i][j] != '\0')
		{
			write(1, &dictionary[0][i][j], 1);
			j++;
		}
		write(1, ": ", 2);
		j = 0;
		while (dictionary[0][i + 1][j] != '\0')
		{
			write(1, &dictionary[0][i + 1][j], 1);
			j++;
		}
		write(1, &newline, 1);
		i += 2;
	}
}

/// SEARCH HERE 
void	ft_searchdict(char *searchstring, char ***dictionary)
{
	
	
	printf("searchstring %s\n", searchstring);
	// printFirstRow(dictionary);




}

// putstr
void	ft_putstr(char *string)
{
	while (*string) 
	{
		write(1, string++, 1);
	}
}


int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}