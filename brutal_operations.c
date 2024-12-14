#include "push_swap.h"

void	bforce_ft_swap_a(t_list *first_a)
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
	ft_swap(a, b);
}

void	bforce_ft_swap_b(t_list *first_b)
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
	ft_swap(a, b);
}

void	bforce_ft_push_b(t_array *tab_int)
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
}

void	bforce_ft_push_a(t_array *tab_int)
{
	t_list	*new_first_b;

	if (!(*tab_int).first_b)
		return ;
	if (!((*(*tab_int).first_b).next))
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
}

void	bforce_ft_rra(t_array *tab_int)
{	
	if (!((*tab_int).first_a))
		return ;
	if (!((*(*tab_int).first_a).next))
		return ;
	(*(*tab_int).first_a).prev = (*tab_int).last_a;
	(*(*tab_int).last_a).next = (*tab_int).first_a;
	(*tab_int).last_a = (*tab_int).first_a;
	(*tab_int).first_a = (*(*tab_int).first_a).next;
	(*(*tab_int).first_a).prev = NULL;
	(*(*tab_int).last_a).next = NULL;
}
void	bforce_ft_rrb(t_array *tab_int)
{	
	if (!((*tab_int).first_b))
		return ;
	if (!((*(*tab_int).first_b).next))
		return ;
	(*(*tab_int).first_b).prev = (*tab_int).last_b;
	(*(*tab_int).last_b).next = (*tab_int).first_b;
	(*tab_int).last_b = (*tab_int).first_b;
	(*tab_int).first_b = (*(*tab_int).first_b).next;
	(*(*tab_int).first_b).prev = NULL;
	(*(*tab_int).last_b).next = NULL;
}

void	bforce_ft_ra(t_array *tab_int)//first becomes last
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
}

void	bforce_ft_rb(t_array *tab_int)
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
}