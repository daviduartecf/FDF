/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:05:22 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 15:57:20 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main ()
// {
// 	t_list *l = ft_lstnew(ft_strdup("nyacat"));
//  	t_list *n = ft_lstnew(ft_strdup("OKOKOK"));

// 	printf("After strdup l = %s\n", (char *)l->content);
// 	printf("After strdup n = %s\n", (char *)n->content);

//  	ft_lstadd_front(&l, n);
//  	if (l == n && !ft_strncmp(l->content, "OK", 7))
//  	{
//  		printf("OKOK\n");
//  	}
// 	printf("nono\n");
// 	printf("AFTER l = %s\n", (char *)l->content);
// 	printf("AFTER n = %s\n", (char *)n->content);
// }
// int	main()
// {
// 	t_list *list;
// 	t_list *new;
// 	int	i;

// 	i = 0;
// 	list = NULL;
// 	new = (t_list *)malloc(sizeof(t_list));
// 	new->content = "first added";
// 	new->next = NULL;
// 	ft_lstadd_front(&list, new);
// 	while (i < 4)
// 	{
// 		new = (t_list *)malloc(sizeof(t_list));
// 		new->content = "string";
// 		new->next = NULL;
// 		ft_lstadd_front(&list, new);
// 		i ++;
// 	}
// 	new = (t_list *)malloc(sizeof(t_list));
// 	new->content = "last added";
// 	new->next = NULL;
// 	ft_lstadd_front(&list, new);
// 	while (list != NULL)
// 	{
// 		printf("%s\n", (char *)list->content);
// 		list = list->next;
// 	}
// 	while (list != NULL)
// 	{
// 		t_list *temp = list->next;
// 		free(list);
// 		list = temp;
// 	}
// }
