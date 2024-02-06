/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:40:33 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 12:48:14 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

static inline std::string	usage(const std::string &programName)
{
	return ("Startup Error! Incorrect number of arguments.\n"
			"Usage: " + programName + " [Username]");
}

#define CLIENT_PROGNAME 0
#define CLIENT_USER 1
#define TRIM_DOT_SLASH 2

int	main(int ac, char **av)
{
	if (ac != 2)
		return (IRC::ErrorExit(IRC::Client::ErrorCodes.USAGE, usage(av[CLIENT_PROGNAME])));

	try { IRC::Client(&av[CLIENT_PROGNAME][TRIM_DOT_SLASH], av[CLIENT_USER]).run(); }
	catch (std::exception &e) { return (IRC::ErrorExit(IRC::ExitCode, e.what())); }
	return (IRC::ExitCode);
}
