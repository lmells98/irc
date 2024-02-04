/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:49:38 by lmells            #+#    #+#             */
/*   Updated: 2024/02/04 18:00:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	IRC::Server::log(const std::string &message, bool nextOutputOnSameLine = false)
{
	if (!nextOutputOnSameLine)
		std::cout << c_logConf.getPrefix() << ": " << message << std::endl;
}

IRC::Server::Server(const std::string &name, const std::string &portStr, const std::string &password) :	c_name(name),
																										c_logConf(IRC::LogConfig::initialise(name)),
																										c_portStr(portStr),
																										c_password(password),
																										c_host("127.0.0.1")
{
	log("Starting Server...");
	log(c_logConf.fillLine());

	m_running = true;
	// m_socket = openSocketConnection();

	log(c_logConf.fillLine('~'));
}

IRC::Server::~Server(void)
{ }

void	IRC::Server::start(void)
{
	IRC::ERROR_CODE = IRC::ERROR_NONE;
}
