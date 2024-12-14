#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# define NB_SORTING_ELEM 6
# define NB_MAX_COMB 50
# define MC 9
# define ML 6
# define MI 5 

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef enum {
	END = 0, 
	PA,
	PB,
	SA,
	SB,
	RA,
	RRA,
	RB,
	RRB, // indicates an end of list
} t_operations;

typedef struct s_list
{
	int	num;
	struct s_list *next;
	struct s_list *prev;
} t_list;

typedef struct s_keystone{
	int num;
	char on_off;
}	t_keystone;

typedef struct s_array{
	int save;
	int size;
	int overflow;
	int index_actions;
	int count_keystone;
	t_keystone *tab; 
	t_list *origin;
	t_list *first_a;
	t_list *first_b;
	t_list *last_a;
	t_list *last_b;
	t_list *v_stack;
	t_operations *actions;
} t_array; 

int		ft_atoi_overflow(char *str, int *overflow, int *i);
int		get_size(int argc, char *str_argv);
int		fill_tab_str(int argc, char *str_argv, t_array *tab_int);
int		fill_tab_argv(int argc, char **argv, t_array *tab_int);
int	init_brute_force(t_list *first_a, t_array *tab_int);
int 	ft_unsorted(t_list *v_stack);
int 	ft_brute_force(t_array *v_stack);
void 	set_comb(int *comb, int index);
void	ft_init_list(t_list *stack, int size);
void	ft_swap(int *a, int *b);
void	ft_sort_int_array(t_keystone *array, int size);
void	ft_swap_a(int *index, t_list *first_a, t_operations *actions);
void	ft_swap_b(int *index, t_list* first_b, t_operations *actions);
void	ft_push_b(int *index, t_array *tab_int, t_operations *actions);
void	ft_rra(int *index, t_array *tab_int, t_operations *actions);
void	ft_push_a(int *index, t_array *tab_int, t_operations *actions);
void	ft_rrb(int *index, t_array *tab_int, t_operations *actions);
void	ft_ra(int *index, t_array *tab_int, t_operations *actions);
void	ft_rb(int *index, t_array *tab_int, t_operations *actions);
void	bforce_ft_swap_a(t_list *first_a);
void	bforce_ft_swap_b(t_list *first_b);
void	bforce_ft_push_b(t_array *tab_int);
void	bforce_ft_push_a(t_array *tab_int);
void	bforce_ft_rra(t_array *tab_int);
void	bforce_ft_rrb(t_array *tab_int);
void	bforce_ft_ra(t_array *tab_int);
void	bforce_ft_rb(t_array *tab_int);
void 	sorting_algo(t_array *tab_int);
//debug
void debug_printlist(t_list *stack);

#endif
