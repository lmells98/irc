/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:35:09 by lmells            #+#    #+#             */
/*   Updated: 2024/02/09 21:29:07 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

# include <Commands/Interfaces/IBaseCommand.hpp>

namespace IRC
{
	class Server;
	class ClientConnection;

	class BaseCommand : public IBaseCommand
	{
		private:
			BaseCommand(void) : c_AuthenticationRequired(false) {}

		protected:
			const bool				c_AuthenticationRequired;
			IRC::Server				*m_HostServer;

		public:
			explicit BaseCommand(IRC::Server *hostServer, bool isAuthenticationRequired = true) : c_AuthenticationRequired(isAuthenticationRequired), m_HostServer(hostServer) {}
			~BaseCommand() {}

			virtual void			execute(IRC::Network::ClientConnection *caller, std::vector<std::string> commandArgs) = 0;

			inline IRC::Server		*getHost(void) { return m_HostServer; }
			inline bool				authenticationRequired() const { return c_AuthenticationRequired; }

			inline void				setHost(IRC::Server *hostServer) { m_HostServer = hostServer; }
	};
}

#endif
