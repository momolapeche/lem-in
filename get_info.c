/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 06:23:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/04 18:58:26 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_env		*get_info(t_env *e)
{
	char	*tmp;

	e->map = (e->param & 1) ? NULL : ft_lstnew(NULL, 0);
	if ((e->nb_ants = get_nb_ants(&e->map, e)) == -1)
		return (NULL);
	if ((tmp = get_rooms(e, &e->map)) == NULL)
		return (NULL);
	if (get_tubes(e, &e->map, tmp))
		return (NULL);
	return (e);
}
