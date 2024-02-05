/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:49:38 by lmells            #+#    #+#             */
/*   Updated: 2024/02/05 12:03:26 by lmells           ###   ########.fr       */
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
	m_socket = openSocketConnection();
}

IRC::Server::~Server(void)
{ }

int	IRC::Server::openSocketConnection(void)
{
	log("Opening socket connection...", true);
	int	servSocket_fd = 1;//socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket_fd < 0)
		throw runtimeError(ERR_SOCK_OPEN, "Could't open socket connection because : ", true);
	log(PRINT_SUCCESS);

	return (servSocket_fd);
}

void	IRC::Server::start(void)
{
	log("Starting Server...");
}
