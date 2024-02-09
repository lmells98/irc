/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandCentre.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:01:20 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:20:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDCENTER_HPP
# define COMMANDCENTER_HPP

# include <map>
# include <string>

// # include <Server.hpp>
# include <Dispatcher/Dispatcher.hpp>
# include <Commands/UserNickname.hpp>


// class IRC::Command::UserNickname;

namespace IRC
{
	namespace Command
	{
		# define AUTH_REQUIRED true
		# define NO_AUTH_REQUIRED false
		class UserNickname;

		// We will set the host for the command at runtime...
		static IrssiCommand	IrssiCommands[COUNT_IRSSI] = {
			{ .type = IRSSI_NICK, .name = "NICK", .command = new UserNickname(NULL, NO_AUTH_REQUIRED) }
		};
	}

	class Server;

	class CommandCentre : public Dispatcher
	{
		private:
			CommandCentre(void) : Dispatcher(NULL) {}
		
		public:
			CommandCentre(IRC::Server *hostServer);
			~CommandCentre(void);

			void	parse(IRC::Network::ClientConnection *client, const std::string &message);

	};
}

#endif
