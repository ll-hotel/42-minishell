/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 13:22:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

int				ft_atoi(const char *nptr);
long			ft_atol(const char *nptr);
void			ft_bzero(void *s, unsigned long n);
void			*ft_calloc(unsigned long nmemb, unsigned long size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, unsigned long n);
int				ft_memcmp(const void *s1, const void *s2, unsigned long n);
void			*ft_memcpy(void *dest, const void *src, unsigned long n);
void			*ft_memmove(void *dest, const void *src, unsigned long n);
void			*ft_memset(void *s, int c, unsigned long n);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			**ft_split(const char *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
unsigned long	ft_strlcat(char *dst, const char *src, unsigned long size);
unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long size);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
unsigned long	ft_strlen(const char *s);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, unsigned long n);
char			*ft_strnstr(const char *big, const char *little,
					unsigned long len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_substr(const char *s, unsigned int start, \
					unsigned long len);
int				ft_tolower(int c);
int				ft_toupper(int c);

typedef struct s_list	t_list;
struct	s_list
{
	t_list	*next;
	void	*content;
};

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *_new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *_new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_log_b(long n, unsigned long b);
int				ft_log_ub(unsigned long n, unsigned long b);
char			*ft_utoa(unsigned int n);
char			*ft_xtoa(unsigned long value, short ox, short capital);

#endif
