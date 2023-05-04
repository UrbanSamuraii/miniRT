/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:29:27 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 16:26:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

float	deg_to_rad(float a)
{
	return (a / 180 * 3.14159265);
}

float	cal_cos(int a)
{
	return (cos(0.0174533 * a));
}

float	cal_sin(int a)
{
	return (sin(0.0174533 * a));
}

float	ft_abs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_sign(int a)
{
	if (a < 0)
		return (-1);
	else if (a > 0)
		return (1);
	return (0);
}
