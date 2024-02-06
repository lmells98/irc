/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:02:04 by lmells            #+#    #+#             */
/*   Updated: 2024/02/06 10:24:19 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ClientConnection.hpp>

IRC::Network::ClientConnection::ClientConnection(const int socket_fd, const int port, const std::string &hostname) : c_socket_fd(socket_fd),
																													 c_port(port),
																													 c_hostname(hostname)
{ }

IRC::Network::ClientConnection::~ClientConnection(void)
{ }
