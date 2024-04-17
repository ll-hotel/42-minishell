/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/16 16:28:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H
# include <stdint.h>

int						ft_atoi(const char *nptr);
long					ft_atol(const char *nptr);
void					ft_bzero(void *s, uint64_t n);
void					*ft_calloc(uint64_t nmemb, uint64_t size);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
char					*ft_itoa(int n);
void					*ft_memchr(const void *s, int c, uint64_t n);
int						ft_memcmp(const void *s1, const void *s2, uint64_t n);
void					*ft_memcpy(void *dest, const void *src, uint64_t n);
void					*ft_memmove(void *dest, const void *src, uint64_t n);
void					*ft_memset(void *s, int c, uint64_t n);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
char					**ft_split(const char *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
uint64_t				ft_strlcpy(char *dst, const char *src, uint64_t size);
void					ft_striteri(char *s, void (*f)(uint32_t, char *));
uint64_t				ft_strlen(const char *s);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_strmapi(const char *s, char (*f)(uint32_t, char));
int						ft_strncmp(const char *s1, const char *s2, uint64_t n);
char					*ft_strnstr(const char *big, const char *little,
							uint64_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(const char *s1, const char *set);
char					*ft_substr(const char *s, uint32_t start, \
							uint64_t len);
int						ft_tolower(int c);
int						ft_toupper(int c);

typedef struct s_list
{
	struct s_list		*next;
	void				*content;
}						t_list;

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *_new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *_new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

int						ft_log_b(int64_t n, uint64_t b);
int						ft_log_ub(uint64_t n, uint64_t b);
char					*ft_utoa(unsigned int n);
char					*ft_xtoa(uint64_t value, short ox, short capital);

#endif
