/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:46:29 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:46:29 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	file_check(int ac, char **av)
{
	int	len;
	int	fd;

	len = 0;
	if (ac != 2)
	{
		printf("Error\ninvalid argument size\n");
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || av[1][len - 1] != 't'
			|| av[1][len - 2] != 'r' || av[1][len - 3] != '.')
	{
		printf("Error\nWrong file name\n");
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open file\n");
		exit(1);
	}
	close(fd);
}

void	check_number(int number, char type, t_all *all)
{
	if (type == 'c')
	{
		if (number > 255 || number < 0)
			print_error("invalid number value", all);
	}
	else
	{
		if (number > 180 || number < 0)
			print_error("invalid view degrees", all);
	}
}

void	check_float_number(float number, char type, t_all *all)
{
	if (type == 'r' || type == 'b')
	{
		if (number > 1.0 || number < 0.0)
			print_error("invalid ratio value", all);
	}
	else if (type == 'v')
	{
		if (number > 1.0 || number < -1.0)
			print_error("invalid vector value", all);
	}
	else
	{
		return ;
	}
}

void	check_obj(t_all *all)
{
	if (all->ambient == NULL || all->camera == NULL || all->light == NULL )
		print_error("Missing object in map file", all);
}
