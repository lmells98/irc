/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:47:54 by lmells            #+#    #+#             */
/*   Updated: 2024/02/07 13:40:48 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

// # include <errno.h>
# include <fcntl.h>
# include <stdlib.h>

# include <arpa/inet.h>
# include <poll.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>

# include <exception>
# include <iostream>
# include <iomanip>
# include <map>
# include <string>
# include <sstream>
# include <vector>

# include <Utils.hpp>
# include <ClientConnection.hpp>

# define PRINT_FAILED "\e[38;5;9mFailed!\e[0m"
# define PRINT_SUCCESS "\e[38;5;10mSuccess!\e[0m"
# define PRINT_WARNING "\e[38;5;11mWarning!\e[0m"

# define NONE 0
# define ERR_USAGE 1
# define ERR_SOCK_CREATE 2
# define ERR_SOCK_LISTEN 3
# define ERR_SOCK_POLL 4
# define ERR_CLIENT_CONNECT 5
# define ERR_DELETE_CONNECTION 6

namespace IRC
{
	class Server
	{
		private:
			const std::string							c_Name;
			const LogConfig								c_LogConfig;
			
			const std::string							c_PortStr;
			const std::string							c_Password;
			const std::string							c_Host;
			
			bool										m_Running;
			int											m_Socket_fd;

			# define MAX_CONNECTIONS 30
			std::vector<pollfd>							m_PollSockets;

			std::map<int, Network::ClientConnection *>	m_Clients;

			Server(void): c_Name(0), c_LogConfig(LogConfig::initialise()), c_PortStr(0), c_Password(0), c_Host(0) {}
			Server(const Server &server): c_Name(server.c_Name), c_LogConfig(server.c_LogConfig), c_PortStr(server.c_PortStr), c_Password(server.c_Password), c_Host(server.c_Host) {}

			int							createSocketConnection(void);

			void						processIncomingRequests(void);
			void						connectClient(void);

		public:
			Server(const std::string &name, const std::string &portStr, const std::string &password);
			~Server(void);

			void						log(const std::string &message, bool nextOutputOnSameLine);
			void						start(void);
			
			inline std::runtime_error	runtimeError(int exitCode, const std::string &message, bool printErrnoMessage = false)
			{
				IRC::ExitCode = exitCode;
				log(PRINT_FAILED, false);
				log(c_LogConfig.fillLine(), false);
				return (std::runtime_error(IRC::BufferErrorMessage(message, printErrnoMessage)));
			}
	};
}

#endif
