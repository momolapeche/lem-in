/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:44:08 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/02 16:57:48 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static t_list	*verify_tube(t_list *room, char *buf)
{
	while (room)
	{
		if (ft_strequ(room->content, buf))
			return (room);
		room = room->next;
	}
	free(buf);
	return (NULL);
}

static int		test_tube(t_env *e, char const *buf, t_list **t1, t_list **t2)
{
	int		i;
	t_list	*lst1;
	t_list	*lst2;

	i = 0;
	while (buf[i] && buf[i] != '-')
		i++;
	if (!buf[i] || !(*t1 = verify_tube(e->room, ft_strsub(buf, 0, i))))
		return (1);
	i++;
	if (ft_strnequ(buf, ft_strdup(&buf[i]), i) ||
			!(*t2 = verify_tube(e->room, ft_strdup(&buf[i]))))
		return (1);
	lst1 = e->tube1;
	lst2 = e->tube2;
	while (lst1 && lst2)
	{
		if ((lst1->content == *t1 && lst2->content == *t2) ||
				(lst1->content == *t2 && lst2->content == *t1))
			return (1);
		lst1 = lst1->next;
		lst2 = lst2->next;
	}
	return (0);
}

static void		add_tube(t_env *e, t_list *room1, t_list *room2)
{
	ft_lstadd(&e->tube1, ft_lstnew(NULL, 0));
	e->tube1->content = room1;
	ft_lstadd(&e->tube2, ft_lstnew(NULL, 0));
	e->tube2->content = room2;
}

int				get_tubes(t_env *e, t_list **map, char *buf)
{
	int		mem;
	t_list	*tmp1;
	t_list	*tmp2;

	mem = buf ? 1 : 0;
	while (mem == 1)
	{
		if (buf[0] != '#' || ft_strequ(buf, "##start") ||
				ft_strequ(buf, "##end"))
		{
			if (test_tube(e, buf, &tmp1, &tmp2))
				return (0);
			add_tube(e, tmp1, tmp2);
		}
		if (*map)
			ft_lstaddl(map, ft_lstnew(buf, ft_strlen(buf) + 1));
		free(buf);
		mem = get_next_line(0, &buf);
	}
	return (0);
}
