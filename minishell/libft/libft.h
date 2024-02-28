/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:40:46 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/23 14:28:16 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdint.h> 
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# define TRUE 1
# define FALSE 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5 
# endif

# define LOWER_HEX_BASE  "0123456789abcdef"
# define UPPER_HEX_BASE  "0123456789ABCDEF"
# define ULONG_MAX		"18446744073709551615"

typedef int	t_boolean;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;


void				ft_free_tab(char **tab);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_nblen(int n);
unsigned long long	ft_cntdgt(unsigned long long n, int base);
int					ft_printf(const char *format, ...);
int					ft_print_str(char *str);
int					ft_print_uns_int(unsigned int n);
int					ft_print_ptr(unsigned long long n);
int					ft_print_int(int n);
int					ft_print_hex(unsigned int n, const char *base);
int					ft_print_char(char c);
int					ft_eval_format(va_list args, const char format);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char const			*ft_strnstr(const char *big,
						const char *little, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_extract_line(char *line);
int					ft_check(char *storage);
char				*ft_line_maker(int fd, char *buf, char *storage);
char				*get_next_line(int fd);
int					ft_strcmp(const char *s1, const char *s2);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
int					ft_lstsize(t_list *lst);

#endif
