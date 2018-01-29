
/*
** Example demonstrating fork() function call.
** Run it in the background to see process IDs.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int	i;

    printf("\n\nAbout to 'fork' a process...\n\n");
    i = fork();
    printf("Fork returned %d\n", i);
    while (1);
}
