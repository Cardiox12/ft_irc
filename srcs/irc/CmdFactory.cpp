/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:07:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:31:05 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdFactory.hpp"

// Use some macro shit to automatically create proto and definitions for commands ?

IRC::CmdFactory::CmdFactory() : ICmdFactory(), m_callbacks() 
{
	m_callbacks.insert(std::make_pair("PASS", &CmdFactory::create_pass_cmd));
	m_callbacks.insert(std::make_pair("PONG", &CmdFactory::create_pong_cmd));
}

IRC::CmdFactory::~CmdFactory() { }

IRC::ACmd*
IRC::CmdFactory::create_cmd(CmdCtx &ctx, std::string const &request) {
	std::map<std::string, callback_t>::iterator found;
	std::string command = ft::split_one(request)[0];

	if ( (found = m_callbacks.find(command)) != m_callbacks.end() ){
		return (this->*found->second)(ctx, request);
	}
	return NULL;
}

IRC::ACmd*
IRC::CmdFactory::create_pass_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPASS(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_pong_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPONG(ctx, request);
}