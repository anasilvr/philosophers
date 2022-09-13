# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 09:47:30 by anarodri          #+#    #+#              #
#    Updated: 2022/09/09 14:06:27 by anarodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc
CFLAGS	=	-g -pthread
#CFLAGS	=	-Wall -Wextra -Werror -g -pthread
RM		=	rm -rf

SRC		=	$(addprefix src/, init.c main.c philoacts.c philocontrol.c timeutils.c utils.c)
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all



.PHONY: all clean fclean re