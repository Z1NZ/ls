# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srabah <srabah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/08 22:22:31 by srabah            #+#    #+#              #
#    Updated: 2014/12/15 01:18:09 by srabah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

FILES_C = ft_aff_right.c \
	ft_display_3.c \
	ft_display_2.c \
	ft_display_1.c \
	ft_liste_file.c \
	ft_process_ls.c \
	ft_process_ls_2.c \
	ft_process_ls_3.c \
	ft_process_ls_4.c \
	ft_strlenbigger.c \
	ft_lstadd.c \
	ft_lstadd_end.c \
	ft_lstdel.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstnew.c \
	main.c

FILES_O = $(FILES_C:.c=.o) 

all: $(NAME)

$(NAME): remake_libft $(FILES_O)
	@gcc $(FLAGS) $(FILES_O) -I includes -I libft/includes -L libft -lft -o ft_ls
	@echo "\\033[1;32mSuccess."
	

remake_libft:
	@make -C libft/

$(FILES_O):
	@echo "\\033[1;34mGenerating objects... Please wait."
	@gcc $(FLAGS) $(FILES_C) -c -g -I libft/includes -I includes
	

.PHONY: clean fclean re

clean:
	make clean -C libft/
	@echo "\\033[1;34mDeleting objects..."
	@rm -f $(FILES_O)

fclean: clean
	make fclean -C libft/
	@echo "\\033[1;34mDeleting ft_ls.a..."
	@rm -f $(NAME)

re: fclean all
	make re -C libft/
	
