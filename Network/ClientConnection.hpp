/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:54:15 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 10:21:01 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

# include <Interfaces/IClientConnection.hpp>

# include <string>

namespace IRC::Network
{
	class ClientConnection : public IClientConnection
	{
		private:
			const int					c_socket_fd;
			const int					c_port;
			const std::string			c_hostname;
			
			ClientConnection(void);
			
		public:
			ClientConnection(const int fd, const int port, const std::string &hostname);
			~ClientConnection();

			inline int			getSocket(void) const { return c_socket_fd; }
			inline int			getPort(void) const { return c_port; }
			inline std::string	getHostname(void) const { return c_hostname; }

	};
		
}

#endif
