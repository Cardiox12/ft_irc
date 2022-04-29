/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:42:07 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/30 00:44:03 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACMD_HPP
#define ACMD_HPP

# include "CmdCtx.hpp"
# include "Action.hpp"
# include "Actions.hpp"
# include "Replies.hpp"
# include "Parse.hpp"
# include "CmdParser.hpp"

# define SERVER_NAME "ft_irc.com"

namespace IRC
{
	class ACmd {
	protected:
		CmdCtx		&m_ctx;
		std::string m_request;
		std::string m_name;
	public:
		ACmd(CmdCtx &ctx, std::string const &request, std::string const &name);
		virtual ~ACmd();
		
		virtual Actions execute() = 0;
		virtual std::vector<std::string> get_arguments() const;

		User		*sender();
		Channels	&channels();
		MasterUsers	&users();
		std::string	const &password();
	};
}


#endif
