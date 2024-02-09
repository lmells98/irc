/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dispatcher.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:16:50 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:31:34 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCHER_HPP
# define DISPATCHER_HPP

# include <CommandCentre/Commands/BaseCommand.hpp>

enum e_IrssiCommands
{
	IRSSI_NICK,
	// IRSSI_USER,
	COUNT_IRSSI
};

namespace IRC
{
	class BaseCommand;

	typedef struct s_Command
	{
		enum e_IrssiCommands	type;
		std::string				name;
		BaseCommand		*command;
	}	IrssiCommand;

	class Dispatcher
	{
		typedef std::map<std::string, BaseCommand *>	Commands;

		private:
			Commands	initialiseCommands(IRC::Server *server);

		protected:
			IRC::Server	*m_HostServer;
			Commands	m_Commands;

		public:
			Dispatcher(IRC::Server *server);
			~Dispatcher();
	
	};
}

#endif
