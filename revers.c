
#include "cub3d.h"
char	*trim_firs(const char *s)
{
    char *s1;

    s1 = ft_strdup(s, 0);
	s1++;
	return ((char *)s);
}

char *function(char *str)
{
    char *retur;
    char *tmp;

    if (strlen(str) < 0)
        return (str);
    tmp = function(trim_firs(str));
    retur = ft_strjoin(tmp, &str[0], 0);
    return retur;
}

int main()
{
    char *str = "hello";
    puts(function(str));
    return 0;
}

