#include "push_swap.h"

int ft_unsorted(t_list *v_stack)
{
	if (v_stack == NULL)
		return (1);
	while ((*v_stack).next != NULL)
	{
		if ((*v_stack).num < (*(*v_stack).next).num)
		{
			//printf("%d", (*v_stack).num);
			v_stack = (*v_stack).next;
		}
		else
			return (1);
	}
	return (0);
}

int init_brute_force(t_list *first_a, t_array *tab_int)
{
	t_list *v_stack;
	int i;

	v_stack = (*tab_int).v_stack;
	i = 0;
	while (first_a != NULL)
	{
		(*(v_stack + i)).num = (*first_a).num;
		if (i > 0)
			(*(v_stack + i)).prev = v_stack + i - 1;
		else
			(*(v_stack + i)).prev = NULL;
		if ((*first_a).next != NULL)
			(*(v_stack + i)).next = v_stack + i + 1;
		else
			(*(v_stack + i)).next = NULL;
		i++;
		first_a = (*first_a).next;
	}
	(*tab_int).origin = (*tab_int).first_a;
	(*tab_int).v_stack = v_stack;
	(*tab_int).first_a = v_stack;
	(*tab_int).last_a = v_stack + i - 1;
	(*tab_int).first_b = NULL;
	(*tab_int).last_b = NULL;
	return (ft_brute_force(tab_int));
}
int	check_comb(int *comb, int index)
{
	while (index > -1)
	{
		if (*(comb + index) != RRB)
			return (0);
		--index;
	}
	return (1);
}
void set_comb(int *comb, int index)
{
	int i;

	i = index; // PENSER A : eliminer les combinaisons symetriques.
	*(comb + index) += 1 + ((*(comb + index - (index != 0)) == PA && *(comb + index) + (index != 0) == PB)
	|| (*(comb + index - (index != 0)) == PB && *(comb + index) + (index != 0) == PA) //here is bool=, (index != 0) is equal
	|| (*(comb + index - (index != 0)) == RA && *(comb + index) + (index != 0) == RRA) // to 1 if True/
	|| (*(comb + index - (index != 0)) == RRA && *(comb + index) + (index != 0) == RA)
	|| (*(comb + index - (index != 0)) == RRB && *(comb + index) + (index != 0) == RB));
	while (i > 0)
	{
		if (*(comb + i) == RRB + 1)
		{
			++(*(comb + i - 1));  //the precedent check *(comb + i - 1) is set to +1 - 9 becomes 
			//first case 1 and second 1 - 1 1; 
			*(comb + i) = PA + (*(comb + index - 1) == PB);
		}
		else
			break;
		--i;
	}
	if (i == 0 && *(comb + i) == RRB + 1)
		*(comb + i) = PA;
}
void debug_print_comb(int *comb, int index)
{
				printf("comb = ");
			for (int i = 0; i < index + 1; ++i)
				printf("%d ", *(comb + i));
			putchar('\n');
}

void back_to_origin(t_array *tab_int, t_list *first_a, t_list *origin)
{
	int i;
	int size;

	size = (*tab_int).size - 1;
	(*tab_int).first_b = NULL;
	(*tab_int).last_b = NULL;
	(*tab_int).first_a = (*tab_int).v_stack;
	(*tab_int).last_a = (*tab_int).v_stack + size;

	(*first_a).num = (*origin).num;
	(*first_a).prev = NULL;
	(*first_a).next = first_a + 1;
	i = 1;
	while (i < size)
	{
		(*(first_a + i)).num = (*(origin + i)).num;
		(*(first_a + i)).prev = first_a + i - 1;
		(*(first_a + i)).next = first_a + i + 1;
		++i;
	}
	(*(first_a + size)).num = (*(origin + size)).num;
	(*(first_a + size)).prev = first_a + size - 1;
	(*(first_a + size)).next = NULL;
}

void do_viurtual_operations(t_array *tab_int, int *comb)
{
		if (*comb == PA)
		{
			bforce_ft_push_a(tab_int);
		}
		else if (*comb == PB)
		{
			bforce_ft_push_b(tab_int);
		}
		else if (*comb == SA)
		{	
			bforce_ft_swap_a((*tab_int).first_a);
		}
		else if (*comb == SB)
		{
			bforce_ft_swap_b((*tab_int).first_b);
		}
		else if (*comb == RA)
		{
			bforce_ft_ra(tab_int);
		}
		else if (*comb == RB)
		{
			bforce_ft_rb(tab_int);
		}
		else if (*comb == RRA)
		{
			bforce_ft_rra(tab_int);
		}
		else if (*comb == RRB)
		{
			bforce_ft_rrb(tab_int);
		}
}

void do_operations(t_array *tab_int, int *comb)
{
		if (*comb == PA)
		{
			ft_push_a(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		}
		else if (*comb == PB)
		{
			ft_push_b(&(*tab_int).index_actions, tab_int, (*tab_int).actions);
		}
		else if (*comb == SA)
		{	
			ft_swap_a(&((*tab_int).index_actions), (*tab_int).first_a, (*tab_int).actions);
		}
		else if (*comb == SB)
		{
			ft_swap_b(&((*tab_int).index_actions), (*tab_int).first_b, (*tab_int).actions);
		}
		else if (*comb == RA)
		{
			ft_ra(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		}
		else if (*comb == RB)
		{
			ft_rb(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		}
		else if (*comb == RRA)
		{
			ft_rra(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		}
		else if (*comb == RRB)
		{
			ft_rrb(&((*tab_int).index_actions), tab_int, (*tab_int).actions);
		}
}

int test_comb(int *comb, t_array *tab_int)
{
	int i;

	i = 0;
	while (*(comb + i) != 0)
	{
		do_viurtual_operations(tab_int, comb + i);
		if (!(ft_unsorted((*tab_int).first_a)) && !((*tab_int).first_b))
			return (0);
		++i;
	}
	back_to_origin(tab_int, (*tab_int).v_stack, (*tab_int).origin);
	return (1);
}

void print_comb(int *comb, t_array *tab_int)
{
	int i;

	i = 0;
	while (*(comb + i) != 0)
	{
		do_operations(tab_int, comb + i);
		++i;
	}
}

int ft_brute_force(t_array *tab_int)
{
	int unsorted;
	int comb[NB_MAX_COMB];
	int index;
	int i;

	unsorted = 1;
	index = 0;
	i = 0;
	while (i < NB_MAX_COMB)
	{
		comb[i] = END;
		i++;
	}
	while (unsorted && index < MC)
	{
		if ((*tab_int).size > ML && index > MI)
			return 1;
		while (unsorted)
		{
			set_comb(comb, index);
			unsorted = test_comb(comb, tab_int);
			if (check_comb(comb, index)) // when everything is set to RRB, prog stops/
				break;
		}
		(*(comb + index + 1)) = RRB;
		++index;
	}
	print_comb(comb, tab_int);
	//puts("----------------LAST----------------");
	//debug_printlist((*tab_int).first_a);
	return (unsorted);
}
