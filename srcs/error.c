/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:06:28 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 16:55:47 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

// todo: more specific errors, either in each function or here
void	error(char **to_free, t_elem *elems, int code)
{
	if (code == ERRITI)
		ft_dprintf(2, FRED"Error\nInvalid type identifier."RESET"\n");
	free_tab(to_free);
	free_structures(elems);
	exit(1);
}
