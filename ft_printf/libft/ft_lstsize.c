/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:36:43 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/19 15:06:17 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*temp;

	n = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		n ++;
	}
	return (n);
}
// #include <stdio.h>
// int	main()
// {
// 	t_list *l;
//  	int actual;
//  	int expected;

//  	l = ft_lstnew(ft_strdup("1"));
//  	l->next = ft_lstnew(ft_strdup("2"));
//  	l->next->next = ft_lstnew(ft_strdup("3"));
//  	expected = 3;
//  	actual = ft_lstsize(l);
// 	printf("size: %d \n", actual);
//  	if (actual == expected)
//  		printf("GOOD");
//  	else
// 		printf("not");
// }
