# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct mihemmi{
    char *name;
    char *nickname;
    struct mihemmi *next;
}               mihm;

mihm    *create_node(char *name, char *nickname)
{
    mihm *red;

    red = malloc(sizeof (mihm));
    red->name = strdup(name);
    red->nickname = strdup(nickname);
    return (red);
}
int main(void)
{
    mihm *red;
    mihm *red1;
    mihm *red2;

    red = create_node("mohamed", "shrbi_a_3mri");
    red1 = create_node("abdelouahed" , "tabi3a");
    red2 = create_node("abderrahman", "lmodir");
    red->next = red1;
    red1->next = red2;
    printf("red ==> name :%s\n nickname : %s\n", red->name, red->nickname);
    printf("==> red1 ==> name :%s\n nickname : %s\n", red->next->name, red->next->nickname);
    printf("==> red2 ==> name :%s\n nickname : %s\n", red->next->next->name, red->next->next->nickname);
}