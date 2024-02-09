/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IBaseCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:10:26 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:32:50 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IBASECOMMAND_HPP
# define IBASECOMMAND_HPP

# include <string>
# include <vector>

# include <ClientConnection.hpp>

namespace IRC
{
	class Server;

	class IBaseCommand
	{
		public:
			IBaseCommand(void) {}
			virtual ~IBaseCommand() {}

			virtual IRC::Server			*getHost(void) = 0;
			virtual bool				authenticationRequired(void) const = 0;
			virtual void				execute(IRC::Network::ClientConnection *caller, std::vector<std::string> commandArgs) = 0;

	};
}

#endif
