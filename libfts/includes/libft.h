/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:17:42 by ulysse            #+#    #+#             */
/*   Updated: 2024/09/18 21:00:36 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 10
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

bool	is_flag(char c, const char *str);
void	ft_putchar(char c, int *nbr);
void	ft_putstr(const char *s, int *nbr, int *blank);
void	ft_putnbr_basep(unsigned long long n, char *base, int *nbr, int output);
void	print_blank(int blank, int *nbr);
void	ft_putunbr_printf(unsigned int n, int *nbr, int output);
void	ft_putptr_printf(void *ptr, int *nbr, int output);
int		minus_flag(const char *str, int *i);
int		printf_bonus_converted(const char *str, int *i, int *nbr);
int		ft_printf(int output, const char *str, ...);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
long	ft_atoi(const char *nptr);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_countwords(char *str, char c);
char	*ft_get_next_line(int fd);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char *str, char c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_putchar_fd(const char c, int *nbr, int fd);
void	ft_putstr_fd(const char *s, int *nbr, int fd);
void	ft_putnbr_fd(int n, int *nbr, int fd);
void	ft_putendl_fd(char *s, int *nbr, int fd);
void	ft_striteri(char *s, void (*f) (unsigned int, char *));
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
#endif //LIBFT_H
