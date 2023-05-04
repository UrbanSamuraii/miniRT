/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:06 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/04 12:02:51 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

void	init_cylinder(t_objects *object, char **params)
{
	char	**tab;

	tab = ft_split(params[1], ',');
	object->origin = (t_vec3){ft_atof(tab[0]),
		ft_atof(tab[1]), ft_atof(tab[2])};
	free_tab(tab);
	tab = ft_split(params[2], ',');
	object->dir = vec3_normalize((t_vec3){ft_atof(tab[0]),
			ft_atof(tab[1]), ft_atof(tab[2])});
	free_tab(tab);
	object->radius = ft_atof(params[3]) / 2;
	object->height = ft_atof(params[4]);
	tab = ft_split(params[5], ',');
	object->colors = colors_to_percent(tab);
	free_tab(tab);
}

// adds first node via init_object_head function or a new node
static void	add_node_cylinder(t_elem *elems, char **params)
{
	if (elems->objects_head == NULL)
		init_object_head(elems, params, CYLINDER);
	else
		new_node_object(elems, params, CYLINDER);
}

// in this function i check every parameter of the line cy
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	cylinder(t_elem *elems, char **params)
{
	int	i;

	printf(YELLOW"CHECKING CYLINDER..."RESET"\n");
	if (invalid_param_number(6, params))
		return (EXIT_FAILURE);
	if (not_valid_range(params[1], -DBL_MAX, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_range(params[2], -1, 1))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[3], 0.0001, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[4], 0.0001, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_range(params[5], 0, 255))
		return (EXIT_FAILURE);
	add_node_cylinder(elems, params);
	i = 0;
	while (params[i])
		printf("[%s] ", params[i++]);
	printf ("\n");
	printf(GREEN"CYLINDER OK!"RESET"\n");
	return (EXIT_SUCCESS);
}
