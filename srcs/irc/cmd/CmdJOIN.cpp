/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:53:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 12:49:32 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdJOIN.hpp"
#include "NumericReplies.hpp"
#include <iostream>

IRC::CmdJOIN::CmdJOIN(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "JOIN") { }

IRC::CmdJOIN::~CmdJOIN() { }

IRC::Actions
IRC::CmdJOIN::execute() {
	User *user = m_ctx.sender;
	Channels &channels = m_ctx.channels;
	std::vector<std::string> args = this->parse();
	ReplyBuilder reply(this->server_name(), this->sender());

	std::cout << "CmdJOIN: " << std::endl;
	// Not enough arguments
	if ( args.size() == 1 || args.size() > Expected_args(2) ){
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	}
	std::vector<std::string> args_chan = ft::split(args[1], ",");
	std::vector<std::string> args_keys;

	if ( args.size() == Expected_args(2) ){
		args_keys = ft::split(args[2], ",");
	}
	Actions actions;
	std::vector<std::string>::iterator chan_it = args_chan.begin();
	std::vector<std::string>::iterator keys_it = args_keys.begin();

	while ( chan_it != args_chan.end() ){
		std::string name = *chan_it;
		std::string key;

		if ( keys_it != args_keys.end() ){
			key = *keys_it;
			++keys_it;
		}

		if ( Channel::is_valid_name(name) ){
			Channel *channel = channels.find(name);

			if ( channel != NULL ) {
				if ( channel->is_banned(user) )
					return Actions::unique_send(user, reply.error_banned_from_channel(name));
				if ( channel->is_private() && !channel->equal_key(key) )
					return Actions::unique_send(user, reply.error_bad_channel_key(name));
				if ( channel->is_invite() && !channel->is_invited(user) )
					return Actions::unique_send(user, reply.error_invite_only_channel(name));
				channel->subscribe(user);

				this->channel_joined_reply(reply, actions, *channel);
				std::cout << "Join channel: " << name << std::endl;
			} else {
				// Create channel
				Channel new_channel(name, user);
				
				std::cout << "Created channel: " << name << std::endl;
				channels.add(new_channel);
				new_channel.subscribe(user);
				this->channel_created_reply(reply, actions, new_channel);
			}
		} else {
			return Actions::unique_send(user, reply.error_no_such_channel(name));
		}
		++chan_it;
	}
	return actions;
}

void
IRC::CmdJOIN::channel_created_reply(ReplyBuilder &reply, Actions &actions, Channel &channel){
	std::string name = channel.get_name();
	
	// JOIN response
	actions.push(Action::send(this->sender(), reply.reply_join(channel.get_name())));
	// RPL_NAMEREPLY
	actions.push(Action::send(this->sender(), reply.reply_name_reply(channel)));
	// RPL_ENDOFNAMES
	actions.push(Action::send(this->sender(), reply.reply_end_of_names(name)));
}

void
IRC::CmdJOIN::channel_joined_reply(ReplyBuilder &reply, Actions &actions, Channel &channel){
	std::string name = channel.get_name();
	
	// JOIN response
	actions.push(Action::send(this->sender(), reply.reply_join(channel.get_name())));
	// RPL_NAMEREPLY
	actions.push(Action::send(this->sender(), reply.reply_name_reply(channel)));
	// RPL_ENDOFNAMES
	actions.push(Action::send(this->sender(), reply.reply_end_of_names(name)));
	// RPL_TOPIC
	actions.push(Action::send(this->sender(), reply.reply_topic(name, channel.get_topic())));
}