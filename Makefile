NAME = minishell

NAMA = minishell.a

SRC = main.c utils.c get_next_line.c get_next_line_utils.c bultins/ft_echo.c bultins/ft_cd.c bultins/ft_pwd.c ft_exit.c\
	ft_split.c ft_env.c bultins/ft_cntrl_c.c ft_export.c ft_unset.c ft_execve.c ft_split_1.c env.c ft_atoi.c

OBJ = $(SRC:.c=.o)

#CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAMA) $(OBJ)
	gcc  $(NAMA) -o $(NAME)
	@echo 'SUCCESS!' 
clean :
	rm -rf $(OBJ)
fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAMA)
re : fclean all