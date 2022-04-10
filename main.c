
#include <stdio.h>
#include <dirent.h>

int is_match(char *str, char *match)
{
    int i;
    int j;

    i = j = 0;
    while(str[i] && match[j])
    {
        if (str[i] == match[j])
        {
            i++;
            j++;
        }
        if (match[j] == '*')
        {
            while(str[i] && match[j + 1] != str[i])
                i++;
            j++;
        }
        else if (str[i] != match[j])
            break ;
    }
    if (!str[i] && !match[j])
        return (1);
    else
        return (0);
}

int main(void)
{
	printf("%d\n", is_match("efile", "*e"));
}
