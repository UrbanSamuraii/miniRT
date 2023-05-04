/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:20:38 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 16:26:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_atof_aux(const char *nptr)
{
	float	res;
	float	decimal;

	res = 0;
	decimal = 0.1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		while ('0' <= *nptr && *nptr <= '9')
		{
			res += (*nptr - '0') * decimal;
			decimal /= 10;
			nptr++;
		}
	}
	return (res);
}

float	ft_atof(const char *nptr)
{
	float	res;
	int		sign;

	sign = 1;
	while ((*nptr == ' ') || ('\t' <= *nptr && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	res = ft_atof_aux(nptr);
	res *= sign;
	return (res);
}
