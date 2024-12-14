#include "push_swap.h"

void ft_swap(int *a, int *b)
{
	int	vessel;

	vessel = *a;
	*a = *b;
	*b = vessel;
}

void ft_sort_int_array(t_keystone *array, int size)
{
	 int i;
	 int j;
	int imin;

	i = 0;
	j = 0;
	while (i < size - 1)
	{
		imin = i;
		j = i + 1;
		//trouver l'index de la valeur la plus petite du array
		while (j < size)
		{
			if ((*(array + j)).num < (*(array + imin)).num)
				imin = j;
			j++;
		}
		ft_swap(&((*(array + i)).num), &((*(array + imin)).num));
		i++;
	}
}