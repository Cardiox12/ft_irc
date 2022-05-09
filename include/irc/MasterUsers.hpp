/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterUsers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:06:22 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MASTERUSERS_HPP
#define FT_MASTERUSERS_HPP

# include <map>
# include "User.hpp"

namespace IRC
{
	/**
	 * MasterUsers
	 * 
	 * 
	 * Create and manage user creation that will be passed to other objects
	 * as a procuration.
	 * MasterUsers manage the liftetime of a user, from the creation to
	 * the deletion.
	 * User objects will be passed as a reference to other objects.
	 */
	class MasterUsers {
		std::map<int, User*> m_users;
	public:
		MasterUsers();
		MasterUsers(MasterUsers const &copy);
		~MasterUsers();

		User *create(Socket *socket);
		void remove(Socket *socket);
		User *find(Socket *socket);

		MasterUsers &operator=(MasterUsers const &rhs);
	};
}


#endif
