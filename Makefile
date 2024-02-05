SERVER_EXE_NAME = ircserv
SERVER_DIR = Server
SERVER_SRC = $(addprefix $(SERVER_DIR)/, $(addsuffix .cpp, \
	Server \
))
# $(addprefix Network/, ServClient ) \
	
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
SERVER_INCS = -I$(SERVER_DIR) -IUtilities
SERVER_ENTRY_POINT = $(SERVER_DIR)/main.cpp

CC = c++
FLAGS = -g -std=c++98 -Wall -Werror -Wextra
INCS = $(SERVER_INCS)

all: $(SERVER_EXE_NAME)

$(SERVER_EXE_NAME): $(SERVER_OBJ)
	$(CC) $(FLAGS) $(INCS) $^ $(SERVER_ENTRY_POINT) -o $@
	
$(SERVER_OBJ): %.o: %.cpp
	$(CC) $(FLAGS) $(SERVER_INCS) -c $< -o $@

clean:
	rm -f $(SERVER_EXE_NAME)

fclean: clean
	rm -f $(SERVER_OBJ)

re: fclean all
