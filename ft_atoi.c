
#include "includes/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
				|| str[i] == '\f' || str[i] == '\v') && str[i])
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

static int  ft_count(long n)
{
    int count;
    count = 0;
    if (n < 0)
    {
        n = n * (-1);
        count++;
    }
    while (n > 9)
    {
        n = n / 10;
        count++;
    }
    count++;
    return (count);
}

char        *ft_itoa(int n)
{
    int     count;
    char    *str;
    int     sign;
    long    l;
    l = n;
    sign = 0;
    count = ft_count(l);
    if (l < 0)
    {
        sign = 1;
        l = l * (-1);
    }
    str = (char *)malloc((count + 1) * sizeof(char));
    if (str == NULL)
        return (NULL);
    str[count--] = '\0';
    while (count >= 0)
    {
        str[count--] = (l % 10) + '0';
        l = l / 10;
    }
    if (sign == 1)
        str[0] = '-';
    return (str);
}