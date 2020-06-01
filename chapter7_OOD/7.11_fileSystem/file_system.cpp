// $Id: file_system.cpp,v 1.5 2016-01-14 16:16:52-08 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "debug.h"
#include "file_system.h"


using namespace std;

//////////////////////////////////////////////////////////////
///////////////////// initialization /////////////////////////
int inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

file_error::file_error (const string& what):
            runtime_error (what) {
}

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {PLAIN_TYPE, "PLAIN_TYPE"},
      {DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}
///////////////////// initialization /////////////////////////
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
/////////////////////// inode_state //////////////////////////
inode_state::inode_state() {
  root = make_shared<inode>(DIRECTORY_TYPE);
  cwd = root;
  directory_ptr_of(root->contents)->new_directory(root);
  DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
}

const string inode_state::prompt() { 
  return "Advance_File_System:" + cwd->name + " " + prompt_; 
}

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

void inode_state::cat(const wordvec& words){
  if (words.size() == 1){
    cout << "Needs More arguments." << endl;
  }else{
    int i = 1;
    const auto end = words.end();
    const auto begin = words.begin();
    file_type is_dir = DIRECTORY_TYPE;
    for(auto itor = begin+1; itor != end; itor++, i++){
       inode_ptr target = naviPath(words, i);
       if( target != NULL && target->get_type() != is_dir){
          plain_file_ptr plain = plain_file_ptr_of(target->get_contents());
          cout << plain->readfile() << endl;
       }else{
          cout << "cat: " << words[i] << 
          ": No such file or directory" << endl;
       }
    }cout << endl;
  }
}

void inode_state::cd(const wordvec& words){
  if (words.size() == 1){
    cwd = root;
  }else{
    inode_ptr newLocation = naviPath(words, 1);
    if (newLocation == NULL){
      cout << "invalid location" << endl;
    }else{
      if (newLocation->get_type() != DIRECTORY_TYPE){
        cwd = newLocation;
      }else{
        cout << "invalid location" << endl;
      }
    }
  }
}

