/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:30:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/06 17:23:44 by rmenegau         ###   ########.fr       */
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

void		aff(t_list *way, int max)
{
	t_list	*lst;
	int		ant;

	way->content_size = 0;
	while (way->content_size != max)
	{
		ant = way->content_size + 1;
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
}

static int	test_param(char c)
{
	return ((c == 'm') + ((c == 'f') << 1) + ((c == 'i') << 2) + ((c == 'c') << 3));
}

static void	help_param(void)
{
	ft_printf("options :[-mfci]\n");
	ft_printf("-m : n'affiche pas les parametres de la carte\n");
	ft_printf("-f : n'affiche pas le deplacement des fourmis\n");
	ft_printf("-c : affiche le chemin utilise\n");
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
	aff_map(e->map);
	i = 0;
	while (ways[i])
	{
		if (!(e->param & 2))
			aff(ways[i], e->nb_ants);
		i++;
	}
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
