/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:10 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/04 12:02:32 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

// radius && height are set to default values
void	init_plane(t_objects *object, char **params)
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
	object->radius = 0;
	object->height = 0;
	tab = ft_split(params[3], ',');
	object->colors = colors_to_percent(tab);
	free_tab(tab);
}

// adds first node via init_plane_head function or a new node
static void	add_node_plane(t_elem *elems, char **params)
{
	if (elems->objects_head == NULL)
		init_object_head(elems, params, PLANE);
	else
		new_node_object(elems, params, PLANE);
}

// in this function i check every parameter of the line pl
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	plane(t_elem *elems, char **params)
{
	int	i;

	printf(YELLOW"CHECKING PLANE..."RESET"\n");
	if (invalid_param_number(4, params))
		return (EXIT_FAILURE);
	if (not_valid_range(params[1], -DBL_MAX, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_range(params[2], -1, 1))
		return (EXIT_FAILURE);
	if (not_valid_range(params[3], 0, 255))
		return (EXIT_FAILURE);
	add_node_plane(elems, params);
	i = 0;
	while (params[i])
		printf("[%s] ", params[i++]);
	printf ("\n");
	printf(GREEN"PLANE OK!"RESET"\n");
	return (EXIT_SUCCESS);
}
