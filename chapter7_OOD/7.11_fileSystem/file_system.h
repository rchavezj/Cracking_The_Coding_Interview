// $Id: file_system.h,v - - $

#ifndef __INODE_H__
#define __INODE_H__

#include <exception>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
using namespace std;

#include "util.h"

// inode_t -
//    An inode is either a directory or a plain file.

enum file_type {
   PLAIN_TYPE, 
   DIRECTORY_TYPE
};
class inode;
class base_file;
class plain_file;
class directory;
using inode_ptr = shared_ptr<inode>;
using base_file_ptr = shared_ptr<base_file>;
using plain_file_ptr = shared_ptr<plain_file>;
using directory_ptr = shared_ptr<directory>;
ostream& operator<< (ostream&, file_type);



// inode_state -
//    A small convenient class to maintain the state of the simulated
//    process:  the root (/), the current directory (.), and the
//    prompt.
class inode_state {
   friend class inode;
   friend ostream& operator<< (ostream& out, const inode_state&);
   private:
      string prompt_ {"==>$ "};
      inode_ptr cwd {nullptr};
      inode_ptr root {nullptr};
   public:
      inode_state();
      inode_state (const inode_state&) = delete; // copy ctor
      inode_state& operator= (const inode_state&) = delete; // op=
      const string prompt();
      void cat(const wordvec& words);
      void cd(const wordvec& words);
      void echo(const wordvec& words);
      void ls(const wordvec& words);
      void lsr(const wordvec& words);
      void lsr_pathname(const wordvec& words);
      void make(const wordvec& words);
      void mkdir(const wordvec& words);
      void prompt(const wordvec& words);
      void pwd(const wordvec& words);
      void pwd(const wordvec& words, const inode_ptr pwdLocation);
      void rm(const wordvec& words);
      void rmr(const wordvec& words);
      bool does_dir_file_exist(const wordvec& path, const inode_ptr potentialFile);
      string pwd_str(const wordvec& words, const inode_ptr pwdLocation);
      inode_ptr naviPath(const wordvec& words,int path_index);
};


// class inode -
// inode ctor -
//    Create a new inode of the given type.
// get_inode_nr -
//    Retrieves the serial number of the inode.  Inode numbers are
//    allocated in sequence by small integer.
// size -
//    Returns the size of an inode.  For a directory, this is the
//    number of dirents.  For a text file, the number of characters
//    when printed (the sum of the lengths of each word, plus the
//    number of words.  
class inode {
   friend class inode_state;
   private:
      static int next_inode_nr;
      string name;
      int inode_nr;
      file_type type;
      base_file_ptr contents;
   public:
      inode (file_type type);
      size_t size() const;
      int get_inode_nr() const;
      void set_name(const string& newName);
      string get_name() const;
      file_type get_type() const;
      base_file_ptr get_contents() const;
};



// class base_file -
// Just a base class at which an inode can point.  No data or
// functions.  Makes the synthesized members useable only from
// the derived classes.
class file_error: public runtime_error {
   public:
      explicit file_error (const string& what);
};
class base_file {
   protected:
      base_file() = default;
   public:
      virtual ~base_file() = default;
      base_file (const base_file&) = delete;
      base_file& operator= (const base_file&) = delete;
      virtual size_t size() const = 0;
      void mkfile (const string& filename);
      friend plain_file_ptr plain_file_ptr_of (base_file_ptr);
      friend directory_ptr directory_ptr_of (base_file_ptr);
};



// class plain_file -
// Used to hold data.
// synthesized default ctor -
//    Default vector<string> is a an empty vector.
// readfile -
//    Returns a copy of the contents of the wordvec in the file.
// writefile -
//    Replaces the contents of a file with new contents.
class plain_file: public base_file {
   private:
      wordvec data;
   public:
      size_t size() const override;
      const wordvec& readfile() const;
      void writefile (const wordvec& newdata);
      void remove (const string& filename);
      void mkfile (const string& filename);
};


// class directory -
// Used to map filenames onto inode pointers.
// default ctor -
//    Creates a new map with keys "." and "..".
// remove -
//    Removes the file or subdirectory from the current inode.
//    Throws an file_error if this is not a directory, the file
//    does not exist, or the subdirectory is not empty.
//    Here empty means the only entries are dot (.) and dotdot (..).
// mkdir -
//    Creates a new directory under the current directory and 
//    immediately adds the directories dot (.) and dotdot (..) to it.
//    Note that the parent (..) of / is / itself.  It is an error
//    if the entry already exists.
// mkfile -
//    Create a new empty text file with the given name.  Error if
//    a dirent with that name exists.
class directory: public base_file {
   private:
      // Must be a map, not unordered_map, so printing is lexicographic
      map<string,inode_ptr> dirents;
   public:
      size_t size() const override;
      const wordvec& readfile() const;
      void iterate_ls();
      vector<inode_ptr> subDirectory();
      void mkdir (const string& dirname);
      void new_directory(inode_ptr root);
      void remove (const string& filename);
      void set_parent_child(inode_ptr parent, inode_ptr child);
      inode_ptr lookup (const string& lookup);
      inode_ptr mkfile (const string& filename);
      inode_ptr get_child(const string& filename);
};

#endif

