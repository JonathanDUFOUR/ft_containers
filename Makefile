# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 10:35:48 by jodufour          #+#    #+#              #
#    Updated: 2022/05/27 17:14:18 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CXX			=	clang++
LINK		=	clang++
MKDIR		=	mkdir -p
RM			=	rm -rf
VG			=	valgrind

######################################
#             EXECUTABLE             #
######################################
NAME		=	unit_test.out

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR		=	srcs/
OBJ_DIR		=	objs/
INC_DIR		=	include/
PRV_DIR		=	private/

######################################
#            SOURCE FILES            #
######################################
SRC			=	\
				main.cpp						\
				test_bidirectional_iterator.cpp	\
				test_forward_iterator.cpp		\
				test_input_iterator.cpp			\
				test_output_iterator.cpp		\
				test_random_access_iterator.cpp	\
				test_reverse_iterator.cpp		\
				test_stack.cpp					\

######################################
#            OBJECT FILES            #
######################################
OBJ			=	${SRC:.cpp=.o}
OBJ			:=	${addprefix ${OBJ_DIR}, ${OBJ}}

DEP			=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CXXFLAGS	=	-c
CXXFLAGS	+=	-Wall -Wextra -Werror
CXXFLAGS	+=	-Wshadow
CXXFLAGS	+=	-Weffc++
CXXFLAGS	+=	-std=c++98
CXXFLAGS	+=	-pedantic
CXXFLAGS	+=	-MMD -MP
CXXFLAGS	+=	-I${INC_DIR}
CXXFLAGS	+=	-I${PRV_DIR}

LDFLAGS		=	

VGFLAGS		=	--leak-check=full
VGFLAGS		+=	--show-leak-kinds=all
VGFLAGS		+=	--track-fds=yes

ifeq (${DEBUG}, 1)
	CXXFLAGS	+=	-g
else \
ifeq (${DEBUG}, 2)
	CXXFLAGS	+=	-g
	CXXFLAGS	+=	-fsanitize=address
	CXXFLAGS	+=	-fsanitize=leak
	CXXFLAGS	+=	-fsanitize=undefined

	LDFLAGS		+=	-fsanitize=address
	LDFLAGS		+=	-fsanitize=leak
	LDFLAGS		+=	-fsanitize=undefined
endif

#######################################
#                RULES                #
#######################################
.PHONY: all clean fclean re fre

${NAME}: ${OBJ}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

test: ${NAME}
	${VG} ${VGFLAGS} ./$< ; if [ $$? -eq 0 ] ; then echo "\033[38;2;0;255;0m>>> SUCCESS <<<" ; else echo "\033[38;2;255;0;0m>>> FAILURE <<<" ; fi

-include ${DEP}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} $< ${CXXFLAGS} ${OUTPUT_OPTION}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

re: clean all

fre: fclean all

-include ${HOME}/Templates/mk_files/coffee.mk
