#ifndef NETCHECK_H
#define NETCHECK_H


#ifndef _WIN32
// BSD socket includes
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <fcntl.h>
#  include <sys/select.h>
#else
#  define WIN32_LEAN_AND_MEAN
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  pragma comment(lib, "wsock32.lib")
#endif

// Timeout
#include <fcntl.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
//#include <string.h>     // strerror



/**
 * Check if possible to connect to ipaddr:port.
 *
 * @note Only supports IPv4 addresses.
 *
 * @param ipaddr ip address to connect to. e.g., "127.0.0.1"
 * @param port port number
 * @param timeout seconds to wait for connection; return false on timeout.
 *        If timeout is smaller than one, the default TCP timeout is used.
 */

bool is_alive (const char *ipaddr, unsigned short port, int timeout = -1)
{
    // Fuck Windows :)
#ifdef _WIN32
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
    printf("WSAStartup failed: %d\n", iResult);
    return false;
    }
#endif
    assert (port>0 and port<0xffff);

    sockaddr_in soaddr;
    soaddr.sin_family = AF_INET;
    soaddr.sin_port = htons (port);
    soaddr.sin_addr.s_addr = inet_addr (ipaddr);
    assert (soaddr.sin_addr.s_addr != -1);

    int fd = socket (AF_INET, SOCK_STREAM, 0);
    assert (fd != -1);

    if (timeout > 0)
    {
#ifndef _WIN32
        int rv = fcntl (fd, F_SETFL, O_NONBLOCK);
        assert (rv == 0);
#else
    int rv = ioctlsocket (fd, FIONBIO, NULL);
        assert (rv == 0);
#endif
    }

    int rv = connect (fd, (sockaddr*) &soaddr, sizeof(soaddr));
    if (rv < 0)
    {
        switch (errno) {
        case ECONNREFUSED:
        case ENETUNREACH:
        case ETIMEDOUT:
            // @note error message can be found in: strerror(errno)
            return false;
        case EINPROGRESS:
            // We are in non-blocking mode. Must wait for completion.
            {
                struct timeval tv = { timeout, 0 };
                fd_set fdset;
                FD_ZERO (&fdset);
                FD_SET (fd, &fdset);
                rv = select (fd+1, NULL, &fdset, NULL, &tv);
                assert (rv >= 0);
                if (rv == 0) return false;  // timeout reached
                // Determine whether connect() completed successfully
                int soerr;
                socklen_t soerrlen = sizeof(soerr);
                rv = getsockopt (fd, SOL_SOCKET, SO_ERROR, (char*)&soerr, &soerrlen);
                assert (rv == 0);
                if (soerr == 0)
                    return true;    // connected
                if (soerr==ECONNREFUSED or soerr==ENETUNREACH)
                    return false;   // can't connect
                goto error_exit;
            }
        default:
            goto error_exit;
        }
    }

    return true;

error_exit:
    // Other network error. Should abort() or log and return false
    //abort();
    return false;
}


#endif // NETCHECK_H
