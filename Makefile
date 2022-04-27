# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 10:35:48 by jodufour          #+#    #+#              #
#    Updated: 2022/04/27 10:41:30 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CXX				=	c++ -c
LINK			=	c++
MKDIR			=	mkdir -p
RM				=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME			=	unit_test.out

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR			=	srcs/
OBJ_DIR			=	objs/
INC_DIR			=	include/
PRV_DIR			=	private/

######################################
#            SOURCE FILES            #
######################################
SRC				=	\
					main.cpp

######################################
#            OBJECT FILES            #
######################################
OBJ				=	${SRC:.cpp=.o}
OBJ				:=	${addprefix ${OBJ_DIR}, ${OBJ}}

DEP				=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CPPFLAGS		=	-Wall -Wextra -Werror
CPPFLAGS		+=	-std=c++98
CPPFLAGS		+=	-MMD -MP

LDFLAGS			=	

ifeq (${DEBUG}, 1)
	CPPFLAGS	+=	-g
endif

#######################################
#                RULES                #
#######################################
${NAME}: ${OBJ}
	${LINK} ${OBJ} ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CPPFLAGS} $< ${OUTPUT_OPTION}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

re: clean all

fre: fclean all

.PHONY: all clean fclean re fre
