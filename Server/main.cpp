/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:53:42 by lmells            #+#    #+#             */
/*   Updated: 2024/02/04 17:46:24 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

static inline std::string	usage(const std::string &programName)
{
	return (std::string("Startup Error! Incorrect number of arguments.\n"
						"Usage: " + programName + " [port number] [password]"));
}

static inline int	errorExit(int error_code, const std::string &message)
{
	std::cerr << message << std::endl;
	return (error_code);
}

#define SERVER_NAME 0
#define TRIM_DOT_SLASH 2

#define SERVER_PORT 1
#define SERVER_PASSWORD 2

int	main(int ac, char **av)
{
	if (ac != 3) return (errorExit(IRC::ERROR_USAGE, usage(av[SERVER_NAME])));
	try {
		IRC::Server(&av[SERVER_NAME][TRIM_DOT_SLASH], av[SERVER_PORT], av[SERVER_PASSWORD]).start();
	}
	catch (const std::exception& e) { return (errorExit(IRC::ERROR_CODE, e.what())); }
	return (0);
}
