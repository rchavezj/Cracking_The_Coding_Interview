// $Id: cix.cpp,v 1.4 2016-05-09 16:01:56-07 - - $

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream log (cout);
struct cix_exit: public exception {};

unordered_map<string,cix_command> command_map {
   {"exit", cix_command::EXIT },
   {"get" , cix_command::GET  },
   {"help", cix_command::HELP },
   {"ls"  , cix_command::LS   },
   {"put" , cix_command::PUT  },
   {"rm"  , cix_command::RM   },
};

void cix_help() {
   static const vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_get (client_socket& server, string filename){
   cix_header header;
   memset(&header, 0, sizeof header);
   header.command = cix_command::GET;
   log << "Sending header " << header << endl;
   if(filename.size() < FILENAME_SIZE) {
      strcpy(header.filename, filename.c_str()); 
      send_packet (server, &header, sizeof header);
      recv_packet (server, &header, sizeof header);
      log << "Received header " << header << endl;
      if(header.command == cix_command::FILE){
         ofstream fs(filename);
         char buffer[header.nbytes + 1];
         recv_packet (server, buffer, header.nbytes);
         log << "Received: " << header.nbytes << " bytes" << endl;
         buffer[header.nbytes] = '\0';
         fs.write(buffer, header.nbytes);
         fs.close();
      }else {
         log << "Command (GET): File ";
         log << header.filename ;
         log << "not found on server. "<< endl;
      }
   }else{
      log << " Command (GET): " << filename;
      log << " filename is too large!" << endl;
      log << " Choose a name with size ";
      log << FILENAME_SIZE << endl;
   }
}

void cix_ls (client_socket& server){
   cix_header header;
   memset(&header, 0, sizeof header);
   header.command = cix_command::LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != cix_command::LSOUT) {
      log << "sent LS, server did not return LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer;
   }
}

void cix_put(client_socket& server, string filename){
   cix_header header;
   memset(&header, 0, sizeof header);
   header.command = cix_command::PUT;
   if(filename.size() < FILENAME_SIZE){
         ifstream fs(filename);
         if (!fs.good()){
            log << "Not a valid file name: ";
            log << header.filename << endl;
         }else{
            header.nbytes = uint32_t(filename.size());
            strcpy(header.filename, filename.c_str());
            log << "sending header " << header << endl;
            send_packet (server, &header, sizeof header);
            recv_packet (server, &header, sizeof header);
            log << "received header " << header << endl;
            // log << "Lick my balls" << endl;
            if (header.command != cix_command::ACK) {
              log << "sent PUT, server did not return ACK" << endl;
              log << "server returned " << header << endl;
            }
         }
   }else{
      log << " Command (PUT): " << filename;
      log << " filename is too large!" << endl;
      log << " Choose a name with size ";
      log << FILENAME_SIZE << endl;
   }
}

void cix_rm(client_socket& server, string filename){
   cix_header header;
   memset(&header, 0, sizeof header);
   header.command = cix_command::RM;
   if(filename.size() < FILENAME_SIZE){
      header.nbytes = uint32_t(filename.size());
      strcpy(header.filename, filename.c_str());
      log << "sending header " << header << endl;
      send_packet (server, &header, sizeof header);
      recv_packet (server, &header, sizeof header);
      log << "received header " << header << endl;
      if (header.command != cix_command::ACK) {
        log << "sent RM, server did not return ACK" << endl;
        log << "server returned " << header << endl;
      }
   }else{
      log << " Command (RM): " << filename;
      log << " filename is too large!" << endl;
      log << " Choose a name with size ";
      log << FILENAME_SIZE << endl;
   }
}


void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

//Code inspired from util.cpp Assignment 2 (shell program)
vector<string> split (const string& line, const string& delimiters) {
   vector<string> words;
   size_t end = 0;
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   return words;
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      int i = 0;
      for (;;) {
         cout << "\nEnter command #" << i << ":"<< endl; i++;
         string line;
         string filename;
         getline (cin, line);
         vector<string> commandLine = split(line," ");
         cout << endl;
         if(cin.eof()) throw cix_exit();
         log << "command " << line << endl;
         const auto& itor = command_map.find (commandLine[0]);
         cix_command cmd = itor == command_map.end()
                         ? cix_command::ERROR : itor->second;
         if(cmd == cix_command::GET || 
            cmd == cix_command::PUT ||
            cmd == cix_command::RM){
            filename = commandLine[1] + "\0";
            if(filename.size()==0){
               log << "No file entered" << endl;
               continue;
            }
         }
         switch(cmd) {
            case cix_command::EXIT:
               throw cix_exit();
               break;
            case cix_command::GET:
               cix_get(server, filename);
               break;
            case cix_command::HELP:
               cix_help();
               break;
            case cix_command::LS:
               cix_ls(server);
               break;
            case cix_command::PUT:
               cix_put(server, filename);
               break;
            case cix_command::RM:
               cix_rm(server, filename);
               break;
            default:
               log << line << ": invalid command" << endl;
               break;
         }
      }
   }
   catch(socket_error& error){ log << error.what() << endl; }
   catch(cix_exit& error){ log << "caught cix_exit" << endl; }
   log << "finishing" << endl; return 0;
}

