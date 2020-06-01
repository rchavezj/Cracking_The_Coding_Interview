// $Id: commandLine.cpp, - - $

#include "commandLine.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
};

command_fn find_command_fn (const string& cmd) {
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such command");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message(){
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

void fn_cat (inode_state& state, const wordvec& words){
   state.cat(words);
}

void fn_cd (inode_state& state, const wordvec& words){
   state.cd(words);
}

void fn_echo (inode_state& state, const wordvec& words){
   state.echo(words);
}


void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
   state.ls(words);
}

void fn_lsr (inode_state& state, const wordvec& words){
   state.lsr(words);
}

void fn_make (inode_state& state, const wordvec& words){
   state.make(words);
}

void fn_mkdir (inode_state& state, const wordvec& words){
   state.mkdir(words);
}

void fn_prompt (inode_state& state, const wordvec& words){
   state.prompt(words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   state.pwd(words);
}

void fn_rm (inode_state& state, const wordvec& words){
   state.rm(words);
}

void fn_rmr (inode_state& state, const wordvec& words){
   state.rmr(words);
}
