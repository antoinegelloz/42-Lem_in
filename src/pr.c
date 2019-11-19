#include "lem_in.h"

void	print_ssize_t(t_list *list)
{
	t_list		*curr;

	//ft_putstr("print ssize_t list: ");
	curr = list;
	while (curr)
	{
		ft_printf("%d ", *(size_t *)curr->content);
		curr = curr->next;
	}
	ft_putchar('\n');
}
