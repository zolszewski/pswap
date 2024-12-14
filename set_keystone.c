/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_keystone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <zoolszew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:44:30 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/14 08:48:13 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *find_keystone(t_keystone *tab, int size, int *count_keystone, int save)
{ 
    static int	i;
	static int	current_keystone[2];
	int mid;
	int midmid;
	
	save = i;
	while (i < size && (*(tab + i)).on_off == 0)
		++i;
	mid = i - (i - save) / 2;
	midmid = mid - (i - save) / 4;
	(*(tab + i + mid)).on_off = 1;
	*current_keystone = (*(tab + mid)).num;
	(*(tab + midmid)).on_off = 1;
	*(current_keystone + 1) = (*(tab + midmid)).num;
	i = mid;
	return (current_keystone);
}


int *find_keystoneB(t_keystone *tab, int size, int *count_keystone, int *i)
{
    int save;
	static int	current_keystone[2];
	int mid;
	int midmid;
	
	save = *i;
	while (*i > -1 && (*(tab + *i)).on_off == 1)
		--(*i);
	while (*i > -1 && (*(tab + *i)).on_off == 0)
		--(*i);
	mid = *i + (save - *i) / 2;
	midmid = mid + (save - *i) / 4;
	(*(tab + *i + mid)).on_off = 1;
	*current_keystone = (*(tab + mid)).num;
	(*(tab + midmid)).on_off = 1;
	*(current_keystone + 1) = (*(tab + midmid)).num;
	*i = mid;
	return (current_keystone);
}

int find_path(int* range, int*rrange, t_array *tab_int, int *current_keystone)
{
	t_list *node;

	*range = 0;
	node = (*tab_int).first_a;
	while (node)
	{
		if ((*node).num <= *current_keystone)
			break ;
		node = (*node).next;
		++(*range);
	}
	if (node == NULL)
		return (1);
	*rrange = 0;
	node = (*tab_int).last_a;
	while (node)
	{
		if ((*node).num <= *current_keystone)
			break ;
		node = (*node).prev;
		++(*rrange);
	}
	return (0);
}

int find_pathB(int* range, int*rrange, t_array *tab_int, int *current_keystone)
{
	t_list *node;

	*range = 0;
	node = (*tab_int).first_b;
	while (node)
	{
		if ((*node).num >= *current_keystone)
			break ;
		node = (*node).next;
		++(*range);
	}
	if (node == NULL)
		return (1);
	*rrange = 0;
	node = (*tab_int).last_b;
	while (node)
	{
		if ((*node).num >= *current_keystone)
			break ;
		node = (*node).prev;
		++(*rrange);
	}
	return (0);
}

void empty_block(int *current_keystone, t_array *tab_int, t_list *first_a, t_list *last_a)
{
	t_list *node;
	int range;
	int rrange;

	find_path(&range, &rrange, tab_int, current_keystone);
	while (1)
	{
		if ((*(*tab_int).first_a).num <= *current_keystone)
		{
			ft_push_b(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
			if ((*(*tab_int).first_b).num <= *(current_keystone + 1))
				ft_rb(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
			if (find_path(&range, &rrange, tab_int, current_keystone))
				return ;
		}
		if (rrange < range)
			ft_rra(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		else
			ft_ra(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
	}
}


void empty_blockB(int *current_keystone, t_array *tab_int, t_list *first_b, t_list *last_b)
{
	t_list *node;
	int range;
	int rrange;

	find_pathB(&range, &rrange, tab_int, current_keystone);
	while (1)
	{
		if ((*(*tab_int).first_b).num >= *current_keystone)
		{
			ft_push_a(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
			if ((*(*tab_int).first_a).num <= *(current_keystone + 1))
				ft_ra(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
			if (find_pathB(&range, &rrange, tab_int, current_keystone))
				return ;
		}
		if (rrange < range)
			ft_rrb(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		else
			ft_rb(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
	}
}

void sorting_algo(t_array *tab_int)
{
	int *current_keystone;
	int i = (*tab_int).size - 1;

	//TODO:while(mon nombre de pivot est assez eleve)
	//{
		while((*tab_int).first_a)
		{
			current_keystone = find_keystone((*tab_int).tab, (*tab_int).size, (&(*tab_int).count_keystone), 0);
			empty_block(current_keystone, tab_int, (*tab_int).first_a, (*tab_int).last_a);
		}
		while ((*tab_int).first_b)
		{
			current_keystone = find_keystoneB((*tab_int).tab, (*tab_int).size, (&(*tab_int).count_keystone), &i);
			empty_blockB(current_keystone, tab_int, (*tab_int).first_b, (*tab_int).last_b);
		}
	//}
	//TODO:Insert sort.

}

