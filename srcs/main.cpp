/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/10 09:15:42 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include "../include/Socket.hpp"
#include "../include/Network.hpp"

Socket *server = NULL;

void sig_handler(int sig) {
    (void)sig;
    std::cout << "\nShutdown server\n";
    server->sock_close();
    delete server;
}

int main()
{
    std::stringstream stream(std::ios::app);

    signal(SIGINT, sig_handler);

    try {
        server = new Socket(AF_INET, SOCK_STREAM);
    } catch (std::exception &e){
        std::cout << "Server failed" << std::endl;
    }

    server->bind("", "3490");

    while ( true ){
        try {
            server->listen(5);

            Socket *new_sock = server->accept();

            std::cout << "New connection from : " << new_sock->storage() << std::endl;

            // Receive content from peer
            new_sock->recv(stream);
            std::cout << "Received: " << stream.str() << std::endl;

            stream.str(std::string());
            // Send message to peer
            new_sock->send("pong\n\n");

            new_sock->close();
            delete new_sock;
            new_sock = NULL;
        } catch ( std::exception &e ){
            break;
        }
    }
    return EXIT_SUCCESS;
}
