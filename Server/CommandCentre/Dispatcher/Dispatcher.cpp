/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dispatcher.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:01:23 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:11:40 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <CommandCentre/CommandCentre.hpp>

IRC::Dispatcher::Dispatcher(IRC::Server *server) : m_HostServer(server)
{
	m_Commands = initialiseCommands(server);
}

IRC::Dispatcher::~Dispatcher()
{
	Commands::iterator	start;
	Commands::iterator	end = m_Commands.end();
	
	for (start = m_Commands.begin(); start != end; start++)
	{
		IRC::BaseCommand	*command = start->second;
		
		m_Commands.erase(start->first);
		delete command;
	}
}

IRC::Dispatcher::Commands	IRC::Dispatcher::initialiseCommands(IRC::Server *server)
{
	Commands	map;

	for (size_t i = 0; i < COUNT_IRSSI; i++)
	{
		IRC::IrssiCommand	*irssi = &IRC::Command::IrssiCommands[i];

		irssi->command->setHost(server);
		map.insert(std::make_pair(irssi->name, irssi->command));
	}
	return (map);
}
