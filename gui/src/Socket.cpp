#include <arpa/inet.h>
#include "Socket.hpp"
#include "Exception.hpp"
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>

zappy::Socket::Socket(int port, std::string hostname) : _pfds(), _clientSocket(),
    _port(port), _address()
{
    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    _address.sin_family = AF_INET;
    _address.sin_port = htons(_port);
    _address.sin_addr.s_addr = 0;
    _pfds[0].events = POLLIN;
    _pfds[0].fd = _clientSocket;
    if (inet_pton(AF_INET, hostname.c_str(), &_address.sin_addr) <= 0) {
        throw zappy::Exception("Socket: Invalid address/ Address not supported \n");
    }
    Connect();
}

zappy::Socket::~Socket()
{
    Close();
}

void zappy::Socket::Connect()
{
    if (connect(_clientSocket, reinterpret_cast<struct sockaddr *>(&_address), sizeof(_address)) < 0) {
        throw zappy::Exception("Socket: Couldn't connect to the server");
    }
}

int zappy::Socket::Poll(int timeout)
{
    return poll(_pfds, 1, timeout);
}

void zappy::Socket::Close()
{
    close(_clientSocket);
}

std::string zappy::Socket::Receive()
{
    char buffer[BUFSIZ] = {0};
    recv(_clientSocket, buffer, BUFSIZ, 0);
    std::string msg(buffer);
    std::cout << msg << std::endl;
    return msg;
}

void zappy::Socket::Send(std::string msg)
{
    send(_clientSocket, msg.c_str(), msg.length(), 0);
}

