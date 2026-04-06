/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:20:13 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/06 17:11:14 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "philo.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_lstadd_back_gc(t_list **lst, t_list *new_node);
void				*ft_calloc_gc(size_t nmemb, size_t size);
t_list				*ft_lstnew_gc(void *content);
void				*ft_malloc(size_t nmemb, size_t size);
void				ft_free_malloc(void *ptr);
void				ft_free_all_malloc(void);

#endif