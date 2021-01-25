
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

// int main (void)
// {
// 	int fd[2];
// 	pipe(fd);  
//     char **tab;
//     int i = 0;
//     tab = (char **)malloc(sizeof(char*) * (4 + 1));
//     tab[0] = strdup("ls");
//     tab[1] = strdup("-la");
//     tab[2] = strdup("tail");
//     tab[3] = strdup("-2");
//     tab[4] = NULL;
// 	int child1 = fork();
// 	while (tab[i])
// 	{
//         if(child1 == 0)
//         {
//                 close(fd[READ_END]);
//             if ((tab[i] + 1) != NULL)
//             {
//                 dup2(fd[WRITE_END], 1); 
//             }
//             execlp(tab[i], tab[i], tab[i + 1], NULL);
//         }
//         int status;
//         waitpid(child1, &status, 0);
//         i++;
//         close(fd[WRITE_END]);
//         dup2(fd[READ_END], 0);
//         execlp(tab[i], tab[i], tab[i+1],NULL);
//         close(fd[READ_END]);
//         close(fd[WRITE_END]);

//     }
// }

// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>

// #define READ_END 0
// #define WRITE_END 1

int main (void)
{
	int fd[2];
    int fdd = 0;
    char **tab;
    int i = 0;
    tab = (char **)malloc(sizeof(char*) * (8 + 1));
    tab[0] = strdup("ls");
    tab[1] = strdup("-la");
    tab[2] = strdup("tail");
    tab[3] = strdup("-2");
    tab[4] = strdup("sort");
    tab[5] = strdup("-r");
    tab[6] = strdup("tail");
    tab[7] = strdup("-1");
    tab[8] = NULL;
	int child1;

	while (tab[i])
	{
        // if (not mys cmd || (cmd->next))
        pipe(fd);
        child1 = fork();
        if (child1 == 0)
        {
            dup2(fdd, 0);
           // close(fd[0]);
            if (tab[i + 2] != NULL)
            {
                dup2(fd[WRITE_END], 1);
               // close(fd[WRITE_END]);
            }
            // if (strcmp(tab[i], "echo"))
            // {
            //     printf
            // }
            close(fd[READ_END]);
            execlp(tab[i], tab[i], tab[i + 1], NULL);
            exit(1);
        }else
        {
            wait(NULL);
            fdd = fd[0];
            close(fd[WRITE_END]);
            i += 2;
            /* code */
        }
        
    }
}
