/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:48:31 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 15:29:49 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

// first node initialization
void	init_object_head(t_elem *elems, char **params, int type)
{
	elems->objects_head = malloc(sizeof(t_objects));
	if (!elems->objects_head)
		perror("Malloc");
	if (type == SPHERE)
		init_sphere(elems->objects_head, params);
	else if (type == PLANE)
		init_plane(elems->objects_head, params);
	else if (type == CYLINDER)
		init_cylinder(elems->objects_head, params);
	elems->objects_head->id = 0;
	elems->objects_head->type = type;
	elems->objects_head->next = NULL;
}

// lstlast adapled for t_plane struct
static t_objects	*sp_lstlast(t_objects *lst, int *id)
{
	int	i;

	i = 1;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	*id = i;
	return (lst);
}

void	new_node_object(t_elem *elems, char **params, int type)
{
	t_objects	*plst;
	t_objects	*new_node;

	new_node = malloc(sizeof(t_objects));
	if (new_node == NULL)
		perror("malloc");
	if (type == SPHERE)
		init_sphere(new_node, params);
	else if (type == PLANE)
		init_plane(new_node, params);
	else if (type == CYLINDER)
		init_cylinder(new_node, params);
	new_node->type = type;
	new_node->next = NULL;
	plst = elems->objects_head;
	plst = sp_lstlast(elems->objects_head, &new_node->id);
	plst->next = new_node;
}
