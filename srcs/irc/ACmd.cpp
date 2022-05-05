/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:55:45 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/01 20:12:11 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACmd.hpp"

IRC::ACmd::ACmd(CmdCtx &ctx, std::string const &request, std::string const &name) :
	m_ctx(ctx),
	m_request(request),
	m_name(name),
	m_parser(request) { }

IRC::ACmd::~ACmd() { }

std::vector<std::string> 
IRC::ACmd::parse() {
	return m_parser.parse();
}

IRC::User*
IRC::ACmd::sender(){
	return m_ctx.sender;
}

IRC::Channels&
IRC::ACmd::channels(){
	return m_ctx.channels;
}

IRC::MasterUsers&
IRC::ACmd::users(){
	return m_ctx.users;
}

std::string	const&
IRC::ACmd::server_pass(){
	return m_ctx.config.server_pass;
}

std::string const&
IRC::ACmd::server_name(){
	return m_ctx.config.server_name;
}