# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

/**************************PARSING******************************/
int		ft_atoi(char *str);
int	ft_isdigit(int c);
void	ft_putnbr(int nb);
#endif