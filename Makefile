NAME 		:=	fillit

F_N			:=	reader solver main board check_piece
FILES		:=	$(addprefix fillit_srcs/, $(addsuffix .c, $(F_N)))
OBJS		:=	$(addprefix objects/, $(addsuffix .o, $(F_N)))	

FLAGS		:= -Wall -Wextra -Werror
INCL		:= -I fillit_srcs/ -I libft/

LIB 		:= libft
LIB_LINK	:= -L $(LIB) -l ft

.PHONY: all clean fclean re

all : $(NAME)

objects/%.o: fillit_srcs/%.c
	@/bin/mkdir -p objects
	@gcc $(FLAGS) -c $(INCL) $< -o $@

$(NAME) : $(OBJS)
	@make -C $(LIB)
	@gcc $(LIB_LINK) $(OBJS) -o $(NAME)

clean :
	@/bin/rm -rf objects
	@make -C libft clean

fclean : clean
	@/bin/rm -f $(NAME)
	@make -C libft fclean

re : fclean all
