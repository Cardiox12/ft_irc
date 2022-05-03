/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/02 20:11:08 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

# include <string>
# include "Role.hpp"
# include "Mode.hpp"
# include "ISubscriber.hpp"
# include "Socket.hpp"

namespace IRC
{
	class User : public ISubscriber {
		std::string m_username;
		std::string m_nickname;
		int			m_mode;
		Socket		*m_socket;
	public:
		User();
		User(std::string const &pseudo, std::string const &nick, 
			int mode, Socket *socket);
		User(Socket *socket);
		User(User const &other);
		User &operator=(User const &other);
		virtual ~User();

		void set_username(std::string const &pseudo);
		void set_nickname(std::string const &nick);
		void set_mode(int mode);
		void set_socket(Socket *socket);

		void unset_mode(int mode);

		bool role_isset(int role);
		bool mode_isset(int mode);

		bool connected() const;

		std::string const	&get_username() const;
		std::string const	&get_nick() const;
		int					get_mode() const;
		Socket				*get_socket();


		virtual void update(std::string const &msg);

		/**
		 * Pseudo predicate
		 * 
		 * Check if pseudo is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class PseudoSelector {
			std::string m_pseudo;
		public:
			PseudoSelector(std::string const &pseudo);
			bool operator()(User *user);
		};

		/**
		 * Nick predicate
		 * 
		 * Check if nickname is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class NickSelector {
			std::string m_nickname;
		public:
			NickSelector(std::string const &nickname);
			bool operator()(User *user);
		};

		/**
		 * Mode predicate
		 * 
		 * Check if mode is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class ModeSelector {
			int m_mode;
		public:
			ModeSelector(int mode);
			bool operator()(User *user);
		};

		/**
		 * Socket predicate
		 * 
		 * Check if socket is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class SocketSelector {
			Socket *m_socket;
		public:
			SocketSelector(Socket *socket);
			bool operator()(User *user);
		};
	};
}


#endif
