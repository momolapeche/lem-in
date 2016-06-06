/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 21:30:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/02 18:39:49 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static	char	*get_nb_line(t_list **map)
{
	char	*buf;

	while (get_next_line(0, &buf) == 1)
	{
		if (ft_strequ(buf, "##start") || ft_strequ(buf, "##end"))
			return (NULL);
		if (buf[0] != '#')
			return (buf);
		if (*map)
			ft_lstaddl(map, ft_lstnew(buf, ft_strlen(buf) + 1));
		free(buf);
	}
	return (NULL);
}

int				get_nb_ants(t_list **map, t_env *e)
{
	int		nb;
	char	*buf;
	char	*tmp;

	if ((buf = get_nb_line(map)) == NULL)
		error("Nombre de fourmis invalide", e->param);
	nb = ft_atoi(buf);
	tmp = ft_itoa(nb);
	if (!ft_strequ(tmp, &buf[buf[0] == '+']))
		error("Nombre de fourmis invalide", e->param);
	if (*map)
		ft_lstaddl(map, ft_lstnew(buf, ft_strlen(buf) + 1));
	free(buf);
	free(tmp);
	if (nb <= 0)
		error("Nombre de fourmis invalide", e->param);
	return (nb <= 0 ? -1 : nb);
}
