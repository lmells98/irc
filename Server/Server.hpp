/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:47:54 by lmells            #+#    #+#             */
/*   Updated: 2024/02/05 12:02:37 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <errno.h>
# include <sys/socket.h>

# include <exception>
# include <iostream>
# include <iomanip>
# include <string>

# include <Utils.hpp>

# define PRINT_FAILED "\e[1;91mFailed!\e[0m"
# define PRINT_SUCCESS "\e[1;92mSuccess!\e[0m"

# define NONE 0
# define ERR_USAGE 2
# define ERR_SOCK_OPEN 2

namespace IRC
{
	class Server
	{
		private:
			const std::string			c_name;
			const LogConfig				c_logConf;
			
			const std::string			c_portStr;
			const std::string			c_password;
			const std::string			c_host;
			
			bool						m_running;
			int							m_socket;

			Server(void): c_name(0), c_logConf(LogConfig::initialise()), c_portStr(0), c_password(0), c_host(0) {}
			Server(const Server &server): c_name(server.c_name), c_logConf(server.c_logConf), c_portStr(server.c_portStr), c_password(server.c_password), c_host(server.c_host) {}

			int							openSocketConnection(void);

		public:
			Server(const std::string &name, const std::string &portStr, const std::string &password);
			~Server(void);

			void						log(const std::string &message, bool nextOutputOnSameLine);
			void						start(void);
			
			inline std::runtime_error	runtimeError(int exitCode, const std::string &message, bool printErrnoMessage = false)
			{
				log(PRINT_FAILED, false);
				log(c_logConf.fillLine(), false);
				return (IRC::RuntimeError(exitCode, message, printErrnoMessage));
			}
	};
}

#endif
