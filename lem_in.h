/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:57:25 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/07 12:19:09 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define ERROR 0
# define ANTS 1
# define ROOM 2
# define TUBE 3
# define COMM 4

typedef struct	s_env
{
	int			nb_ants;
	t_list		**ends;
	t_list		*room;
	t_list		*tube1;
	t_list		*tube2;
	char		**ant;
	t_list		*map;
	int			param;
}				t_env;

void			error(char const *err, int i);
int				get_nb_ants(t_list **map, t_env *e);
char			*get_rooms(t_env *e, t_list **map);
int				get_tubes(t_env *e, t_list **map, char *buf);
t_env			*get_info(t_env *e);
void			nb_tube_init(t_env *e);
void			set_tic(t_env *e);
t_list			**get_ways(t_env *e, int max);
void			att_ants(t_list **ways, int nb_ants);

#endif
