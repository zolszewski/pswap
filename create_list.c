/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <zoolszew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:13:39 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/14 08:57:50 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi_overflow(char *str, int *overflow, int *i)
{
	int sign;
	unsigned int	result;
	
	sign = 1;
	result = 0;
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++; // Skip whitespace
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[(*i)++] == '-')
			sign = -1;
	}

	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = (str[*i] - '0') + (result * 10);  // Correct dereferencing of i
		if ((sign == -1 && result > 0x80000000) || (sign == 1 && result > 0x7fffffff))
		{
			write(1, "overflow\n", 9);
			*overflow = 1;
			break;
		}
		(*i)++;  // Increment the pointer after reading each digit
	}
	return (result * sign);
}

int	get_size(int argc, char *str_argv)
{
	int	i;
	int size;
	
	i = 0;
	size = 0;
	if (argc < 2)
		return (0);
	if (*str_argv == '\0')
		return (0);
	while (*(str_argv + i) != '\0')
	{
		if (*(str_argv + i) <= '9' && *(str_argv + i) >= '0')
		{
			++size;
			while (*(str_argv + i) <= '9' && *(str_argv + i) >= '0')
				++i;
		}
		else
			++i;
	}
	return (size);
}

int alloc(t_array *tab_int)
{
	(*tab_int).tab = malloc((*tab_int).size * sizeof(t_keystone)
	+ (*tab_int).size * sizeof(t_list)
	+ (*tab_int).size * (*tab_int).size * (*tab_int).size * sizeof(t_operations)
	+ (*tab_int).size * sizeof(t_list));
	if (!tab_int->tab)
		return (1);
	(*tab_int).first_a = (t_list *)((*tab_int).tab + (*tab_int).size);
	(*tab_int).last_a = (t_list *)((*tab_int).first_a + (*tab_int).size - 1);
	(*tab_int).actions = (t_operations *)((*tab_int).first_a + (*tab_int).size);
	(*tab_int).v_stack = (t_list *)((*tab_int).actions + (*tab_int).size * (*tab_int).size * (*tab_int).size);
	return (0);
}

int fill_tab_str(int argc, char *str_argv, t_array *tab_int)
{
	static int	i = 0;
	static int j = 0;
	
	tab_int->size = get_size(argc, str_argv);
	if (tab_int->size == 0)
		return (0);
	if (alloc(tab_int))
		return (0); 
	while (*(str_argv + i) != 0)
	{
		(*((*tab_int).tab + j)).num = ft_atoi_overflow(str_argv, &((*tab_int).overflow), &i);
		if ((*tab_int).overflow == 1)
			return (1);
		(*((*tab_int).tab + j)).on_off = 0; //(*tab_int).tab = t_keystone, contenant num et on_off.
		(*((*tab_int).first_a + j)).num = (*((*tab_int).tab + j)).num;
		//printf("2cd tab = %d  stack = %d\n", (tab_int->tab[j]).num, (tab_int->first_a[j]).num);
		++j;
	}
	return (1);
}


int fill_tab_argv(int argc, char **argv, t_array *tab_int)
{
	static int i = 0;
	static int j = 1;
	(*tab_int).size = argc - 1;
	if ((*tab_int).size == 0)
		return (0);
	if (alloc(tab_int))
		return (0);
	while (j < argc)
	{
		(tab_int->tab[j - 1]).num = ft_atoi_overflow(argv[j], &(tab_int->overflow), &i);
		if ((*tab_int).overflow == 1)
			return (1);
		(tab_int->tab[j - 1]).on_off = 0;
		i = 0;
		(tab_int->first_a[j - 1]).num = (tab_int->tab[j - 1]).num;
		//printf("2cd tab = %d  stack = %d\n", (tab_int->tab[j - 1]).num, (tab_int->first_a[j - 1]).num);
		j++;	
	}
	return (1);
}

void ft_init_list(t_list *stack, int size)
{
	int i;
	
	i = 1;
	if (size == 1)
		return (void)(stack[0].prev = NULL, stack[0].next = NULL, /*printf("current = %p, prev = %p, num = %d, next = %p\n", stack, stack->prev, stack->num, stack->next)*/ (void)0);
	stack[0].prev = NULL;
	stack[0].next = stack + i; // &stack[i]
	while (i < size - 1)
	{
		stack[i].prev = stack + i - 1; // &stack[i - 1]
		stack[i].next = stack + i + 1;
		++i;
	}
	stack[size - 1].prev = stack + size - 2; //DONC &(stack[size - 2]), -2 est l'avant dernier
	stack[size - 1].next = NULL;
}
