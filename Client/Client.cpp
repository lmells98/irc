/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:42:27 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 21:53:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

inline std::runtime_error	IRC::Client::runtimeError(int exitCode, const std::string &message, bool printErrnoMessage)
{
	IRC::ExitCode = exitCode;

	if (exitCode > ErrorCodes.CREATE_SOCKET)
	{
		log(PRINT_FAILED);
		log(c_logConfig.fillLine());
	}
	return (std::runtime_error(IRC::BufferErrorMessage(message, printErrnoMessage)));
}

IRC::Client::Client(const std::string &name, const std::string &username) : c_logConfig(IRC::LogConfig::initialise(name)),
																			c_Username(username)
{
	m_State = CLI::DISCONNECTED;

	m_Running = true;
}

IRC::Client::~Client()
{ }

void	IRC::Client::log(const std::string &message, bool nextOutputOnSameLine)
{
	// static bool	cursorOnSameLine;

	// std::cout << (cursorOnSameLine == false ? c_logConfig.getPrefix() + ": " : "");
	std::cout << message;
	std::cout << (nextOutputOnSameLine == true ? "\e[s" : "\n");
	std::cout.flush();
	// cursorOnSameLine = nextOutputOnSameLine;
}

void	IRC::Client::run(void)
{
	log(c_logConfig.fillLine());
	log("Hello " + c_Username + "...");
	log("Welcome to IRC Client!");
	log(c_logConfig.fillLine('~'));
	log("Commands:");
	log("/CONNECT - Connect to host with IP Address followed by the port number!");
	log("\t\tMaybe there is a password for the server... Add that on at the end :)");
	log(c_logConfig.fillLine());


	std::string	inputBuffer;
	while (m_Running)
	{
		std::cout << " > " << std::flush;
		std::getline(std::cin, inputBuffer);
		std::cin.clear();

		std::cout << "\"" << inputBuffer << "\"" << std::endl;
		inputBuffer.clear();
		m_Running = false;
	}
}
