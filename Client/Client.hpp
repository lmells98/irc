/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:30:00 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 20:33:19 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <arpa/inet.h>

# include <exception>
# include <map>
# include <iomanip>
# include <iostream>

# include <ClientConnection.hpp>
# include <Utils.hpp>

struct s_ErrorCodes
{
	public:
		enum e_ErrorCodes {
			NONE,
			USAGE,
			CREATE_SOCKET
		};

		s_ErrorCodes(void) {}
		~s_ErrorCodes(void) {}
};

typedef struct s_ClientStates
{
	public:
		typedef enum e_ClientStates {
			NONE = -1,
			DISCONNECTED,
			CONNECTED,
			COUNT_STATES
		}	ActiveState;
	
		s_ClientStates() {}
		~s_ClientStates() {}
}	CLI;

namespace IRC
{
	class Client : public Network::IClientConnection
	{
		private:
		//	---- Abstracted from Network::IClientConnection --------------------
			int						m_Socket_fd;
			int						m_Port;
			std::string				m_Hostname;
		//	--------------------------------------------------------------------
			const LogConfig			c_logConfig;
			const std::string		c_Username;

			bool					m_Running;

			CLI::ActiveState		m_State;

			Client(void);

		public:
			static struct s_ErrorCodes		ErrorCodes;	// Gives global access to error codes without creating the parent object.
			// static struct s_ClientStates	CLI_States;

			Client(const std::string &name, const std::string &username);
			~Client(void);

		//	---- Abstracted from Network::IClientConnection --------------------
			inline int					getSocket(void) const { return m_Socket_fd; }
			inline int					getPort(void) const { return m_Port; }
			inline std::string			getHostname(void) const { return m_Hostname; }
		//	--------------------------------------------------------------------
			void						log(const std::string &message, bool nextOutputOnSameLine = false);
			inline std::runtime_error	runtimeError(int exitCode, const std::string &message, bool printErrnoMessage = false);

			void						run(void);

			
	};
}

#endif
