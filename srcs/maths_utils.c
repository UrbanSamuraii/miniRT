/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:29:27 by avast             #+#    #+#             */
/*   Updated: 2023/05/12 14:30:01 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

float	deg_to_rad(float a)
{
	return (a / 180 * 3.14159265);
}

float	ft_abs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	pos_val(float a)
{
	if (a < 0)
		return (0);
	else
		return (a);
}
