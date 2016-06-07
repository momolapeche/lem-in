/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 11:57:34 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/07 14:37:27 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		get_max(size_t *ways_tmp)
{
	int		i;
	size_t	tmp;

	i = 1;
	tmp = 0;
	while (i < ways_tmp[0])
	{
		if (ways_tmp[i] > tmp)
			tmp = ways_tmp[i];
		i++;
	}
	return (tmp);
}

static int		ways_add(t_list **ways)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (ways[i])
	{
		ret += ways[i]->content_size;
		i++;
	}
	return (ret);
}

static int		equalizer(t_list **ways, int nb_ants)
{
	int		j;
	int		i;
	int		max;
	size_t	*ways_tmp;

	i = 0;
	while (ways[i])
		i++;
	ways_tmp = (size_t *)ft_memalloc(sizeof(size_t) * (i + 1));
	ways_tmp[0] = i + 1;
	i = 1;
	while (i < ways_tmp[0])
	{
		ways_tmp[i] = ft_lstcount(ways[i - 1]);
		i++;
	}
	j = 0;
	max = get_max(ways_tmp);
	while (max && j < nb_ants)
	{
		i = 1;
		while (i < ways_tmp[0] && j < nb_ants)
		{
			if (ways_tmp[i])
			{
				ways[i - 1]->content_size++;
				ways_tmp[i]--;
				j++;
			}
			i++;
		}
		max--;
	}
	free(ways_tmp);
	max = ways_add(ways);
	return (max);
}

static void		transf(t_list *way)
{
	size_t	tmp;

	tmp = way->content_size;
	way->content_size = 0;
	while (way->next)
		way = way->next;
	ft_printf("%zi\n", way->content_size = tmp);
}

void			att_ants(t_list **ways, int nb_ants)
{
	size_t	ants;
	int		i;

	ants = equalizer(ways, nb_ants);
	while (ants < nb_ants)
	{
		i = 0;
		while (ways[i] && ants < nb_ants)
		{
			ways[i]->content_size++;
			i++;
			ants++;
		}
	}
	i = 0;
	while (ways[i])
	{
		transf(ways[i]);
		ft_printf("%zi\n", ways[i]->content_size);
		i++;
	}
}
