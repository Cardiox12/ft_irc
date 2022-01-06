/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AddressInfo.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:21:25 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/03 14:58:24 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDRESS_INFO_HPP

# define ADDRESS_INFO_HPP

# include "IPAddress.hpp"

class AddressInfo
{
public:
    int         m_flags;

    AddressInfo();
    AddressInfo(sa_family_t family, int sockType, int protocol, int flags);
    AddressInfo(
        char const *ipAddress, char const *service,
        AddressInfo const &hint = AddressInfo(0, 0, 0, 0)
    );
    AddressInfo(AddressInfo const &copy);
    ~AddressInfo();

    int getSockType() const;
    int getProtocol() const;
    AIPAddress const *getIPAddress() const;
    sa_family_t getIPFamily() const;

    AddressInfo &operator=(AddressInfo const &rhs);

    class GetAddressInfoException : public std::exception
    {
    public:
        GetAddressInfoException(int errcode);
        const char *what() const throw();

    private:
        int _errcode;
    };

    class NoAddressInfoException : public std::exception
    {
    public:
        const char *what() const throw();
    };

private:
    AIPAddress  *_ipAddress;
    sa_family_t _ipFamily;
    int         _sockType;
    int         _protocol;
};

#endif