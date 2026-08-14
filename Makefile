NAME :=	matrix

CXX := c++
CXXFLAGS :=	-g -MP -MMD -std=c++20# -Wall -Wextra -Werror

LIB_DIR :=	lib/
INC_DIR :=	inc/
SRC_DIR :=	src/
OBJ_DIR :=	.obj/

INCLUDE_DIRS :=	-I$(INC_DIR) -I$(LIB_DIR)
LFLAGS :=

SRCS :=	src/main.cpp	\

OBJS :=	$(SRCS:%.cpp=$(OBJ_DIR)%.o)
DEPS :=	$(SRCS:%.cpp=$(OBJ_DIR)%.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)