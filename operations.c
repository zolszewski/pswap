/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <zoolszew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:56:49 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/14 08:09:30 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

void debug_printlist(t_list *stack)
{
	if (stack == NULL)
	{
		puts("NULL");
		return ;
	}
	t_list *node = stack;
	while (node)
	{
		printf("current = %p, prev = %p, num = %d, next = %p\n", node, node->prev, node->num, node->next);
		node = node->next;
	}
}

void	ft_swap_a(int *index, t_list *first_a, t_operations *actions)
{
	int *a;
	int *b;
	t_list *second_a;
	
	if (!(first_a))
		return ;
	if ((!(*first_a).next))
		return ;
	second_a = (*first_a).next;
	a = &((*first_a).num);
	b = &((*second_a).num);
	*(actions + (*index)) = SA;
	ft_swap(a, b);
	(*index)++;
}

void	ft_swap_b(int *index, t_list *first_b, t_operations *actions)
{
	int *a;
	int *b;
	t_list *second_b;

	if (!(first_b))
		return ;	
	if (!(*first_b).next)
		return ; 	
	second_b = (*first_b).next;
	a = &((*first_b).num);
	b = &((*second_b).num);
	*(actions + (*index)) = SB;
	ft_swap(a, b);
	(*index)++;
}

void	ft_push_b(int *index, t_array *tab_int, t_operations *actions)
{
	t_list *new_first_a;
	
	if (!((*tab_int).first_a)) //PREVOIR un cas dans le main certainement ou first_a next n'existe pas
	//et il n'y a pas d'element dans b => la liste est deja triee !!
		return ;
	if (!(*(*tab_int).first_a).next)
	{
		(*(*tab_int).first_a).next = (*tab_int).first_b;
		(*(*tab_int).first_b).prev = (*tab_int).first_a;
		(*tab_int).first_b = (*tab_int).first_a;
		(*tab_int).last_a = NULL;
		(*tab_int).first_a = NULL;
	}
	else if (!((*tab_int).first_b))
	{
		(*tab_int).first_b = (*tab_int).first_a;
		new_first_a = (*(*tab_int).first_a).next;
		(*(*tab_int).first_b).next = NULL;
		(*(*tab_int).first_b).prev = NULL;
		(*tab_int).first_a = new_first_a;
		(*new_first_a).prev = NULL;
		(*tab_int).last_b = (*tab_int).first_b;
	}	
	else
	{
		new_first_a = (*(*tab_int).first_a).next;
		(*(*tab_int).first_a).next = (*tab_int).first_b;
		(*(*tab_int).first_b).prev = (*tab_int).first_a;
		(*tab_int).first_b = (*tab_int).first_a;
		(*tab_int).first_a = new_first_a;
		(*new_first_a).prev = NULL;
 	}
	*(actions + (*index)) = PB;
	(*index)++;
}

void	ft_push_a(int *index, t_array *tab_int, t_operations *actions)
{
	t_list	*new_first_b;

	if (!(*tab_int).first_b)
		return ;
	if ((*(*tab_int).first_b).next == NULL)
	{
		(*(*tab_int).first_b).next = (*tab_int).first_a;
		(*(*tab_int).first_a).prev = (*tab_int).first_b;
		(*tab_int).first_a = (*tab_int).first_b;
		(*tab_int).last_b = NULL;
		(*tab_int).first_b = NULL;
	}
	else if (!(*tab_int).first_a)
	{
		(*tab_int).first_a = (*tab_int).first_b;
		new_first_b = (*(*tab_int).first_b).next;
		(*(*tab_int).first_a).next = NULL;
		(*(*tab_int).first_a).prev = NULL;
		(*tab_int).first_b = new_first_b;
		(*new_first_b).prev = NULL;
		(*tab_int).last_a = (*tab_int).first_a;
	}
	else 
	{
		new_first_b = (*(*tab_int).first_b).next;
		(*(*tab_int).first_b).next = (*tab_int).first_a;
		(*(*tab_int).first_a).prev = (*tab_int).first_b;
		(*tab_int).first_a = (*tab_int).first_b;
		(*tab_int).first_b = new_first_b;
		(*new_first_b).prev = NULL;
	}
	*(actions + (*index)) = PA;
	(*index)++;
}

void	ft_rra(int *index, t_array *tab_int, t_operations *actions)
{	
	if (!((*tab_int).first_a))
		return ;
	if (!((*(*tab_int).first_a).next))
		return ;
	(*(*tab_int).first_a).prev = (*tab_int).last_a;
	(*(*tab_int).last_a).next = (*tab_int).first_a;
	(*tab_int).first_a = (*tab_int).last_a;
	(*tab_int).last_a = (*(*tab_int).last_a).prev;
	(*(*tab_int).first_a).prev = NULL;
	(*(*tab_int).last_a).next = NULL;
	*(actions + (*index)) = RRA;
	(*index)++;
}
void	ft_rrb(int *index, t_array *tab_int, t_operations *actions)
{	
	if (!((*tab_int).first_b))
		return ;
	if (!((*(*tab_int).first_b).next))
		return ;
	(*(*tab_int).first_b).prev = (*tab_int).last_b;
	(*(*tab_int).last_b).next = (*tab_int).first_b;
	(*tab_int).first_b = (*tab_int).last_b;
	(*tab_int).last_b = (*(*tab_int).last_b).prev;
	(*(*tab_int).first_b).prev = NULL;
	(*(*tab_int).last_b).next = NULL;
	*(actions + (*index)) = RRB;
	(*index)++;
}

void	ft_ra(int *index, t_array *tab_int, t_operations *actions)//first becomes last
{
	if (!((*tab_int).first_a))
		return ;
	if (!((*(*tab_int).first_a).next))
		return ;
	(*(*tab_int).last_a).next = (*tab_int).first_a;
	(*(*tab_int).first_a).prev = (*tab_int).last_a;
	(*tab_int).first_a = (*(*tab_int).first_a).next;
	(*tab_int).last_a = (*(*tab_int).last_a).next;
	(*(*tab_int).first_a).prev = NULL;
	(*(*tab_int).last_a).next = NULL;
	*(actions + (*index)) = RA;
	(*index)++;
}

void	ft_rb(int *index, t_array *tab_int, t_operations *actions)
{
	if (!((*tab_int).first_b))
		return ;
	if (!((*(*tab_int).first_b).next))
		return ;
	(*(*tab_int).last_b).next = (*tab_int).first_b;
	(*(*tab_int).first_b).prev = (*tab_int).last_b;
	(*tab_int).first_b = (*(*tab_int).first_b).next;
	(*tab_int).last_b = (*(*tab_int).last_b).next;
	(*(*tab_int).first_b).prev = NULL;
	(*(*tab_int).last_b).next = NULL;
	*(actions + (*index)) = RB;
	(*index)++;
}
