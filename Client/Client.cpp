/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:42:27 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 13:04:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

inline std::runtime_error	IRC::Client::runtimeError(int exitCode, const std::string &message, bool printErrnoMessage)
{
	IRC::ExitCode = exitCode;
	log(PRINT_FAILED);
	log(c_logConfig.fillLine());
	return (std::runtime_error(IRC::BufferErrorMessage(message, printErrnoMessage)));
}

IRC::Client::Client(const std::string &name, const std::string &username) : c_logConfig(IRC::LogConfig::initialise(name)),
																			c_Username(username)
{
	m_Socket_fd = socket();
	if (m_Socket_fd < 0)
		throw runtimeError(ErrorCodes.CREATE_SOCKET, IRC::BufferErrorMessage("Failed to create socket for client because : ", true));

	m_Running = true;
}

IRC::Client::~Client()
{ }

void	IRC::Client::log(const std::string &message)
{
	std::cout << c_logConfig.getPrefix() << ": " << std::setw(c_logConfig.getLineLength()) << std::left << message << std::endl;
}

void	IRC::Client::run(void)
{
	
}
