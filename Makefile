SERVER_EXE_NAME = ircserv
SERVER_DIR = Server
SERVER_SRC = $(addprefix $(SERVER_DIR)/, $(addsuffix .cpp, \
	$(addprefix Network/, ServClient ) \
	Server \
))
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
SEVER_BUILD_OBJS = $(SERVER_OBJ)
SERVER_INCS = -I$(SERVER_DIR)
SERVER_ENTRY_POINT = $(SERVER_DIR)/main.cpp

CC = c++
FLAGS = -g -std=c++98 -Wall -Werror -Wextra
INCS = $(SERVER_INCS)

all: $(SERVER_EXE_NAME)

$(SERVER_EXE_NAME): $(SEVER_BUILD_OBJS)
	$(CC) $(FLAGS) $(INCS) $^ $(SERVER_ENTRY_POINT) -o $@
	
$(SERVER_OBJ): %.o: %.cpp
	$(CC) $(FLAGS) $(SERVER_INCS) -c $< -o $@

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(BUILD_OBJS)

re: fclean all
