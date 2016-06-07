/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:30:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/07 22:08:54 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int	get_nb_ways(t_env *e)
{
	int		start;
	int		end;
	t_list	*tmp1;
	t_list	*tmp2;

	start = 0;
	end = 0;
	tmp1 = e->tube1;
	tmp2 = e->tube2;
	while (tmp1 && tmp2)
	{
		if (tmp1->content == e->ends[0] ||
				tmp2->content == e->ends[0])
			start++;
		if (tmp1->content == e->ends[1] ||
				tmp2->content == e->ends[1])
			end++;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (!start || !end)
		error("Pas de chemin possible", e->param);
	return (start < end ? start : end);
}

static void	aff_map(t_list *lst)
{
	t_list	*tmp;

	if (lst)
	{
		lst = lst->next;
		while (lst)
		{
			ft_putendl(lst->content);
			tmp = lst;
			lst = lst->next;
			free(tmp);
		}
		ft_putchar('\n');
	}
}

int			get_max(t_list *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst->content_size);
}

int			aff(t_list *way, int tmp)
{
	t_list	*lst;
	int		ant;
	int		max;

	max = get_max(way);
	while (way->content_size != max)
	{
		ant = tmp + way->content_size + 1;
		lst = way;
		while (lst->next)
		{
			if (lst->next->content_size)
			{
				lst->content_size++;
				lst->next->content_size--;
				ft_printf("L%i-%s ", ant++, lst->content);
			}
			lst = lst->next;
		}
		ft_putchar('\n');
	}
	return (way->content_size);
}

int			tic(t_list **ways)
{
	int			i;
	int			ret;
	unsigned	mem;
	t_list		*lst;

	i = 0;
	mem = 1;
	ret = 0;
	while (ways[i])
	{
		ret += ways[i]->content_size;
		mem += ways[i]->content_size;
		lst = ways[i];
		while (lst->next)
		{
			if (lst->next->content_size)
			{
				ft_printf("L%d-%s ", mem, lst->content);
				mem += lst->next->content_size;
				lst->content_size++;
				lst->next->content_size--;
			}
			lst = lst->next;
		}
		i++;
	}
	write(1, "\n", 1);
	return (ret);
}

int			mooove(t_list **ways, int max)
{
	t_list	*lst;
	int		gbl;
	int		nb_moves;

	gbl = 0;
	nb_moves = 0;
	while (gbl < max)
	{
		gbl = tic(ways);
		nb_moves++;
	}
	return (nb_moves);
}

static int	test_param(char c)
{
	return ((c == 'm') + ((c == 'f') << 1) + ((c == 'i') << 2) + ((c == 'c') << 3) + ((c == 't') << 4));
}

static void	help_param(void)
{
	ft_printf("options : [-mfcti]\n");
	ft_printf("-m : n'affiche pas les parametres de la carte\n");
	ft_printf("-f : n'affiche pas le deplacement des fourmis\n");
	ft_printf("-c : affiche le chemin utilise\n");
	ft_printf("-t : affiche le nombre de tics\n");
	ft_printf("-i : affiche le details de l'erreur\n");
	exit(0);
}

static int	get_param(int ac, char **av, t_env *e)
{
	int		param;
	int		i;

	param = 0;
	if (ac > 2)
		error("trop de parametres", e->param);
	if (av[1][0] != '-')
		error("parametre invalide", e->param);
	i = 1;
	if (ft_strequ(av[1], "-help"))
		help_param();
	while (test_param(av[1][i]) != 0)
	{
		param |= test_param(av[1][i]);
		i++;
	}
	if (!param || av[1][i])
		help_param();
	return (param);
}

static void	aff_way(t_list *way)
{
	while (way)
	{
		ft_printf("%s", way->content);
		if (way->next)
			ft_printf(" <- ");
		way = way->next;
	}
	ft_putchar('\n');
}

int			main(int ac, char **av)
{
	t_env	*e;
	t_list	**ways;
	int		i;

	e = (t_env *)ft_memalloc(sizeof(t_env));
	e->param = ac > 1 ? get_param(ac, av, e) : 0;
	get_info(e);
	ways = get_ways(e, get_nb_ways(e));
	att_ants(ways, e->nb_ants);
	aff_map(e->map);
	i = mooove(ways, e->nb_ants);
	if (e->param & 0x10)
		ft_printf("%d tics");
	i = 0;
	if (e->param & 8)
		ft_printf("chemin(s) utilise(s) :\n");
	while (ways[i])
	{
		if (e->param & 8)
			aff_way(ways[i]);
		i++;
	}
	return (0);
}
