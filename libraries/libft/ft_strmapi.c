/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:14:21 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/08 14:39:27 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*ptr;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
char custom_map(unsigned int index, char c) {
    // For example, convert lowercase characters to uppercase
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

void test_ft_strmapi(const char *input) {
    printf("Input: %s\n", input);

    // Apply ft_strmapi with custom_map function
    char *output = ft_strmapi(input, custom_map);

    if (output != NULL) {
        printf("Result: %s\n", output);
        free(output); // Free the allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
}

int main() {
    const char *test_string1 = "Hello, World!";
    const char *test_string2 = "abc123DEF";

    test_ft_strmapi(test_string1);
    test_ft_strmapi(test_string2);

    return 0;
}
 */
