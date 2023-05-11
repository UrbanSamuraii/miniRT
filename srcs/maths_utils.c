/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:29:27 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 19:04:01 by ankhabar         ###   ########.fr       */
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
