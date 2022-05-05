/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:51:33 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:06 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDJOIN_HPP
#define CMDJOIN_HPP

#include "ACmd.hpp"

namespace IRC
{
	struct CmdJOIN : public ACmd {
		CmdJOIN(CmdCtx &ctx, std::string const &request);
		virtual ~CmdJOIN();

		virtual Actions execute();
	};
}


#endif
