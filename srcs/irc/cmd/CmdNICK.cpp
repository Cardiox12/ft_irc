/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:18:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/15 11:25:04 by lperson-         ###   ########.fr       */
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
	ReplyBuilder				reply(this->server_name(), user);
	Actions						actions;
	
	std::cout << "CmdNICK" << std::endl;
	// Check if role not onboard
	if ( user->pass_accepted() || user->connected() ){
		std::cout << "HELLO there 0" << std::endl;
		if ( m_arguments.size() == 1 ){
			std::cout << "> NICK not enough parameters" << std::endl;
			return Actions::unique_send(user, reply.error_no_nickname_given());
		}
		if ( m_arguments.size() > Expected_args(2) ){
			// Do we have to send it ? Not indicated in RFC
			return Actions::unique_send(user, reply.error_need_more_params(m_name));
		}
		std::string nickname = m_arguments[1];
		std::cout << nickname << std::endl;

		// Check nickname validity
		if ( !is_valid_nick(nickname) ){
			std::cout << "> NICK erroneous nickname" << std::endl;
			return Actions::unique_send(user, reply.error_erroneus_nickname(nickname));
		}

		// Check if nickname collide
		std::vector<User*> collided_users = this->users().select(User::NickSelector(nickname));
		if ( !collided_users.empty() ){
			if ( collided_users.front() == user ){
				// User changing his nickname with the same nickname
				return Actions::unique_send(user, reply.error_nickname_in_use(nickname));
			} else {
				// Nickname collision, disconnect all users
				std::cout << "> NICK COLLISION!" << std::endl;
				collided_users.push_back(user);

				// Remove the user from all channels
				channels().remove_user(collided_users.front());

				// Send error and disconnect all users
				return actions
					.push(Action::send(user, reply.error_nickname_collision(nickname)))
					.push(
						Action::sendall(collided_users,reply.reply_cmd_kill(
							nickname, "Nick collision"
						))
					)
					.push(Action::disconnectall(collided_users));
			}
		} 
		// No Collision occurred, change nickname
		std::cout << "> NICK SET TO " << nickname << std::endl;
		user->set_nickname(nickname);
		user->set_mode(MODE_NICK_);
		
		if ( user->connection_complete() ){
			std::cout << "Connection completed!" << std::endl;
			user->unset_mode(MODE_RESTRICTED_);
			return reply.connection_complete_replies(user, m_ctx.config);
		}
	}
	return Actions::unique_idle();
}