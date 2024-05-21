/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:15:45 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/10 12:47:19 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

/**
 * @brief Get next line from a file
 * @param fd The file descriptor of an opened file
 * @return The line read from the file or NULL if there is none
*/
char	*get_next_line(int fd);

/**
 * @brief Saves the exceding string after the '\\n'
 * @param buffer The string to parse and save
 * @return The string saved after the '\\n'
*/
char	*save_str(char *buffer);

/**
 * @brief Gets the string until the '\\n'
 * @param buffer The string read from the file
 * @return The line (string until the '\\n')
*/
char	*get_lines(char *buffer);

/**
 * @brief Gets the string until the '\\n'
 * @param fd The file descriptor of an opened file
 * @param buffer The static string to save what is read from file
 * @return The string read from file
*/
char	*read_file(int fd, char *buffer, int bytes_read);

//UTILS
int		ft_strlen(char *s);
int		ft_strchr(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
