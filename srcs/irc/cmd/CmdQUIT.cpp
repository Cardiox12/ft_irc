/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQUIT.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:57:08 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 13:01:50 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdQUIT.hpp"
#include <iostream>

IRC::CmdQUIT::CmdQUIT(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "QUIT") { }

IRC::CmdQUIT::~CmdQUIT() { }

/**
 * QUIT
 * 
 * QUIT [<Quit message>]
 */
IRC::Actions
IRC::CmdQUIT::execute() {
	Actions actions;
	User *user = m_ctx.sender;
	
	std::cout << "CmdQUIT" << std::endl;
	// Notify all channels where sender is present
	if ( m_arguments.size() >= 2 ){
		std::string message = m_arguments[1];

		actions.push(Action::send(user, message));
	}
	actions.push(Action::disconnect(user));
	return actions;
}
