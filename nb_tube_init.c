/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_tube_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 13:41:37 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/04 18:54:23 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		set_content_size(t_list *lst, size_t n)
{
	if ((!lst->content_size || lst->content_size > n) && lst->content_size != (size_t)-1)
	{
		lst->content_size = n;
		return (1);
	}
	return (0);
}

static int		set_room(t_env *e, t_list *room)
{
	t_list	*t1;
	t_list	*t2;
	int		ret;

	t1 = e->tube1;
	t2 = e->tube2;
	ret = 0;
	while (t1 && t2)
	{
		if (t1->content == room)
			ret |= set_content_size(t2->content, room->content_size + 1);
		if (t2->content == room)
			ret |= set_content_size(t1->content, room->content_size + 1);
		t1 = t1->next;
		t2 = t2->next;
	}
	return (ret);
}

void			set_tic(t_env *e)
{
	int		tmp;
	t_list	*lst;

	e->ends[1]->content_size = 1;
	tmp = set_room(e, e->ends[1]);
	while (tmp)
	{
		tmp = 0;
		lst = e->room;
		while (lst)
		{
			if (lst->content_size && lst->content_size != (size_t)-1)
				tmp |= set_room(e, lst);
			lst = lst->next;
		}
	}
}

void			nb_tube_init(t_env *e)
{
	t_list	*room;

	room = e->room;
	while (room)
	{
		if (room->content_size != (size_t)-1)
			room->content_size = 0;
		room = room->next;
	}
}
