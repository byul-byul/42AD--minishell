/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:10:47 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 23:21:00 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

# ifndef SIZE_MAX
#  define SIZE_MAX 18446744073709551615UL
# endif

# ifndef MAX_FD
#  define MAX_FD OPEN_MAX
# endif

# define LEN			21

# define TRUE			1
# define FALSE			0

# define MAX_INT		2147483647
# define MIN_INT		-2147483648
# define MAX_LL			9223372036854775807LL
# define MIN_LL			-9223372036854775808LL
# define MAX_SQRT_INT	2147395600

# define FLAG_ZERO		0b00000001
# define FLAG_DASH		0b00000010
# define FLAG_PLUS		0b00000100
# define FLAG_SHRP		0b00001000
# define FLAG_SPCE		0b00010000
# define FLAG_PRNT		0b00100000

# define SPACE_SET		" \f\n\r\t\v"
# define INT_BASE		"0123456789"
# define SEPARATOR		'\n'

typedef unsigned int		t_unint;
typedef unsigned char		t_unchr;
typedef const char			t_cchr;
typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_arg
{
	t_unchr	flags;
	va_list	value;
	char	type;
	char	*prefix;
	char	sign;
	int		width;
	int		prec;
	int		is_up;
	int		base;
	int		res;
}				t_arg;

size_t	ft_arrlen(t_cchr **arr, size_t size);
size_t	ft_arrsize(char **arr);
void	ft_freearr(char **arr, ssize_t size);
char	**ft_arrdup(char **src, size_t size);

int		ft_isascii(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_iswhitespace(int c);
int		ft_iswhitespacestr(char *str);
int		ft_isspacestr(char *str);
int		ft_isdigit(int c);
int		ft_isxdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isinstr(int c, t_cchr *str);
int		ft_isalphas(t_cchr *str);
int		ft_isdigits(t_cchr *str);
int		ft_isxdigits(t_cchr *str);
int		ft_isalnums(t_cchr *str);
int		ft_isduplicate(int c, t_cchr *pos, t_cchr *str);
int		ft_isprime(int nb);
int		ft_issquare(int nb);
int		ft_isdollarsign(int c);
int		ft_issinglequote(int c);
int		ft_isdoublequote(int c);
int		ft_isopenparentheses(int c);
int		ft_iscloseparentheses(int c);
int		ft_isparentheses(int c);
int		ft_isquote(int c);

void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memrchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

int		ft_sqrt(int nb);
int		ft_factorial(int nb);
int		ft_power(int nb, int power);
int		ft_numlen(t_ll num, int base_len);

void	ft_putchar(char c);
void	ft_putstr(t_cchr *s);
void	ft_putendl(t_cchr *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(t_cchr *s, int fd);
void	ft_putendl_fd(t_cchr *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_base(t_ll nbr, t_cchr *base);
void	ft_putnbr_base_fd(t_ll nbr, t_cchr *base, int fd);

size_t	ft_strlen(t_cchr *s);
int		ft_strcmp(t_cchr *s1, t_cchr *s2);
int		ft_strncmp(t_cchr *s1, t_cchr *s2, size_t n);
size_t	ft_strlcat(char *dest, t_cchr *src, size_t size);
size_t	ft_strlcpy(char *dst, t_cchr *src, size_t size);
char	*ft_strcat(char *dest, t_cchr *src);
char	*ft_strncat(char *dest, t_cchr *src, size_t n);
char	*ft_strcpy(char *dest, t_cchr *src);
char	*ft_strncpy(char *dest, t_cchr *src, unsigned int n);
char	*ft_strdup(t_cchr *s);
char	*ft_strndup(t_cchr *s, size_t n);
char	*ft_strtrim(char const *str, char const *set);
char	*ft_substr(char const *str, t_unint start, size_t len);
char	*ft_strchr(t_cchr *s, int c);
char	*ft_strrchr(t_cchr *s, int c);
char	*ft_strstr(t_cchr *s1, t_cchr *s2);
char	*ft_strnstr(t_cchr *s1, t_cchr *s2, size_t len);
char	**ft_split(char const *arr, char c);
char	**ft_split_charset(t_cchr *arr, t_cchr *charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strljoin(t_cchr *s1, t_cchr *s2, size_t len1, size_t len2);
char	*ft_strjoin_charset(int size, t_cchr **strs, t_cchr *sep);
char	*ft_strljoin_charset(int s, size_t *lens, t_cchr **strs, t_cchr *sep);
char	*ft_strmapi(char const *str, char (*f)(t_unint, char));
void	ft_striteri(char *s, void (*f)(t_unint, char *));
char	*ft_skipspace(char *str);
char	*ft_skipchar(char c, char *str);
char	*ft_skipcharset(char *str, t_cchr *charset);
char	*ft_keepcharset(char *str, t_cchr *charset);
int		ft_charpos(char c, t_cchr *str);
size_t	ft_substrlen(char *str, t_cchr *charset);
int		ft_substrcount(char *str, t_cchr *charset);
int		ft_safeappendchar(char **str, char c);
int		ft_safeappendstr(char **str, char *append);

int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(t_cchr *nptr);
char	*ft_itoa(int n);
char	*ft_convert_base(char *nbr, t_cchr *base_from, t_cchr *base_to);
int		ft_atoi_base(t_cchr *nptr, t_cchr *base);
char	*ft_itoa_base(int nbr, t_cchr *base);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);

int		ft_printf(const char *str, ...);
int		putchar_len_times(int len, char c);
int		flag_check(t_arg *arg, t_unchr flag);
void	arg_printer(t_arg *arg);
void	num_printer(t_arg *arg);
t_ull	get_num_type(t_arg *arg);

#endif