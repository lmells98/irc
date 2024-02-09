/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandCentre.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:38:05 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:20:25 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CommandCentre.hpp>
#include <Server.hpp>

IRC::CommandCentre::CommandCentre(IRC::Server *hostServer) : Dispatcher(hostServer) { }

IRC::CommandCentre::~CommandCentre(void) { }

void	IRC::CommandCentre::parse(IRC::Network::ClientConnection *client, const std::string &message)
{
	(void)client;
	(void)message;

	m_HostServer->log("Parsing client message...", true);
	m_HostServer->log(PRINT_FAILED, false);
}
