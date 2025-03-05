#include "philo.h"

//The correct input must be ./philo 5 800 200 200  
void    error_msg(char *error)
{
    printf("%s\n", error);
    exit(EXIT_FAILURE);
}
static inline bool is_digit(int c)
{
    return (c >= '0' && c <= '9');
}

static long valid_input_check(const char *str)
{
    long    index;
    long    len;
    char    nb;

    len = 0;
    index = 0;
    nb = 1;
    if (str[index] == ' ')
        index++;
    else if (str[index] == '+')
        index++;
    else if (!is_digit(str[index]))
        error_msg("Only gidits accepted");
    else if (str[index] == '-')
        error_msg("Only positive numbers accepted");
    nb = str;
    while(is_digit(str[index]))
        len++;
    if (len > 10)
        error_msg("Error! INT MAX is the limit");
    return (nb);
}
static long    ft_atol(const char *str)
{
    long    num;

    str = valid_input_check(&str);
    while(is_digit(*str))
        num = (num * 10) + (*str++ - 48);
    if (num > INT_MAX)
        error_msg("INT MAX is the limit, please enter smaller numbers");
    return (num);
}

void    parsing(int argc, char **argv)
{
    t_table *table;

    table->nbr_philos = atol(argv[1]);
    table->time_die = atol(argv[2]);
    table->time_eat = atol(argv[3]);
    table->time_sleep = atol(argv[4]);
    if (table->time_die < 60 || table->time_eat < 60 
        || table->time_sleep < 60 || table->nbr_philos <= 0)
            return 1;
    if (argv[5])
        table->nb_meals = atol(argv[5]);
    else if (!argv[5])
        table->nb_meals = -1;
}
