/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 09:34:45 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/07 14:31:18 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static t_list	*next_room(t_list *t1, t_list *t2, t_list *room, size_t n)
{
	t_list	*tmp;

	while (t1 && t2)
	{
		if (t1->content == room)
		{
			tmp = t2->content;
			if (tmp->content_size == n - 1)
				return (tmp);
		}
		if (t2->content == room)
		{
			tmp = t1->content;
			if (tmp->content_size == n - 1)
				return (tmp);
		}
		t1 = t1->next;
		t2 = t2->next;
	}
	return (NULL);
}

static t_list	*get_way(t_env *e)
{
	t_list	*path;
	t_list	*lst;
	size_t	tmp;

	path = ft_lstnew(NULL, 0);
	lst = e->ends[0];
	path->content = lst->content;
	tmp = lst->content_size;
	while (lst != e->ends[1] && lst)
	{
		if ((lst = next_room(e->tube1, e->tube2, lst, tmp)))
		{
			ft_lstadd(&path, ft_lstnew(NULL, 0));
			path->content = lst->content;
			tmp = lst->content_size;
			lst->content_size = (size_t)-1;
		}
		else
			return (NULL);
	}
	return (path);
}

t_list			**get_ways(t_env *e, int max)
{
	t_list	*lst;
	t_list	**path;
	int		i;

	path = (t_list **)ft_memalloc(sizeof(t_list *) * (max + 1));
	i = 0;
	while (i < max)
	{
		nb_tube_init(e);
		set_tic(e);
		if ((path[i] = get_way(e)) == NULL)
			return (path);
		i++;
	}
	return (path);
}
