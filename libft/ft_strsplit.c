/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:24:46 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 14:12:08 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_warrfill(char **warr, const char *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	while (s[start] != '\0')
	{
		if ((start == 0 || s[start - 1] == c) && s[start] != c)
		{
			end = start;
			while (s[end] != c && s[end] != '\0')
				end++;
			ft_strncpy(warr[i++], &s[start], end - start);
		}
		start++;
	}
}

static char		**ft_warrcheck(char **warr, size_t wc)
{
	size_t i;

	i = 0;
	while (warr[i] != NULL)
		i++;
	if (i < wc)
	{
		i = 0;
		while (i < wc + 1)
		{
			free(warr[i]);
			warr[i++] = NULL;
		}
		free(warr);
		warr = NULL;
	}
	return (warr);
}

static void		ft_warralloc(char **warr, const char *s, char c)
{
	size_t	i;
	size_t	counter;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			counter = 0;
			while (s[i + counter] != c && s[i + counter] != '\0')
				counter++;
			warr[j++] = ft_strnew(counter);
		}
		i++;
	}
}

static size_t	ft_countwords(const char *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
		{
			counter++;
			i++;
		}
		if (s[i - 1] == c && s[i] != c)
			counter++;
		i++;
	}
	return (counter);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**warr;
	size_t	wc;
	size_t	i;

	if (s == NULL)
		return (NULL);
	wc = ft_countwords(s, c);
	warr = (char**)malloc(sizeof(*warr) * (wc + 1));
	if (warr == NULL)
		return (NULL);
	i = 0;
	while (i < wc + 1)
		warr[i++] = NULL;
	if (wc > 0)
	{
		ft_warralloc(warr, s, c);
		i = 0;
		warr = ft_warrcheck(warr, wc);
		if (warr != NULL)
			ft_warrfill(warr, s, c);
	}
	return (warr);
}
