/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:02:17 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 19:34:26 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

// first node initialization
static void	init_light_head(t_elem *elems, char **params)
{
	char	**tab;

	elems->lights_head = malloc(sizeof(t_light));
	if (!elems->lights_head)
		perror("Malloc");
	tab = ft_split(params[1], ',');
	elems->lights_head->origin = (t_vec3){ft_atof(tab[0]),
		ft_atof(tab[1]), ft_atof(tab[2])};
	free_tab(tab);
	elems->lights_head->ratio = ft_atof(params[2]);
	tab = ft_split(params[3], ',');
	elems->lights_head->colors = colors_to_percent(tab);
	free_tab(tab);
	elems->lights_head->next = NULL;
}

// lstlast adapted for t_light struct
static t_light	*sp_lstlast(t_light *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	new_node_light(t_elem *elems, char **params)
{
	char	**tab;
	t_light	*plst;
	t_light	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		perror("Malloc");
	new_node->ratio = ft_atof(params[2]);
	tab = ft_split(params[3], ',');
	new_node->colors = (t_vec3){ft_atof(tab[0]),
		ft_atof(tab[1]), ft_atof(tab[2])};
	new_node->colors.xyz /= 255;
	free_tab(tab);
	tab = ft_split(params[1], ',');
	new_node->origin = (t_vec3){ft_atof(tab[0]),
		ft_atof(tab[1]), ft_atof(tab[2])};
	free_tab(tab);
	new_node->next = NULL;
	plst = elems->lights_head;
	plst = sp_lstlast(elems->lights_head);
	plst->next = new_node;
}

// adds first node via init_light_head function or a new node
static void	add_node_light(t_elem *elems, char **params)
{
	if (elems->lights_head == NULL)
		init_light_head(elems, params);
	else
		new_node_light(elems, params);
}

// in this function i check every parameter of the line L
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	light(t_elem *elems, char **params)
{
	printf(YELLOW"CHECKING LIGHT..."RESET"\n");
	if (invalid_param_number(4, params))
		return (EXIT_FAILURE);
	if (not_valid_range(params[1], -DBL_MAX, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[2], 0, 1))
		return (EXIT_FAILURE);
	if (not_valid_range(params[3], 0, 255))
		return (EXIT_FAILURE);
	add_node_light(elems, params);
	printf(GREEN"LIGHT OK!"RESET"\n");
	return (EXIT_SUCCESS);
}
