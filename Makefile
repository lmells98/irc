# ============================================================================ /
# 			IRC Network
# ============================================================================ /
NETWORK_DIR = Network
NETWORK_SRC = $(addprefix $(NETWORK_DIR)/, $(addsuffix .cpp, \
	ClientConnection	))
NETWORK_OBJ = $(NETWORK_SRC:.cpp=.o)
# ============================================================================ /
# 			IRC Server
# ============================================================================ /
SERVER_EXE_NAME = ircserv
SERVER_DIR = Server
SERVER_SRC = $(addprefix $(SERVER_DIR)/, $(addsuffix .cpp, \
	Server	))
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
SERVER_ENTRY_POINT = $(SERVER_DIR)/main.cpp
SERVER_INCS = -I$(NETWORK_DIR) -I$(SERVER_DIR) -IUtilities
# ============================================================================ /
# 			IRC Client
# ============================================================================ /
CLIENT_EXE_NAME = ircclient
CLIENT_DIR = Client
CLIENT_SRC = $(addprefix $(CLIENT_DIR)/, $(addsuffix .cpp, \
	Client	))
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)
CLIENT_ENTRY_POINT = $(CLIENT_DIR)/main.cpp
CLIENT_INCS = -I$(NETWORK_DIR) -I$(CLIENT_DIR) -IUtilities
# ============================================================================ /
# 			Compiler
# ============================================================================ /
CC = c++
FLAGS = -g -std=c++98 -Wall -Werror -Wextra
# ============================================================================ /
# 			Compile Executables
# ============================================================================ /
all: $(SERVER_EXE_NAME) $(CLIENT_EXE_NAME)
server: $(SERVER_EXE_NAME)
client: $(CLIENT_EXE_NAME)
# 	~~ Server ~~
$(SERVER_EXE_NAME): $(NETWORK_OBJ) $(SERVER_OBJ)
	$(CC) $(FLAGS) $(SERVER_INCS) $(NETWORK_OBJ) $(SERVER_OBJ) $(SERVER_ENTRY_POINT) -o $@
# 	~~ Client ~~
$(CLIENT_EXE_NAME): $(NETWORK_OBJ) $(CLIENT_OBJ)
	$(CC) $(FLAGS) $(CLIENT_INCS) $(NETWORK_OBJ) $(CLIENT_OBJ) $(CLIENT_ENTRY_POINT) -o $@
# ============================================================================ /
# 			Build Objects
# ============================================================================ /
$(NETWORK_OBJ): %.o: %.cpp
	$(CC) $(FLAGS) -I$(NETWORK_DIR) -c $< -o $@

$(SERVER_OBJ): %.o: %.cpp
	$(CC) $(FLAGS) $(SERVER_INCS) -c $< -o $@

$(CLIENT_OBJ): %.o: %.cpp
	$(CC) $(FLAGS) $(CLIENT_INCS) -c $< -o $@
# ============================================================================ /
# 			Clean & Rebuild
# ============================================================================ /
clean:
	rm -f $(SERVER_EXE_NAME) $(CLIENT_EXE_NAME)

fclean: clean
	rm -f $(NETWORK_OBJ) $(SERVER_OBJ) $(CLIENT_OBJ)

re: fclean all
