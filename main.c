#include "push_swap.h"

void ft_print_sorted_sequence(t_operations *actions, t_array *tab_int)
{
	int i = 0;

	while (i <= (*tab_int).index_actions)
	{
		if (*(actions + i) == PA)
		{
			write(1, "pa\n", 3);
		}
		else if (*(actions + i) == PB)
		{
			write(1, "pb\n", 3);
		}
		else if (*(actions + i) == SA)
		{	
			write(1, "sa\n", 3);
		}
		else if (*(actions + i) == SB)
		{
			write(1, "sb\n", 3);
		}
		else if (*(actions + i) == RA)
		{
			write(1, "ra\n", 3);
		}
		else if (*(actions + i) == RB)
		{
			write(1, "rb\n", 3);
		}
		else if (*(actions + i) == RRA)
		{
			write(1, "rra\n", 4);
		}
		else if (*(actions + i) == RRB)
		{
			write(1, "rrb\n", 4);
		}
		++i;
	}
}

int main(int argc, char **argv)
{
	static t_array tab_int;

	if (argc == 2)
	{
		if (!fill_tab_str(argc, argv[1], &tab_int))
			return (write(1, "malloc failed\n", 14), 1);
	}
	else
	{
		if (!fill_tab_argv(argc, argv, &tab_int))
			return (write(1, "malloc failed\n", 14), 1);
	}
	if (tab_int.overflow == 1)
		return (free(tab_int.tab), write(1, "overflow\n", 9), 1);
	ft_init_list(tab_int.first_a, tab_int.size);
	if (tab_int.size == 1 || ft_unsorted(tab_int.first_a) == 0)
		return (free(tab_int.tab), 0);
	ft_sort_int_array(tab_int.tab, tab_int.size);

	//puts("\tstack a -----------------------");
	//debug_printlist(tab_int.first_a);

	if (!init_brute_force((tab_int).first_a, &(tab_int)))
	{
		ft_print_sorted_sequence(tab_int.actions, &tab_int);
		return (free(tab_int.tab), 0);
	}
	sorting_algo((&(tab_int)));
//	puts("stack b -----------------------");
//	debug_printlist(tab_int.first_b);
	ft_print_sorted_sequence(tab_int.actions, &tab_int);
	return (free(tab_int.tab), 0);
}

