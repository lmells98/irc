/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserNickname.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:58:59 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:30:46 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <CommandCentre/Commands/UserNickname.hpp>

IRC::Command::UserNickname::UserNickname(IRC::Server *server, bool requiresAuthentication) : BaseCommand(server, requiresAuthentication) { }

IRC::Command::UserNickname::~UserNickname() { }

// Execute "NICK" command - Set/Modify a client user's nickname.
// 
// ~~ Command syntax from Irssi client ~~
// NICK " nickname"
void	IRC::Command::UserNickname::execute(IRC::Network::ClientConnection *caller, std::vector<std::string> commandArgs)
{
	// No nickname to set yet.
	if (commandArgs.empty() || commandArgs[0].empty()) return (caller->sendReplyToClient(UserNickname::NO_NAME_GIVEN(caller->getNickname())));

	std::string	nickname = commandArgs[0];
	// Username already exists.
	if (m_HostServer->getClient(nickname)) return (caller->sendReplyToClient(UserNickname::ALREADY_IN_USE(caller->getNickname())));

	caller->setNickname(nickname);
	m_HostServer->welcome(caller);
}
