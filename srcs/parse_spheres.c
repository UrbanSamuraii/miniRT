/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:15 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 19:04:01 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"


// dir && height are set to default values
void	init_sphere(t_objects *object, char **params)
{
	char	**tab;

	tab = ft_split(params[1], ',');
	object->origin = (t_vec3){ft_atof(tab[0]),
		ft_atof(tab[1]), ft_atof(tab[2])};
	free_tab(tab);
	object->dir = (t_vec3){0, 0, 0};
	object->radius = ft_atof(params[2]) / 2;
	object->height = 0;
	tab = ft_split(params[3], ',');
	object->colors = colors_to_percent(tab);
	free_tab(tab);
}

// adds first node via init_sphere_head function or a new node
static void	add_node_sphere(t_elem *elems, char **params)
{
	if (elems->objects_head == NULL)
		init_object_head(elems, params, SPHERE);
	else
		new_node_object(elems, params, SPHERE);
}

// in this function i check every parameter of the line sp
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	sphere(t_elem *elems, char **params)
{
	int	i;

	printf(YELLOW"CHECKING SPHERE..."RESET"\n");
	if (invalid_param_number(4, params))
		return (EXIT_FAILURE);
	if (not_valid_range(params[1], -DBL_MAX, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[2], 0.0001, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_range(params[3], 0, 255))
		return (EXIT_FAILURE);
	add_node_sphere(elems, params);
	i = 0;
	while (params[i])
		printf("[%s] ", params[i++]);
	printf ("\n");
	printf(GREEN"SPHERE OK!"RESET"\n");
	return (EXIT_SUCCESS);
}
