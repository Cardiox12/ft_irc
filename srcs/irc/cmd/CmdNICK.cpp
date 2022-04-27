/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:18:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 03:32:09 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNICK.hpp"
#include <iostream>

IRC::CmdNICK::CmdNICK(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "NICK") { }

IRC::CmdNICK::~CmdNICK() { }

/**
 * NICK
 * 
 * NICK <nickname>
 */
IRC::Actions
IRC::CmdNICK::execute() {
	User						*user = this->sender();
	std::vector<std::string>	args = this->get_arguments();
	ReplyBuilder				reply(SERVER_NAME, user);
	Actions						actions;
	
	std::cout << "CmdNICK" << std::endl;
	// Check if role not onboard
	if ( !user->mode_isset(MODE_ONBOARD) ){
		if ( args.empty() ){
			std::cout << "> NICK not enough parameters" << std::endl;
			return Actions::unique_send(user, reply.error_no_nickname_given());
		}
		if ( args.size() > 2 ){
			// Do we have to send it ? Not indicated in RFC
			return Actions::unique_send(user, reply.error_need_more_params(m_name));
		}
		std::string nickname = args[0];

		// Check nickname validity
		if ( !is_valid_nick(nickname) ){
			std::cout << "> NICK erroneous nickname" << std::endl;
			return Actions::unique_send(user, reply.error_erroneus_nickname(nickname));
		}

		// Check if nickname collide
		std::vector<User*> collided_users = this->users().select(User::NickSelector(nickname));
		if ( !collided_users.empty() ){
			if ( collided_users.front() == user ){
				// User changing nickname
				std::cout << "> NICK CHANGING" << std::endl;
				return Actions::unique_send(user, reply.error_nickname_in_use(nickname));
			} else {
				// Nickname collision, disconnect all users
				std::cout << "> NICK COLLISION!" << std::endl;
				collided_users.push_back(user);

				// Remove the user from all channels
				channels().remove_user(collided_users.front());

				// Send error and disconnect all users
				actions.push(Action::send(user, reply.error_nickname_collision(nickname)));
				actions.push(Action::disconnectall(collided_users));
				return actions;
			}
		} else {
			std::cout << "> NICK SET TO " << nickname << std::endl;
			user->set_nick(nickname);
		}
	}
	return Actions::unique_idle();
}