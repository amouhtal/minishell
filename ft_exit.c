#include "includes/minishell.h"

int ft_exit()
{
	int fd;
	fd = open("exit" , O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, "1", 1);
	puts("  ////   \t  ////");
	puts(" (°>°)   \t (°>°)");
	puts("__| |__  \t__| |__");
	puts("--   --  \t--   -- ");
	puts(" ) | )   \t ) | )");
	puts("( ( )    \t( ( ) ");
	puts(" |||    \t |||");
	puts(" > >    \t  > >");
	exit(0);
	return 0;
}