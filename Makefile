# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 10:35:48 by jodufour          #+#    #+#              #
#    Updated: 2022/05/25 21:11:05 by jodufour         ###   ########.fr        #
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
				test_reverse_iterator.cpp

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
CXXFLAGS	+=	-std=c++98
CXXFLAGS	+=	-MMD -MP
CXXFLAGS	+=	-I${INC_DIR}
CXXFLAGS	+=	-I${PRV_DIR}

LDFLAGS		=	

VGFLAGS		=	--leak-check=full
VGFLAGS		+=	--show-leak-kinds=all
VGFLAGS		+=	--track-fds=yes

ifeq (${DEBUG}, 1)
	CXXFLAGS	+=	-g
endif

#######################################
#                RULES                #
#######################################
.PHONY: all clean fclean re fre

${NAME}: ${OBJ}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

test: ${NAME}
	${VG} ${VGFLAGS} ./$<

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
