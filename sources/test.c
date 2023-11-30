/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:07:23 by bpochlau          #+#    #+#             */
/*   Updated: 2023/11/29 15:20:16 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (void)
{
	char	*path = "/bin/ls";
	char	*argv[] = {"/bin/ls", "-lsa", NULL};

	execve(path, argv, NULL);
}

// #include <stdio.h>


// int main(void) {
//  char *args[] = {"/bin/ls", "-lsa", NULL};
//  execve(args[0], args, NULL);
//  return 0;
// }
