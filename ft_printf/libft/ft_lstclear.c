/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:23 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/19 12:56:39 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		if (temp->content)
			ft_lstdelone(temp, (*del));
		temp = next;
	}
	*lst = NULL;
}
