// $Id: commandLine.h,v --$

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <unordered_map>
using namespace std;

#include "file_system.h"
#include "util.h"

// A couple of convenient usings to avoid verbosity.

using command_fn = void (*)(inode_state& state, const wordvec& words);
using command_hash = unordered_map<string,command_fn>;

// command_error -
//    Extend runtime_error for throwing exceptions related to this 
//    program.

class command_error: public runtime_error {
   public: 
      explicit command_error (const string& what);
};

// execution functions -

void fn_cat    (inode_state& state, const wordvec& words);
void fn_cd     (inode_state& state, const wordvec& words);
void fn_echo   (inode_state& state, const wordvec& words);
void fn_exit   (inode_state& state, const wordvec& words);
void fn_ls     (inode_state& state, const wordvec& words);
void fn_lsr    (inode_state& state, const wordvec& words);
void fn_make   (inode_state& state, const wordvec& words);
void fn_mkdir  (inode_state& state, const wordvec& words);
void fn_prompt (inode_state& state, const wordvec& words);
void fn_pwd    (inode_state& state, const wordvec& words);
void fn_rm     (inode_state& state, const wordvec& words);
void fn_rmr    (inode_state& state, const wordvec& words);

command_fn find_command_fn (const string& command);

// exit_status_message -
//    Prints an exit message and returns the exit status, as recorded
//    by any of the functions.

int exit_status_message();
class ysh_exit: public exception {};

#endif
