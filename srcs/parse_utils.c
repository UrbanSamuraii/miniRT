/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:02:23 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 19:04:01 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"


t_vec3	colors_to_percent(char **tab)
{
	t_vec3	ret;
	float	red;
	float	green;
	float	blue;

	red = ft_atof(tab[0]);
	green = ft_atof(tab[1]);
	blue = ft_atof(tab[2]);
	ret = (t_vec3){(red / 255), (green / 255), (blue / 255)};
	return (ret);
}
