/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/20 11:50:53 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include "irc/Mode.hpp"
#include <iostream>

/**
 * @brief Construct a new IRC::CmdMODE object
 *
 * @param ctx the context of command builds (sender, channels etc...)
 * @param request the request of the command (needed to parse this)
 */

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string const &request):
	ACmd(ctx, request, "MODE"),
	m_target(""),
	m_authorized_modes(IRC_USER_MODE_STRING),
	m_parser()
{
	if (m_arguments.size() > 1)
		m_target = m_arguments[1];

	std::string parameter_modes;
	if (!m_target.empty() && Channel::is_valid_name(m_target))
	{
		m_authorized_modes = IRC_CHANNEL_MODE_STRING;
		parameter_modes = IRC_CHANNEL_PARAMETERS_MODE_STRING;
	}
	else
		parameter_modes = IRC_USER_PARAMETERS_MODE_STRING;

	if (m_arguments.size() > 2)
	{
		std::vector<std::string> mode_arguments;
		if (m_arguments.size() > 3)
			mode_arguments.assign(m_arguments.begin() + 3, m_arguments.end());

		m_parser = CmdMODEParse(
			m_arguments[2],
			mode_arguments,
			m_authorized_modes,
			parameter_modes
		);
	}
}

IRC::CmdMODE::CmdMODE(CmdMODE const &copy):
		ACmd(copy),
		m_parser(copy.m_parser)
{
}

IRC::CmdMODE::~CmdMODE()
{
}

IRC::Actions IRC::CmdMODE::execute() {
	std::cout << "Commmand MODE:";

	std::vector<std::string> m_arguments = this->parse();
	ReplyBuilder reply(this->server_name(), this->sender());

	if (m_target.empty())
	{
		return Actions::unique_send(
			this->sender(), reply.error_need_more_params(m_name)
		);
	}

	if (Channel::is_channel_name(m_target))
		return this->execute_channel_mode_(reply);

	std::cout << std::endl;
	return this->execute_user_mode_(reply);
}

IRC::Actions IRC::CmdMODE::execute_channel_mode_(
	ReplyBuilder &reply
) {
	User *sender = this->sender();
	std::string channel_name = m_target;
	Channel *channel = this->channels().find(channel_name);

	if (!channel)
		return Actions::unique_send(
			sender, reply.error_no_such_channel(channel_name)
		);

	if (channel->find(sender) == channel->end())
		return Actions::unique_send(
			sender, reply.error_not_on_channel(channel_name)
		);

	if (!channel->is_operator_user(sender))
		return Actions::unique_send(
			sender, reply.error_chan_o_privs_needed(channel_name)
		);

	std::map<Mode, bool, CmdMODEParse::ModeComp> modes;
	try
	{
		modes = m_parser.parse();
	}
	catch (CmdMODEParse::ModeUnknownException const &e)
	{
		return Actions::unique_send(
			sender, reply.error_unknown_mode(e.mode())
		);
	}
	catch (CmdMODEParse::ArgumentMissingException const &)
	{
		return Actions::unique_idle();
	}

	std::map<Mode, bool, CmdMODEParse::ModeComp>::const_iterator first;
	first = modes.begin();
	std::map<Mode, bool, CmdMODEParse::ModeComp>::const_iterator last;
	last = modes.end();
	for (; first != last; ++first)
	{
		if (first->second)
		{
			if (!first->first.parameter.empty())
			{
				; // TODO: handle parameter mode
			}
			else
			{
				channel->set_mode(first->first.value);
			}
		}
		else
		{
			if (!first->first.parameter.empty())
			{
				; // TODO: handle parameter mode
			}
			else
			{
				channel->unset_mode(first->first.value);
			}
		}
	}


	return channel->notify(reply.reply_channel_mode_is(*channel));
}

/**
 * @brief Change users modes in IRC
 * Checks:
 *	if user targeted is the same that made the command,
 *	if user set its mode: if no just display its currently modes
 *	if modes are valids
 *
 * then change its modes if necessary and display its new modes
 *
 * @param reply the reply built previously
 * @return IRC::Actions actions sent to the server
 */

IRC::Actions IRC::CmdMODE::execute_user_mode_(ReplyBuilder &reply)
{
	User *sender = this->sender();

	std::cout << "Argument size " << m_arguments.size() << std::endl;

	if (sender->get_nickname() != m_target)
		return Actions::unique_send(
			sender, reply.error_users_dont_match()
		);

	if (m_arguments.size() == 2)
	{
		return Actions::unique_send(
			sender, reply.reply_u_mode_is(
				sender->get_nickname(), sender->get_mode()
			)
		);
	}

	std::map<Mode, bool, CmdMODEParse::ModeComp> modes;
	try
	{
 		modes = m_parser.parse();
	}
	catch (CmdMODEParse::ModeUnknownException const &)
	{
		return Actions::unique_send(
			sender, reply.error_u_mode_unknown_flag()
		);
	}
	catch (CmdMODEParse::ArgumentMissingException const &)
	{
		return Actions::unique_idle();
	}

	std::map<Mode, bool, CmdMODEParse::ModeComp>::iterator first;
	first = modes.begin();
	std::map<Mode, bool, CmdMODEParse::ModeComp>::iterator last;
	last = modes.end();

	for (; first != last; ++first)
	{
		if (first->second)
			sender->set_mode(first->first.value);
		else
			sender->unset_mode(first->first.value);
	}

	return Actions::unique_send(
		sender, reply.reply_u_mode_is(
			sender->get_nickname(), sender->get_mode()
		)
	);
}