void inode_state::echo(const wordvec& words){
  cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

void inode_state::ls(const wordvec& words){
  if (words.size() == 1){
    inode_ptr currentLocation = cwd;
    directory_ptr dir = directory_ptr_of(currentLocation->get_contents());
    cout << pwd_str(words, currentLocation) << ":" << endl;
    dir->iterate_ls();
  }else{
    inode_ptr location = naviPath(words, 1);
    if (location == NULL){
      cout << "invalid location" << endl;
    }else{
      directory_ptr dir = directory_ptr_of(location->get_contents());
      pwd(words, location);
      dir->iterate_ls()  ;
    }
  }
}

void inode_state::lsr(const wordvec& words){
  if(words.size() == 2){
    lsr_pathname(words);
  }else if(words.size() == 1){
    wordvec pathname;
    directory_ptr dir = directory_ptr_of(cwd->get_contents());
    vector<inode_ptr> childeren = dir->subDirectory();
    cout << pwd_str(words, cwd) << ":" << endl;
    dir->iterate_ls();
    int i = 0;
    auto end = childeren.end();
    auto begin = childeren.begin();
    file_type dir_type = DIRECTORY_TYPE;
    for (auto itor = begin; itor != end; itor++, i++){
      if (childeren.at(i)->get_type() != dir_type){
        if (cwd == root){
          pathname.push_back("/" + childeren.at(i)->get_name());
          lsr_pathname(pathname);
          pathname.pop_back();
        }else{
          pathname.push_back(pwd_str(words, cwd) + "/" + childeren.at(i)->get_name());
          lsr_pathname(pathname);
          pathname.pop_back();
        }
      }
    }    
  }else{cout << "To many arguments" << endl;}
}

void inode_state::lsr_pathname(const wordvec& words){
  inode_ptr pathname_ptr;
  if (words.size() == 1) pathname_ptr = naviPath(words, 0);
  else pathname_ptr = naviPath(words, 1);
  if(pathname_ptr == NULL){
    cout << "Path Doesn't exist\n" << endl;
  }else{
    wordvec pathname;
    directory_ptr dir = directory_ptr_of(pathname_ptr->get_contents());
    vector<inode_ptr> childeren = dir->subDirectory();
    cout << pwd_str(words, pathname_ptr) << ":" << endl;
    dir->iterate_ls();
    int i = 0;
    auto end = childeren.end();
    auto begin = childeren.begin();
    file_type dir_type = DIRECTORY_TYPE;
    for (auto itor = begin; itor != end; itor++, i++){
      if (childeren.at(i)->get_type() != dir_type){
        if (pathname_ptr == root){
          pathname.push_back("/" + childeren.at(i)->get_name());
          lsr_pathname(pathname);
          pathname.pop_back();
        }else{
          pathname.push_back(pwd_str(words, pathname_ptr) + "/" + childeren.at(i)->get_name());
          lsr_pathname(pathname);
          pathname.pop_back();
        }
      }
    } 
  }
}

void inode_state::make(const wordvec& words){
  DEBUGF ('c', words);
  if (words.size() < 3){
    cout << "not enought arguments" << endl;
  }else{
    directory_ptr dir = directory_ptr_of(cwd->get_contents());
    inode_ptr file_node = dir->lookup(words[1]);
    if(file_node == nullptr){
      file_node = dir->mkfile(words[1]);
    }
    plain_file_ptr new_old_file = plain_file_ptr_of(file_node->get_contents());
    new_old_file->writefile(words);
  }
}
 
void inode_state::mkdir(const wordvec& words){
  if (words.size() == 1 || words.size() > 2){
    cout << "You invoked " << words.size() << " word(s)!" << endl;
    cout << "We only need 2 words. " << endl;
    cout << "First is the command and second, argument"<< endl;
  }else{
    inode_ptr target = naviPath(words, 1);
    if (target != NULL){
      cout << "mkdir: "<< words[1] <<": File exists" << endl;
    }else{
      directory_ptr dir = directory_ptr_of(cwd->get_contents());
      wordvec path = split(words[1],"/");
      dir->mkdir(path[path.size()-1]);
    }
  }
}

void inode_state::prompt(const wordvec& words){
  if(words.size() == 2){
    prompt_ = words[1] + " ";
  }
}

void inode_state::pwd(const wordvec& words){
  pwd(words, cwd);
}

void inode_state::pwd(const wordvec& words, const inode_ptr pwdLocation){
  string str;
  if (words.size() == 1){ 
    inode_ptr p = pwdLocation;
    directory_ptr dp = directory_ptr_of(p->contents);
    while(p != root){
        str = "/" + p->name + str;
        p = dp->lookup("..");
        dp = directory_ptr_of(p->contents);    
    }if (str.size() == 0){
      str = "/";
    }
    cout << str << endl;
  }
}

void inode_state::rm(const wordvec& words){
  if (words.size() == 1){
    cout << "You invoked " << words.size() << " word(s)!" << endl;
    cout << "We only need 2 words. " << endl;
    cout << "First is the command and second, argument"<< endl;
  }else{
    int i = 1;
    const auto end = words.end();
    const auto begin = words.begin();
    file_type is_dir = DIRECTORY_TYPE;
    for(auto itor = begin+1; itor != end; itor++, i++){
      inode_ptr target = naviPath(words, i);
      if( target != NULL && target->get_type() != is_dir){
          directory_ptr dir = directory_ptr_of(cwd->get_contents());
          dir->remove(words[i]);
       }else{
          cout << "rm: " << words[i] << 
          ": No such file exist" << endl;
       }
    }
  }
}

void inode_state::rmr(const wordvec& words){
  DEBUGF ('c', words);
}

bool inode_state::does_dir_file_exist(const wordvec& path, const inode_ptr potentialFile){
  inode_ptr potentialFile_ = potentialFile;
  directory_ptr dir = directory_ptr_of(potentialFile_->get_contents());
  potentialFile_ = dir->get_child(path[0]);
  if(potentialFile_ == NULL && path.size() == 1) return false;
  return true; 
}

string inode_state::pwd_str(const wordvec& words, const inode_ptr pwdLocation){
  string str;
  if (words.size() == 1){ 
    inode_ptr p = pwdLocation;
    directory_ptr dp = directory_ptr_of(p->contents);
    while(p != root){
        str = "/" + p->name + str;
        p = dp->lookup("..");
        dp = directory_ptr_of(p->contents);    
    }if (str.size() == 0){
      str = "/";
    }
  }return str;
}

inode_ptr inode_state::naviPath(const wordvec& words, int path_index){         
   inode_ptr head;
   directory_ptr dir;
   wordvec path = split(words[path_index],"/");
   file_type is_dir = DIRECTORY_TYPE;
   int size = path.size();
   if(words[path_index].at(0) =='/'){
      if (words[path_index].size() == 1){
        return root;
      }head = root;
   }else{
      head = cwd;
   }
   
   dir = directory_ptr_of(head->get_contents());
   head = dir->get_child(path[0]);
   if(head == NULL && path.size() == 1) return NULL;

   for(int i = 1; i < size; i++){
      if(head->get_type() != is_dir){
        dir = directory_ptr_of(head->get_contents());
        head = dir->get_child(path[i]);
      }else{ 
        return NULL;
      }
   }return head;
}
/////////////////////// inode_state //////////////////////////
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
////////////////////////// inode /////////////////////////////
inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case PLAIN_TYPE:
           type = PLAIN_TYPE;
           contents = make_shared<plain_file>();
           break;
      case DIRECTORY_TYPE:
           type = DIRECTORY_TYPE;
           contents = make_shared<directory>();
           break;
   }
}

