/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:23:32 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:24:33 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static float	process_fraction(const char *str, int *i)
{
	float	factor;
	float	frac_val;

	factor = 1.0;
	frac_val = 0.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit((unsigned char)str[*i]))
		{
			factor /= 10.0;
			frac_val += (str[*i] - '0') * factor;
			(*i)++;
		}
	}
	return (frac_val);
}

float	ft_atof(const char *str, char type, t_all *all)
{
	float	result;
	int		negative;
	int		i;

	i = 0;
	result = 0.0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (ft_isdigit((unsigned char)str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	result += process_fraction(str, &i);
	result = result * negative;
	check_float_number(result, type, all);
	return (result);
}
