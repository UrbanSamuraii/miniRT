/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:50:09 by ulysse            #+#    #+#             */
/*   Updated: 2023/04/26 16:47:17 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_string(char *s1, char set, int size)
{
	int		i;
	int		j;
	char	*new_string;

	new_string = ft_calloc(size, sizeof(char));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (set != s1[i])
		{
			new_string[j] = s1[i];
			j++;
		}
		i++;
	}
	new_string[j] = '\0';
	if (s1 != NULL)
		free (s1);
	return (new_string);
}

char	*ft_strtrim(char *s1, char set)
{
	int		i;
	int		w_space;

	i = 0;
	w_space = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
	{	
		if (set == s1[i])
			w_space++;
		i++;
	}
	return (ft_new_string(s1, set, i - w_space + 1));
}
