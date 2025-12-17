/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:47:26 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:47:26 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>

static int	word_count(const char *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		if (s[a] != c && s[a] != '\0')
			b++;
		while (s[a] != c && s[a] != '\0')
			a++;
	}
	return (b);
}

static int	word_len(const char *s, char c)
{
	int	a;

	a = 0;
	while (s[a] && s[a] != c)
		a++;
	return (a);
}

static int	word_save(char **f, char const *s, char c, t_all *all)
{
	int	b;
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			b = word_len(&s[i], c);
			f[k] = (char *)safe_malloc((sizeof(char) * (b + 1)), all);
			if (!f[k])
				return (1);
			b = 0;
			while (s[i] && s[i] != c)
				f[k][b++] = s[i++];
			f[k++][b] = '\0';
		}
		else
			i++;
	}
	f[k] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c, t_all *all)
{
	char	**f;
	int		a;

	if (!s[0])
		print_error(" ", all);
	f = (char **)safe_malloc(sizeof(char *) * (word_count(s, c) + 1), all);
	if (!f)
		print_error("Memory allocation failed", all);
	a = word_save(f, s, c, all);
	if (a != 0)
		print_error("Memory allocation failed", all);
	return (f);
}
