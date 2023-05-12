SRCS :	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
	ft_putptr_fd.c

OBJS : ${SRCS:.c=.o}
NAME : libftprintf.a
LIBC : ar -rcs
CC : cc 
RM : rm -f
FLAGS : -Wall -Werror -Wextra 

.c.o:
	${CC} ${FLAGS} -c $< -o${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}	

all: ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 