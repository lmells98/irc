/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IClientConnection.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:43:49 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 10:28:28 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICLIENTCONNECTION_HPP
# define ICLIENTCONNECTION_HPP

# include <string>

namespace IRC::Network
{
	class IClientConnection
	{
		public:
			IClientConnection(void) {}
			virtual ~IClientConnection(void) {}

			virtual inline int			getSocket() const = 0;
			virtual inline int			getPort() const = 0;
			virtual inline std::string	getHostname() const = 0;

	};
}

#endif
