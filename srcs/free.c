/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:05:25 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 15:29:49 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

void	ft_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_objects(t_objects *objects)
{
	t_objects	*tmp;

	while (objects != NULL)
	{
		tmp = objects;
		objects = objects->next;
		ft_free((void **)&tmp);
		tmp = NULL;
	}
}

void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights != NULL)
	{
		tmp = lights;
		lights = lights->next;
		ft_free((void **)&tmp);
		tmp = NULL;
	}
}

void	free_structures(t_elem *elems)
{
/* 	if (elems->ambient != NULL)
		free(elems->ambient);
	if (elems->camera != NULL)
		free(elems->camera); */
	if (elems->lights_head != NULL)
		free_lights(elems->lights_head);
	if (elems->objects_head != NULL)
		free_objects(elems->objects_head);
}
