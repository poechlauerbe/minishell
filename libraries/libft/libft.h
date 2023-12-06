/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:30:19 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 17:23:17 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// include libraries
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

// define default BUFFER_SIZE for get_next_line if not defined dur. compilation
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/*		a struct that links to another struct resulting in a linked list	*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*		determine if a char is...		*/

/* determines if a character is a printable (ASCII 32 - 126)
	Return values:
	1: printable;		0: not printable*/
int		ft_isprint(int c);
/* determines if a character is a digit (ASCII 48 - 57)
	Return values:
	1: digit;		0: not a digit*/
int		ft_isdigit(int c);
/* determines if a character is an ASCII character (ASCII 0 - 127)
	Return values:
	1: ASCII;		0: not ASCII*/
int		ft_isascii(int c);
/* determines if a character is part of alphabet (ASCII 65 - 90 and 97 - 122)
	Return values:
	1: alphabet character;		0: not an alphabet character*/
int		ft_isalpha(int c);
/* determines if a character is alphanumberic (see ft_isalpha and ft_isdigit)
	Return values:
	1: alphanumeric;		0: not alphanumeric*/
int		ft_isalnum(int c);

/*		convert char to upper-/lowercase		*/

// converts a lowercase character to upperc. and returns the character as an int
int		ft_toupper(int c);
// converts an upperc. character to lowerc. and returns the character as an int
int		ft_tolower(int c);

/*		string manipulation		*/

// determines the length of a string s and returns its length
size_t	ft_strlen(const char *s);
/* Takes a destination and a src string as input plus size and returns the
	length of the source string; if size permits it NULL terminates the string*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/* Concatenates two strings, NULL terminates the resulting string and returns
	the length of the string it tried to create */
size_t	ft_strlcat(char *dst, const char *src, size_t size);
/* Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
	specified in ’set’ removed from the beginning and the end of the string;
	Return values:
	returns a pointer to the trimmed string;
	returns NULL if the allocation failed */
char	*ft_strtrim(char const *s1, char const *set);
/* Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’
	Return values:
	returns the substring;
	returns NULL if the allocation failed */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/* Allocates (with malloc(3)) and returns a new string, which is the result of
	the concatenation of ’s1’ and ’s2’.
	Return values:
	returns the new string;
	returns NULL if the allocation fails */
char	*ft_strjoin(char const *s1, char const *s2);
/* Allocates (with malloc(3)) and returns an array of strings obtained by
	splitting ’s’ using the character ’c’ as a delimiter. The array must end
	with a NULL pointer.
	Return values:
	returns the array of new strings resulting from the split;
	returns NULL if the allocation fails */
char	**ft_split(char const *s, char c);
/* Applies the function ’f’ to each character of the string ’s’, and passing its
	index as first argument to create a new string (with malloc(3)) resulting
	from successive applications of ’f’
	Return values:
	returns the string created by successive applications of 'f';
	returns NULL if the allocation fails */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/* Returns a pointer to the first occurrence of the character c in the string s.
	Otherwise it returns NULL */
char	*ft_strchr(const char *s, int c);
/* Returns a pointer to the last occurrence of the character c in the string s.
	If the character is not found, it returns NULL. */
char	*ft_strrchr(const char *s, int c);
/* Finds the first occurrence of the substring small in the string big. The
	terminating null bytes (aq\0aq) are not compared.
	Return values:
	returns a pointer to the beginning of the substring;
	returns NULL if the substring is not found. */
char	*ft_strnstr(const char *big, const char *little, size_t len);
/*  Returns a pointer to a new string which is a duplicate of the string s.
	Memory for the new string is obtained with malloc(3).
	Returns NULL if insufficient memory was available. */
char	*ft_strdup(const char *s);
/* Compares the two strings s1 and s2. It returns an integer less than, equal
	to, or greater than zero if s1 is found, respectively, to be less than, to
	match, or be greater than s2.  */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* Applies the function ’f’ on each character of the string passed as argument,
	passing its index as first argument. Each character is passed by address to
	’f’ to be modified if necessary. */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*		put functions		*/

// Outputs the string ’s’ to the given file descriptor followed by a newline.
void	ft_putendl_fd(char *s, int fd);
// Outputs the integer ’n’ to the given file descriptor.
void	ft_putnbr_fd(int n, int fd);
// Outputs the character ’c’ to the given file descriptor.
void	ft_putchar_fd(char c, int fd);
// Outputs the string ’s’ to the given file descriptor.
void	ft_putstr_fd(char *s, int fd);
/* Allocates (with malloc(3)) and returns a string representing the integer
	received as an argument
	Return values:
	returns the string representing the integer;
	returns NULL if the allocation fails */
char	*ft_itoa(int n);
/* Converts the initial portion of the string pointed to by nptr to int.
	Return values:
	The converted value. */
int		ft_atoi(const char *nptr);

