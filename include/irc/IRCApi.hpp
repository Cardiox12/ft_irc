/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:08:41 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 21:42:40 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRC_API_HPP
# define IRC_API_HPP

# include "MasterUsers.hpp"
# include "Channels.hpp"
# include "ICmdFactory.hpp"

namespace IRC
{
	class Api {
		MasterUsers m_users;
		Channels	m_channels;
		std::string m_password;
		ICmdFactory *m_cmd_factory;
	public:
		Api(std::string const &password);
		~Api();

		void connect(Socket *socket);
		void disconnect(Socket *socket);
		void process_request(Socket *socket, std::string const &request);
	};
}



#endif