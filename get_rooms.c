/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 10:59:51 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/03 17:52:09 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		test_room(char const *buf, t_list *room)
{
	int	i;
	int	s;

	if (!buf)
		return (1);
	i = 0;
	s = 0;
	while (buf[i])
		if (buf[i++] == ' ')
		{
			if (!s)
				while (room)
				{
					if (ft_strnequ(room->content, buf, i - 1))
						return (1);
					room = room->next;
				}
			s++;
		}
	if (s != 2)
		return (1);
	return (0);
}

static int		get_coor(char const *buf, int *i, t_env *e)
{
	int		tmp;
	char	*nbr;

	tmp = *i;
	*i += buf[*i] == '+' || buf[*i] == '-';
	while (ft_isdigit(buf[*i]))
		(*i)++;
	if (buf[*i] && buf[*i] != ' ')
		error(ft_strjoin(buf, " : coordonnees invalides"), e->param);
	nbr = ft_itoa(ft_atoi(&buf[tmp]));
	if (!ft_strnequ(nbr, &buf[tmp], ft_strlen(nbr)))
		error(ft_strjoin(buf, " : coordonnees invalides"), e->param);
	free(nbr);
	return (ft_atoi(&buf[tmp]));
}

static t_list	*create_room(char const *buf, t_env *e)
{
	char	*room;
	int		i;

	i = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	if (!buf[i])
		error(ft_strjoin(buf, " : salle non valide"), e->param);
	if (buf[0] == 'L')
		error("une salle ne peut pas commencer par 'L'", e->param);
	room = ft_strsub(buf, 0, i++);
	get_coor(buf, &i, e);
	if (buf[i++] != ' ')
		error(ft_strjoin(buf, " : salle non valide"), e->param);
	get_coor(buf, &i, e);
	if (buf[i])
		error(ft_strjoin(buf, " : salle non valide"), e->param);
	return (ft_lstnew(room, ft_strlen(room) + 1));
}

static int		get_comm_rooms(t_env *e, char **buf, t_list **map)
{
	int		comm;

	if (*map)
		ft_lstaddl(map, ft_lstnew(*buf, ft_strlen(*buf) + 1));
	comm = ft_strequ(*buf, "##end");
	if (e->ends[comm])
		error(ft_strjoin("Double declaration de ", *buf), e->param);
	free(*buf);
	while (get_next_line(0, buf) == 1)
	{
		if (ft_strequ(*buf, "##start") || ft_strequ(*buf, "##end"))
			error(ft_strjoin(*buf, " : commande invalide"), e->param);
		if ((*buf)[0] != '#')
			break ;
		free(*buf);
	}
	if (test_room(*buf, e->room))
		error(ft_strjoin(*buf, " non valide"), e->param);
	ft_lstadd(&e->room, create_room(*buf, e));
	e->ends[comm] = e->room;
	return (0);
}

char			*get_rooms(t_env *e, t_list **map)
{
	char	*buf;

	if ((e->ends = (t_list **)ft_memalloc(sizeof(t_list *) * 2)) == NULL)
		error("L'allocation de Start et End a echouee", e->param);
	while (get_next_line(0, &buf) == 1)
	{
		if (buf[0] != '#' && test_room(buf, e->room))
			break ;
		if (buf[0] != '#')
			ft_lstadd(&e->room, create_room(buf, e));
		if (ft_strequ(buf, "##start") || ft_strequ(buf, "##end"))
			get_comm_rooms(e, &buf, map);
		if (*map)
			ft_lstaddl(map, ft_lstnew(buf, ft_strlen(buf) + 1));
		free(buf);
	}
	if (!e->ends[0] || !e->ends[1])
		error("##start et/ou ##end non declare", e->param);
	return (buf);
}