/*		memory manipulation 	*/

/* Sets the first n bytes of the area starting at s to zero (bytes containing
	aq\0aq). */
void	ft_bzero(void *s, size_t n);
/* Fills the first n bytes of the memory area pointed to by s with the constant
	byte c. */
void	*ft_memset(void *s, int c, size_t n);
/* Copies n bytes from memory area src to memory area dest. The memory areas may
	overlap: if src is smaller than destination, copying starts with the last
	element. Otherwise we start with the first element */
void	*ft_memmove(void *dest, const void *src, size_t n);
/* Copies n bytes from memory area src to memory area dest. The memory areas
	must not overlap.  */
void	*ft_memcpy(void *dest, const void *src, size_t n);
/* Scans the initial n bytes of the memory area pointed to by s for the first
	instance of c.
	Return values:
	returns a pointer to the matching byte;
	returns NULL if the character does not occur in the given memory area */
void	*ft_memchr(const void *s, int c, size_t n);
/* Compares the first n bytes (each interpreted as unsigned char) of the memory
	areas s1 and s2.
	Return values:
	returns an integer less than, equal to, or greater than zero if the first n
	bytes of s1 is found, respectively, to be less than, to match, or be greater
	than the first n bytes of s2. */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/* Allocates memory for an array of nmemb elements of size bytes each and
	returns a pointer to the allocated memory. The memory is set to zero. If
	nmemb or size is 0, then calloc() returns either NULL, or a unique pointer
	value that can later be successfully passed to free().  */
void	*ft_calloc(size_t nmemb, size_t size);

/*		list functions 	*/

/* Allocates (with malloc(3)) and returns a new node. The member variable
	’content’ is initialized with the value of the parameter ’content’. The
	variable ’next’ is initialized to NULL
	Return value:
	returns a pointer to the new node;
	return NULL if allocations fails. */
t_list	*ft_lstnew(void *content);
// Adds the node ’new’ at the beginning of the list.
void	ft_lstadd_front(t_list **lst, t_list *new);
/* Counts the number of nodes in a list.
	Return value:
	the length of the list. */
int		ft_lstsize(t_list *lst);
// Returns the last node of the list.
t_list	*ft_lstlast(t_list *lst);
/* Iterates the list ’lst’ and applies the function ’f’ on the content of each
	node. Creates a new list resulting of the successive applications of the
	function ’f’. The ’del’ function is used to delete the content of a node if
	needed.
	Return values:
	returns a pointer to the new list;
	returns NULL if the allocation fails. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// Adds the node ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new);
/* Takes as a parameter a node and frees the memory of the node’s content using
	the function ’del’ given as a parameter and free the node. The memory of
	’next’ must not be freed. */
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/* Deletes and frees the given node and every successor of that node, using the
	function ’del’ and free(3). Sets the pointer to the list to NULL */
void	ft_lstclear(t_list **lst, void (*del)(void *));
/* Iterates the list ’lst’ and applies the function ’f’ on the content of each
	node. */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*		get_next_line functions		*/

typedef struct s_list1
{
	char			*str_buf;
	struct s_list1	*next;
}	t_list1;

t_list1	*ft_lstlast_gnl(t_list1 *lst);
void	copy_str(t_list1 *list, char *str);
void	ft_add_elem(t_list1 **lst, char *buf, int fd);
char	*get_next_line(int fd);
int		ft_lst_strlen(t_list1 *lst);
int		ft_check(t_list1 *list);

/*		printf functions		*/

// checks the input and selects the according function depending on the selector
void	ft_check_prntf(char s, int *len, va_list *args);
// puts a character and simultaneously increases the variable len by one
void	ft_putchar(int c, int *len);
// puts a string and simultaneously increases len by one for each character
void	ft_putstr(char *s, int *len);
// prints a pointer variable to the screen and increases len
void	ft_putptr(void *ptr, int *len);
// puts an int to to the screen and increases len
void	ft_putnbr(int n, int *len);
// prints an unsigned number to the screen and increases len
void	ft_putuns(unsigned int n, int *len);
// prints a hexadecimal to the screen and increases len
void	ft_puthex(char s, unsigned int nbr, int *len);
// an implementation of the printf function
int		ft_printf(const char *s, ...);

/* printf_fd */
// for description see printf functions; only difference writes to fd specified
int		ft_printf_fd(int fd, const char *s, ...);
void	ft_check_prntffd(char s, int *len, va_list *args, int fd);
void	ft_putchar_pffd(int c, int *len, int fd);
void	ft_putchar_pffd(int c, int *len, int fd);
void	ft_putptr_pffd(void *ptr, int *len, int fd);
void	ft_putnbr_pffd(int n, int *len, int fd);
void	ft_putuns_pffd(unsigned int n, int *len, int fd);
void	ft_puthex_pffd(char s, unsigned int nbr, int *len, int fd);

#endif
