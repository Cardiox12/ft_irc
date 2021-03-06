/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:16:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/19 23:12:17 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
#define CHANNELS_HPP

# include "Channel.hpp"
# include "Actions.hpp"
# include <vector>
# include <map>

namespace IRC
{
	class Channels {
		std::map<std::string, Channel> m_channels;
	public:
		Channels();
		~Channels();

		void	add(Channel const &channel);
		void	remove(std::string const &name);
		bool	has(std::string const &name);
		Channel	*find(std::string const &name);

		void	remove_user(User *user);
		Channel	*find_by_user(User *user);
		std::vector<Channel*> get_channels_by_user(User *user);

		Actions notify_by_user(User *user, std::string const &message);
		std::vector<Channel> get_channels();
	};
}


#endif
