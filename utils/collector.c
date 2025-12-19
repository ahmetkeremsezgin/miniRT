/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:46:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:46:57 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>

void	add_collector(t_all *all, void *address)
{
	t_collector	*new_collector;
	t_collector	*current;

	current = all->collector;
	new_collector = (t_collector *) ft_calloc(sizeof(t_collector), 1);
	if (new_collector == NULL)
		print_error("Memory allocation failed", all);
	new_collector->value = address;
	new_collector->next = NULL;
	if (all->collector == NULL)
		all->collector = new_collector;
	else
	{
		current = all->collector;
		while (current->next != NULL)
			current = current->next;
		current->next = new_collector;
	}
}

void	*safe_malloc(int size, t_all *all)
{
	void	*str;

	str = ft_calloc(size, 1);
	if (str == 0)
		print_error ("Memory allocation failed", all);
	add_collector(all, str);
	return (str);
}

char	*collector_dup(char *str, t_all *all)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new = (char *)safe_malloc(len + 1, all);
	while (str[i] && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

void	clean_collector(t_all *all)
{
	t_collector	*current;
	t_collector	*temp;

	current = all->collector;
	temp = NULL;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	get_next_line(-1);
	all->ambient = NULL;
	all->camera = NULL;
	all->cylinder = NULL;
	all->light = NULL;
	all->plane = NULL;
	all->sphere = NULL;
	all->collector = NULL;
	exit(1);
}
