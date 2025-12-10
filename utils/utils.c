/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:47:35 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:47:35 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini_rt.h"
#include <stdio.h>
#include <stdlib.h>

void	print_error(char *error, t_all *all)
{
	printf( "error: %s\n", error);
	clean_collector(all);
}

float ft_atof(const char *str, char type, t_all *all)
{
	float	result;
	float	factor;
	int		negative;
	int		i;

	i = 0;
	negative = 1;
	result = 0.0;
	factor = 1.0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		printf("type is: %c index is: %d\n", type, i);
        i++;
	}
    if (str[i] == '+' || str[i] == '-')
	{
        if (str[i] == '-') {
            negative = -1;
        }
        i++;
    }
    while (ft_isdigit((unsigned char)str[i]))
	{
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    if (str[i] && str[i] == '.')
	{
		i++;
        while (ft_isdigit((unsigned char)str[i])) {
            factor /= 10.0;
            result += (str[i] - '0') * factor;
            i++;
        }
    }
	result = negative * result;
	check_float_number(result, type, all);
    return (result);
}


int	ft_atoi(char *str, char type, t_all *all)
{
	int			i;
	long int	number;
	int			negative;

	number = 0;
	negative = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			negative = -1; 
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number *= 10;
		number += str[i] - 48;
		i++;
	}
	number *= negative;
	check_number(number, type, all);
	return (number);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*ft_calloc(int nmemb, int size)
{
	int	i;
	int	byte;
	char	*x;

	i = 0;
	byte = nmemb * size;
	if (size && (byte / size != nmemb))
		return (0);
	x = (char *)malloc(byte);
	if (!x)
		return (0);
	while (byte > 0)
	{
		x[i] = 0;
		i++;
		byte--;
	}
	return ((void *)x);
}
