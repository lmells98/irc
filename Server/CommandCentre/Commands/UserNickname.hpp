/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserNickname.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:55:52 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:03:36 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERNICKNAME_HPP
# define USERNICKNAME_HPP

// # include <Server.hpp>
# include <CommandCentre/Commands/BaseCommand.hpp>

namespace IRC
{
	namespace Command
	{
		class UserNickname : public IRC::BaseCommand
		{
			inline static std::string	NO_NAME_GIVEN(const std::string &arg)
			{
				return (std::string("[-] 431 " + arg + " : Nickname was not recieved!"));
			}

			inline static std::string	ALREADY_IN_USE(const std::string &arg)
			{
				return (std::string("[-] 433 " + arg + " : Nickname is already in use!"));
			}

			public:
				UserNickname(IRC::Server *server, bool requiresAuthentication);
				~UserNickname();

				void	execute(IRC::Network::ClientConnection *caller, std::vector<std::string> commandArgs);

		};
	}
}

#endif
