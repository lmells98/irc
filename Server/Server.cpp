/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:49:38 by lmells            #+#    #+#             */
/*   Updated: 2024/02/05 14:29:24 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	IRC::Server::log(const std::string &message, bool nextOutputOnSameLine = false)
{
	static bool	cursorOnSameLine;

	std::ios originalOutputFormat(NULL);
	originalOutputFormat.copyfmt(std::cout);

	if (nextOutputOnSameLine && !cursorOnSameLine)
		std::cout << c_logConf.getPrefix() << ": " << std::setw(c_logConf.getActionFieldWidth()) << std::left << message << "\e[s";

	else if (cursorOnSameLine && !nextOutputOnSameLine)
		std::cout << "| " << std::setw(c_logConf.getResultFieldWidth()) << std::left << message << std::endl;

	else
		std::cout << c_logConf.getPrefix() << ": " << std::left << std::setw(c_logConf.getLineLength()) << message << std::endl;

	std::cout.flush();
	cursorOnSameLine = nextOutputOnSameLine;
	std::cout.copyfmt(originalOutputFormat);
}

IRC::Server::Server(const std::string &name, const std::string &portStr, const std::string &password) :	c_name(name),
																										c_logConf(IRC::LogConfig::initialise(name)),
																										c_portStr(portStr),
																										c_password(password),
																										c_host("127.0.0.1")
{
	log(c_logConf.fillLine());
	log("");
	log(centerStringInTextField(c_logConf.getLineLength(), "{ FT_IRC SERVER }", ' '));
	log("");
	log(c_logConf.fillLine());
	log(centerStringInTextField(c_logConf.getActionFieldWidth(), "Performing Action", ' '), true);
	log(centerStringInTextField(c_logConf.getResultFieldWidth(), "Result", ' '));
	log(c_logConf.fillLine());

	m_running = true;
	m_socket = createSocketConnection();
}

IRC::Server::~Server(void)
{ }

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

	// This will block the poll until an incoming request has been recieved, then we will process the request.
	log("Setting socket to \"non-blocking\" mode...", true);
	if (fcntl(servSocket_fd, F_SETFL, O_NONBLOCK) < 0)
		throw runtimeError(ERR_SOCK_CREATE, "Couldn't set socket to \"non-blocking\" mode because : ", true);
	log(PRINT_SUCCESS);

	// Bind the socket's file descriptor to the socket address for I/O communications over the connection.
	log("Binding socket to IP address on port " + c_portStr + "...", true);
	struct sockaddr_in	serverSocketAddress = {
		.sin_family = AF_INET,	// AF_INET - (Address Family) Internet IPv4 Addresses.
		.sin_port 	= htons(atoi(c_portStr.c_str())),	// Convert from host machine endian to network protocol endian.
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
	log("Starting Server...");
}
