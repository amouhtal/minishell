NAME = minishell

NAMA = minishell.a

SRC = main.c utils.c get_next_line.c get_next_line_utils.c ft_split.c ft_split_1.c parsing/env.c \
parsing/token.c parsing/check_fir.c parsing/check_sec.c minishell.c bultins/ft_cd.c bultins/ft_cntrl_c.c bultins/ft_pwd.c \
ft_exit.c ft_unset.c ft_export.c  ft_env.c ft_atoi.c bultins/ft_echo.c ft_execve.c 
 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAMA) $(OBJ)
	@gcc $(CFLAGS) $(NAMA) -o $(NAME)
	@echo 'SUCCESS!' 
clean :
	@rm -rf $(OBJ)
fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAMA)
re : fclean all