# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/13 13:11:49 by aben-azz          #+#    #+#              #
#    Updated: 2019/02/03 00:38:13 by aben-azz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m
NAME			=	libftprintf.a
CC				=	gcc
CFLAGS			+=	-Wall -Werror -Wextra
LIBFT_PATH		?=	./libft/
LIBFT_NAME		=	libft.a
SRC_PATH		=	./src/
SRC_NAME		=	ft_printf.c
MSG				=	Compilation de
SRC				=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ_PATH		=	./obj/
OBJ_NAME		=	$(SRC_NAME:.c=.o)
OBJ				=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INCLUDES		=	$(LIBFT_PATH)includes ./includes/
INC_CC	 		=	$(foreach DIR,$(INCLUDES),-I$(DIR) )
CFLAGS			+=	$(INC_CC)
LONGEST			=	$(shell echo $(notdir $(SRCS)) | tr " " "\n" | awk ' { if (\
				length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I./ -o $@ -c $<
	@printf "$(_BOLD)$(_PURPLE)$(MSG)$(_END) $(_CYAN)%-$(LONGEST)s\
	$(_END)" $(notdir $<)
	@if test -s src/$*.c; then \
	printf "$(_GREEN) [OK]\n$(_END)";\
	else \
	printf "$(_RED) [ERROR]\n$(_END)"; fi

all: $(LIBFT_PATH)$(LIBFT_NAME) $(NAME)

$(LIBFT_PATH)$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH);

$(NAME): $(OBJ)
	@echo "$(_BOLD)$(_YELLOW)Creation de la libftprintf ...$(_END)"
	@cp $(LIBFT_PATH)$(LIBFT_NAME) $(NAME)
	@$(AR) rcs $(NAME) $^
		@echo "$(_BOLD)$(_GREEN)Compilation de la libftprintf terminée => ${NAME}$(_END)"
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
debug :
	@gcc main.c libftprintf.a -o o -Wall -Wextra -Werror
	@printf "$(_GREEN)main.c pret$(_END)\n"
re: fclean all
.PHONY: all, clean, fclean, re, $(LIBFT_PATH)$(LIBFT_NAME)
