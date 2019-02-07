/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:36:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/07 21:48:17 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# define MAX OPEN_MAX
# define BUFF_SIZE 32

typedef	unsigned short int	t_bits;
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, void *src, size_t n);
void			*ft_memccpy(void *dst, void *src, int c, size_t n);
void			*ft_memmove(void *dst, void *src, size_t len);
void			*ft_memchr(void *s, int c, size_t n);
int				ft_memcmp(void *s1, void *s2, size_t n);
size_t			ft_strlen(char *s);
char			*ft_strdup(char *s1);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strncpy(char *dst, char *src, size_t len);
char			*ft_strcat(char *s1, char *s2);
char			*ft_strncat(char *s1, char *s2, size_t n);
size_t			ft_strlcat(char *dst, char *src, size_t size);
char			*ft_strchr(char *s, int c);
char			*ft_strrchr(char *s, int c);
char			*ft_strstr(char *haystack, char *needle);
char			*ft_strnstr(char *haystack, char *needle,
		size_t len);
int				intlen(long long len);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				ft_atoi(char *str);
void			ft_ftoa(long double n, int precision, char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_is_space(int c);
int				ft_indexof(char *source, char c);
int				ft_count(char *source, char c);
int				ft_repeat_char(char source, int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char *s, char (*f)(char));
char			*ft_strmapi(char *s, char (*f)(unsigned int, char));
int				ft_strequ(char *s1, char *s2);
int				ft_strnequ(char *s1, char *s2, size_t n);
char			*ft_strsub(char *s, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strtrim(char *s);
char			**ft_strsplit(char *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putendl(char *s);
void			ft_putnbr(long long n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(long long n, int fd);
char			*ft_itoa_base(intmax_t n, int base, int islower);
char			*ft_utoa_base(uintmax_t nb, int base, int uppercase);
long long		ft_pow(int base, int i);
long double		ft_round(long double fl, long precision);
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
int				get_next_line(int fd, char **line, char separator);
int				is_even(int number);
int				abs(int n);
t_bits			get_bit(t_bits i, t_bits n);
t_bits			rev_bit(t_bits i, t_bits n);
t_bits			up_bit(t_bits i, t_bits n);
t_bits			down_bits(t_bits i, t_bits n);
typedef struct	s_gnl
{
	int			i;
	int			i_read;
	char		buff[BUFF_SIZE + 1];
	char		*ptr_leak;
	char		*s[MAX];
}				t_gnl;

#endif
