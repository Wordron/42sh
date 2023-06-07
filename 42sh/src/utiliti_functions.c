/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** utiliti_functions
*/

char *my_strreplace(char *str, char to_be_replaced, char replace)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == to_be_replaced)
            str[i] = replace;
    }
    return (str);
}

int my_strlen(char *str, char end, int start)
{
    int size = start;

    while (str[size] != '\0' && str[size] != end)
        size++;
    return (size);
}

char *my_strcpy(char *dest, char *src, int i)
{
    for (int j = 0; src[j] != '\0'; j++) {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}
