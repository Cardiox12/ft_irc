/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:54:08 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 11:17:32 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_HPP

# define CMD_MODE_HPP

# include "irc/ACmd.hpp"
# include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

namespace IRC
{
	class CmdMODE : public ACmd
	{
	public:
		explicit CmdMODE(CmdCtx &ctx, std::string const &request);
		CmdMODE(CmdMODE const &copy);
		virtual ~CmdMODE();
	
		virtual Actions execute();

		CmdMODE &operator=(CmdMODE const &rhs);

	private:
		std::string		m_target;
		std::string		m_authorized_modes;
		CmdMODEParse	m_parser;

		// Channel modes utils
		Actions execute_channel_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);

		// User mode utils
		Actions execute_user_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);
		void add_mode_list_to_user_(
			User *target, std::string const &mode_list
		);
		void delete_mode_list_to_user_(
			User *target, std::string const &mode_list
		);
		bool is_mode_users_valid_(std::vector<std::string> const &mode_lists);


		// Utils for chan and user modes
		std::vector<std::string> parse_mode_string_(
			std::string const &mode_string
		) const;
		int char_to_mode_(char c);
	};
}

#endif
