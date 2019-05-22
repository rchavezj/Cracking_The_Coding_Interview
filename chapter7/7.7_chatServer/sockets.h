// $Id: sockets.h,v 1.2 2016-05-09 16:01:56-07 - - $

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//
// class base_socket:
// mostly protected and not used by applications
//

class base_socket {
   private:
      static constexpr size_t MAXRECV = 0xFFFF;
      static constexpr int CLOSED_FD = -1;
      int socket_fd {CLOSED_FD};
      sockaddr_in socket_addr;
   protected:
      base_socket(); // only derived classes may construct
      base_socket (const base_socket&) = delete; // prevent copying
      base_socket& operator= (const base_socket&) = delete;
      ~base_socket();
      // server_socket initialization
      void create();
      void bind (const in_port_t port);
      void listen() const;
      void accept (base_socket&) const;
      // client_socket initialization
      void connect (const string host, const in_port_t port);
      // accepted_socket initialization
      void set_socket_fd (int fd);
   public:
      void close();
      ssize_t send (const void* buffer, size_t bufsize);
      ssize_t recv (void* buffer, size_t bufsize);
      void set_non_blocking (const bool);
      friend string to_string (const base_socket& sock);
};


//
// class accepted_socket
// used by server when a client connects
//

class accepted_socket: public base_socket {
   public:
      accepted_socket() {}
      accepted_socket(int fd) { set_socket_fd (fd); }
};

//
// class client_socket
// used by client application to connect to server
//

class client_socket: public base_socket {
   public: 
      client_socket (string host, in_port_t port);
};

//
// class server_socket
// single use class by server application
//

class server_socket: public base_socket {
   public:
      server_socket (in_port_t port);
      void accept (accepted_socket& sock) {
         base_socket::accept (sock);
      }
};


//
// class socket_error
// base class for throwing socket errors
//

class socket_error: public runtime_error {
   public:
      explicit socket_error (const string& what): runtime_error(what){}
};

//
// class socket_sys_error
// subclass to record status of extern int errno variable
//

class socket_sys_error: public socket_error {
   public:
      int sys_errno;
      explicit socket_sys_error (const string& what):
               socket_error(what + ": " + strerror (errno)),
               sys_errno(errno) {}
};

//
// class socket_h_error
// subclass to record status of extern int h_errno variable
//

class socket_h_error: public socket_error {
   public:
      int host_errno;
      explicit socket_h_error (const string& what):
               socket_error(what + ": " + hstrerror (h_errno)),
               host_errno(h_errno) {}
};


//
// class hostinfo
// information about a host given hostname or IPv4 address
//

class hostinfo {
   public:
      const string hostname;
      const vector<string> aliases;
      const vector<in_addr> addresses;
      hostinfo (); // localhost
      hostinfo (hostent*);
      hostinfo (const string& hostname);
      hostinfo (const in_addr& ipv4_addr);
      friend string to_string (const hostinfo&);
};

string localhost();
string to_string (const in_addr& ipv4_addr);

#endif

