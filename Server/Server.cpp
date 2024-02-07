/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:49:38 by lmells            #+#    #+#             */
/*   Updated: 2024/02/07 13:50:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	IRC::Server::log(const std::string &message, bool nextOutputOnSameLine = false)
{
	static bool	cursorOnSameLine;

	std::ios originalOutputFormat(NULL);
	originalOutputFormat.copyfmt(std::cout);

	if (nextOutputOnSameLine && !cursorOnSameLine)
		std::cout << c_LogConfig.getPrefix() << ": " << std::setw(c_LogConfig.getActionFieldWidth()) << std::left << message << "\e[s";

	else if (cursorOnSameLine && !nextOutputOnSameLine)
		std::cout << "| " << std::setw(c_LogConfig.getResultFieldWidth()) << std::left << message << std::endl;

	else
		std::cout << c_LogConfig.getPrefix() << ": " << std::left << std::setw(c_LogConfig.getLineLength()) << message << std::endl;

	std::cout.flush();
	cursorOnSameLine = nextOutputOnSameLine;
	std::cout.copyfmt(originalOutputFormat);
}

IRC::Server::Server(const std::string &name, const std::string &portStr, const std::string &password) :	c_Name(name),
																										c_LogConfig(IRC::LogConfig::initialise(name)),
																										c_PortStr(portStr),
																										c_Password(password),
																										c_Host("127.0.0.1")
{
	log(c_LogConfig.fillLine());
	log("");
	log(centerStringInTextField(c_LogConfig.getLineLength(), "{ FT_IRC SERVER }", ' '));
	log(combineStringWithDividerCenterTextField(c_LogConfig.getLineLength(), "Host Address", c_Host, ":"));
	log(combineStringWithDividerCenterTextField(c_LogConfig.getLineLength(), "Port Number", c_PortStr, ":"));
	log(combineStringWithDividerCenterTextField(c_LogConfig.getLineLength(), "Password", c_Password, ":"));
	log("");
	log(c_LogConfig.fillLine());
	log(centerStringInTextField(c_LogConfig.getActionFieldWidth(), "Performing Action", ' '), true);
	log(centerStringInTextField(c_LogConfig.getResultFieldWidth(), "Result", ' '));
	log(c_LogConfig.fillLine());

	m_Running = true;
	m_Socket_fd = createSocketConnection();
}

IRC::Server::~Server(void)
{
	// !! TESTING PURPOSES ONLY !!
	// ~~ This is not a valid solution...
	// ~~ I was just getting a crash on exit without doing this...
	try
	{
		const size_t		countClients = m_Clients.size();
		std::ostringstream	ss;

		ss << "Clients Connected: " << countClients;
		log(ss.str());
		ss.clear();

		for (size_t i = 0; i < countClients; i++)
		{
			int							client_fd = m_PollSockets[i + 1].fd;
			Network::ClientConnection	*connection = m_Clients.at(client_fd);

			log(c_LogConfig.fillLine('~'));
			char	output[c_LogConfig.getLineLength()] = {0};
			sprintf(output, "Client connected from %s:%d (refer to socket_fd[%i])", connection->getHostname().c_str(), connection->getPort(), connection->getSocket());
			log(output);
			log(c_LogConfig.fillLine('~'));

			// m_Clients.erase(client_fd);
			delete connection;
		}
	}
	catch(const std::exception& e)
	{
		log(c_LogConfig.fillLine('~'));
		throw runtimeError(ERR_DELETE_CONNECTION, e.what(), true);
	}
}

int	IRC::Server::createSocketConnection(void)
{
	// Socket endpoint for IO communication.
	// ~~ domain	: AF_INET - (Address Family) Internet IPv4 Addresses.
	// ~~ type		: SOCK_STREAM - Send byte stream for communications.
	// ~~ protocol	: 0 - TCP.
	log("Creating socket connection...", true);
	int	servSocket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket_fd < 0)
		throw runtimeError(ERR_SOCK_CREATE, "Couldn't open socket connection because : ", true);
	log(PRINT_SUCCESS);

	// Socket options for client connections.
	// ~~ fd		: servSocket_fd - File descriptor that refers to server socket.
	// ~~ level		: SOL_SOCKET - Modify at socket level.
	// ~~ optname	: SO_READDUSER - Allows the reuse of local addresses, except when an active listening socket is bound to that address.
	// ~~ optval	: Address of options variable - Gives access to options value.
	// ~~ optlen	: Buffer size for options variable.
	log("Setting socket options...", true);
	int	options = 1;
	if (setsockopt(servSocket_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) < 0)
		throw runtimeError(ERR_SOCK_CREATE, "Couldn't set socket options because : ", true);
	log(PRINT_SUCCESS);

	// Proccess wont wait for read() & write() calls to finish executing before continuing.
	log("Setting socket to \"non-blocking\" mode...", true);
	if (fcntl(servSocket_fd, F_SETFL, O_NONBLOCK) < 0)
		throw runtimeError(ERR_SOCK_CREATE, "Couldn't set socket to \"non-blocking\" mode because : ", true);
	log(PRINT_SUCCESS);

	// Bind the socket's file descriptor to the socket address for I/O communications over the connection.
	log("Binding IP address to socket...", true);
	sockaddr_in	serverSocketAddress = {
		.sin_family = AF_INET,	// AF_INET - (Address Family) Internet IPv4 Addresses.
		.sin_port 	= htons(atoi(c_PortStr.c_str())),	// Convert from host machine endian to network protocol endian.
		.sin_addr 	= (in_addr){.s_addr = INADDR_ANY},	// Accept any incoming connections to this address.
		.sin_zero 	= {0}
	};
	if (bind(servSocket_fd, (sockaddr *)&serverSocketAddress, sizeof(serverSocketAddress)) < 0)
		throw runtimeError(ERR_SOCK_CREATE, "Couldn't set socket options because : ", true);
	log(PRINT_SUCCESS);

	return (servSocket_fd);
}

void	IRC::Server::start(void)
{
	pollfd	server = {
		.fd			= m_Socket_fd,		// Perform I/O actions on file descriptor that refers to the server's socket.
		.events		= POLLIN,	// Only care about reading data from incoming connections.
		.revents	= 0
	};
	m_PollSockets.push_back(server);

	log("Starting Server...", true);
	if (listen(m_Socket_fd, MAX_CONNECTIONS) < 0)
		throw runtimeError(ERR_SOCK_LISTEN, "Can't listen for incoming connections because : ", true);
	log(PRINT_SUCCESS);

	log(c_LogConfig.fillLine('~'));
	log("Server is now listening @" + c_Host + ":" + c_PortStr);
	log(c_LogConfig.fillLine('~'));

	size_t	i = 0;
	while (++i != 3 && m_Running)
	// while (m_Running)
	{
		log("Waiting for incoming request...", true);
		// Set timeout to -1 to stop the poll until an incoming request has been received.
		// if (i == 2 && poll(m_PollSockets.begin().base(), m_PollSockets.size(), -1) < 0)
		if (poll(m_PollSockets.begin().base(), m_PollSockets.size(), -1) < 0)
			throw runtimeError(ERR_SOCK_POLL, "Couldn't poll for connection requests because : ", true);
		log(PRINT_SUCCESS);
		processIncomingRequests();
	}
}

void	IRC::Server::processIncomingRequests(void)
{
	int	i = 0;

	for (std::vector<pollfd>::iterator request = m_PollSockets.begin(); request != m_PollSockets.end(); request++)
	{
		std::ostringstream	ss;
		ss << "[" << ++i << "] Processing request from fd " << request->fd << " ...";
		log(ss.str(), true);

		// No request from this socket.
		if (!request->revents)
		{
			log("None!");
			continue ;
		}
			
		// Incoming request is a client connection.
		if ((request->revents & POLLIN) == POLLIN && request->fd == m_Socket_fd)
		{
			log(PRINT_SUCCESS);
			return (connectClient());
		}
		// Unknown requests type.
		log(PRINT_FAILED);
		log(c_LogConfig.fillLine('~'));
		log(PRINT_WARNING" Event type handler not yet implemented");
		log(c_LogConfig.fillLine('~'));
		return ;
	}
	throw runtimeError(ERR_SOCK_POLL, "Something went wrong when polling for incoming connections. No actual request events occurred.");
}

void	IRC::Server::connectClient(void)
{
	log("Connecting client to server...", true);

	sockaddr_in	clientSocketAddress = {
		.sin_family	= 0,
		.sin_port	= 0,
		.sin_addr	= {0},
		.sin_zero	= {0}
	};
	socklen_t	addressBufferSize = sizeof(clientSocketAddress);
	int			clientSocket_fd = accept(m_Socket_fd, (sockaddr *)&clientSocketAddress, &addressBufferSize);
	if (clientSocket_fd < 0)
		throw runtimeError(ERR_CLIENT_CONNECT, "Failed to accept client connection because : ", true);
	log(PRINT_SUCCESS);

	pollfd		clientConnection = {
		.fd			= clientSocket_fd,
		.events		= POLLIN,
		.revents	= 0
	};
	m_PollSockets.push_back(clientConnection);

	log("Collecting information from client...", true);
	char	clientHostname[NI_MAXHOST] = {0};
	if (getnameinfo((sockaddr *)&clientSocketAddress, addressBufferSize, clientHostname, NI_MAXHOST, 0, 0, NI_NUMERICSERV) < 0)
		throw runtimeError(ERR_CLIENT_CONNECT, "Failed to collect information from client because : ", true);
	log(PRINT_SUCCESS);

	Network::ClientConnection	*connection = new Network::ClientConnection(clientSocket_fd, ntohs(clientSocketAddress.sin_port), clientHostname);
	m_Clients.insert(std::make_pair(clientSocket_fd, connection));

	log(c_LogConfig.fillLine('~'));
	char	output[c_LogConfig.getLineLength()] = {0};
	sprintf(output, "Client connected from %s:%d (refer to socket_fd[%i])", connection->getHostname().c_str(), connection->getPort(), connection->getSocket());
	log(output);
	log(c_LogConfig.fillLine('~'));

}