size_t inode::size() const {
    if (type != PLAIN_TYPE)
        return plain_file_ptr_of(contents)->size();
    else
        return directory_ptr_of(contents)->size();
}

int inode::get_inode_nr() const {
   return inode_nr;
}

void inode::set_name(const string& newName){
  name  = newName;
}

string inode::get_name() const{
  return name;
}

file_type inode::get_type() const{
  return type;
}

base_file_ptr inode::get_contents() const{
  return contents;
}
///////////////////////// inode //////////////////////////////
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
//////////////////////// base_file ///////////////////////////
plain_file_ptr plain_file_ptr_of (base_file_ptr ptr) {
  plain_file_ptr pfptr = dynamic_pointer_cast<plain_file> (ptr);
  if (pfptr == nullptr){
    throw invalid_argument ("plain_file_ptr_of");
  }
  return pfptr;
}

directory_ptr directory_ptr_of (base_file_ptr ptr) {
  directory_ptr dirptr = dynamic_pointer_cast<directory> (ptr);
  if (dirptr == nullptr){
    throw invalid_argument ("directory_ptr_of");
  } 
  return dirptr;
}
/////////////////////// base_file ////////////////////////////
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
/////////////////////// plain_file ///////////////////////////

size_t plain_file::size() const {
   size_t size {0};
   size = data.size();
   for (auto word = data.begin();
             word != data.end();
             word++) {
      size += word->size();
   }
   if (size > 1) size -= 1;
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

void plain_file::writefile (const wordvec& words){
   if (data.size() != 0){
     data.clear();
   }int itor = 2;
   for (auto i = words.begin()+2; i != words.end(); i++, itor++){
     data.push_back(words[itor]);
   }
}

void plain_file::remove (const string&) {
   throw file_error ("is a plain file");
}

void plain_file::mkfile (const string&) {
   throw file_error ("is a plain file");
}
/////////////////////// plain_file ///////////////////////////
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
/////////////////////// directory ////////////////////////////

size_t directory::size() const {
   size_t size {0};
   size = dirents.size();
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& directory::readfile() const {
   throw file_error ("is a directory");
}

void directory::iterate_ls(){
  auto itor = dirents.begin();
  auto end = dirents.end();
  for (; itor != end; ++itor) {
    cout << "\t" << itor->second->get_inode_nr() << "\t";
    cout << itor->first << endl;
  }
}

void directory::mkdir(const string& dirname) {
  if (dirents.find(dirname) != dirents.end()){
    cout << "mkdir: " + dirname + ": dirname exists" << endl;
  }
  inode_ptr parent = dirents.at(".");
  inode_ptr dirnode = make_shared<inode>(DIRECTORY_TYPE);
  dirnode->set_name(dirname);
  directory_ptr dir = directory_ptr_of(dirnode->get_contents());
  dir->set_parent_child(parent, dirnode);
  dirents.insert(make_pair(dirname, dirnode));
}

void directory::new_directory(inode_ptr root){
  dirents.insert(make_pair(".", root));
  dirents.insert(make_pair("..", root));
  root->set_name("/");
}

void directory::remove (const string& filename){
  auto find = dirents.find(filename);
  if (find != dirents.end()){
    dirents.erase(filename);
  }
}

void directory::set_parent_child(inode_ptr parent, inode_ptr child){
    dirents.insert(make_pair(".", child));
    dirents.insert(make_pair("..", parent));
}

inode_ptr directory::lookup(const string& lookup){
  auto find = dirents.find(lookup);
  if (find != dirents.end()){
    return find->second;
  }return nullptr;
}

inode_ptr directory::mkfile (const string& filename) {
  inode_ptr file_node = make_shared<inode>(PLAIN_TYPE);
  file_node->set_name(filename);
  dirents.insert(make_pair(filename, file_node));
  return file_node;
}

inode_ptr directory::get_child(const string &dirname){
  auto itor = dirents.begin();
  auto end = dirents.end();
   
   for (; itor != end; ++itor) {
      if ( dirname.compare(itor->first) == 0)
         return itor->second;
   }
   return NULL;
}

vector<inode_ptr> directory::subDirectory(){
  vector<inode_ptr> childeren;
  auto itor = dirents.begin();
  itor++; // ignore .  directory
  itor++; // ignore .. directory
  auto end = dirents.end();
  // file_type is_dir = DIRECTORY_TYPE;

  for (; itor != end; ++itor) {
    if (itor->second->get_type() != DIRECTORY_TYPE){
      // cout << "Test: " << endl;
      childeren.push_back(itor->second);
    }
  }return childeren;
}
/////////////////////// directory ////////////////////////////
//////////////////////////////////////////////////////////////
