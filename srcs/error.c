/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:06:28 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 19:04:29 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

void	error(char **to_free, t_elem *elems)
{
	free_tab(to_free);
	free_structures(elems);
	exit(1);
}
