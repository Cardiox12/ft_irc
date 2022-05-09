/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdCtx.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:33:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:22:00 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdCtx.hpp"

IRC::CmdCtx::CmdCtx(User *sender_, Channels &channels_, MasterUsers &users_, 
	std::string &password_ ) :
	sender(sender_), channels(channels_), users(users_), password(password_) { }

IRC::CmdCtx::CmdCtx(CmdCtx const &other) :
	sender(other.sender), channels(other.channels), users(other.users), password(other.password) { }

IRC::CmdCtx::~CmdCtx() { }

IRC::CmdCtx &IRC::CmdCtx::operator=(CmdCtx const &other) {
	if ( &other == this )
		return *this;
	sender = other.sender;
	channels = other.channels;
	users = other.users;
	password = other.password;
	return *this;
}
