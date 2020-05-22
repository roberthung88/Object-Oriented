#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string LOG_COMMIT_STARTER = "Commit: ";



// Class implementation
GitInt::GitInt(){
    //create empty 0 commit
    std::map<std::string, int> temp;
    CommitObj first("", temp, 0);
    commits_.push_back(first);
}

void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);

    if (cmd == "quit"){
        quit = true;
    }else if(cmd == "create"){
        string filename = "";
        ss >> filename;
        if(filename == ""){
            //filename not provided
            throw std::runtime_error(INVALID_COMMAND);
        }else{
            //filename provided
            if(valid_file(filename)){
                //filename already exists
                throw std::invalid_argument(INVALID_OPTION);
            }else{
                //filename doesn't exist so add
                int value;
                ss >> value;
                if(ss.fail()){
                    //integer not provided
                    throw std::runtime_error(INVALID_COMMAND);
                }else{
                    //integer provided
                    create(filename, value);
                }
                
            }
        }
    }else if(cmd == "edit"){
        string filename = "";
        ss >> filename;
        if(filename == ""){
            //filename not provided
            throw std::runtime_error(INVALID_COMMAND);
        }else{
            //filename provided
            if(!valid_file(filename)){
                //filename does not exists
                throw std::invalid_argument(INVALID_OPTION);
            }else{
                //filename exists
                int value;
                ss >> value;
                if(ss.fail()){
                    //integer not provided
                    throw std::runtime_error(INVALID_COMMAND);
                }else{
                    //integer provided
                    edit(filename, value);
                }
            }
        }
    }else if(cmd == "display"){
        int commitnum;
        ss >> commitnum;
        if(ss.eof()){
            //nothing provided
            display_all();
        }else{
            //something provided
            if(ss.fail()){
                //a string is input
                ss.clear();
                string filename;
                ss >> filename;
                if(!valid_file(filename)){
                    //invalid filename
                    throw std::invalid_argument(INVALID_OPTION);
                }else{
                    //valid filename
                    display(filename);
                }
            }else{
                //an int is input
                if(valid_commit(commitnum)){
                    //invalid commit number
                    throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                }else{
                    //valid commit number
                    display_commit(commitnum);
                }
            }
        }
    }else if(cmd == "add"){
        if(ss.eof()){
            return false;
        }else{
            string input;
            ss >> input;
            if(!valid_file(input)){
                //invalid filename
                throw std::invalid_argument(INVALID_OPTION);
            }else{
                //valid filename
                add(input);
                while(!ss.eof()){
                    string input;
                    ss >> input;
                    if(valid_file(input)){
                        add(input);
                    }else{
                        return false;
                    }
                }
            }
        }
    }else if(cmd == "commit"){
        if(staged_files.size() == 0){
            throw std::runtime_error(INVALID_COMMAND);
        }
        if(ss.eof()){
            //no message provided
            throw std::runtime_error(INVALID_COMMAND);
        }else{
            //there is message
            string message;
            getline(ss, message);
            if(message == "\"\""){
                //no message
                throw std::runtime_error(INVALID_COMMAND);
            }
            message.erase(0, message.find_first_not_of(' '));
            if(message.substr(0,1) == "\""){
                size_t index = message.substr(1).find("\"");
                if(index == string::npos){
                    //incorrect format
                    throw std::runtime_error(INVALID_COMMAND);
                }else{
                    string temp = message.substr(1, index);
                    commit(temp);
                }
            }
        }
    }else if(cmd == "log"){
        GitInt::log();
    }else if(cmd == "tag"){
        string type = "";
        ss >> type;
        if(!ss.eof()){
            // uses -a
            if(type != "-a"){
                throw std::runtime_error(INVALID_COMMAND);
            }else{
                string tagname;
                ss >> tagname;
                map<string, int>::iterator it;
                it = taghelper.find(tagname);
                if(it == taghelper.end()){
                    //not found
                    create_tag(tagname, head_);
                }else{
                    //found
                    throw std::invalid_argument(INVALID_OPTION);
                }
            }
            
        }else{
            GitInt::tags();
        }
    }else if(cmd == "checkout"){
        //check if anything is provided
        if(ss.eof()){
            //nothing provided
            throw std::runtime_error(INVALID_OPTION);
        }else{
            int input;
            ss >> input;
            if(ss.fail()){
                //a string is input
                ss.clear();
                string tagname;
                ss >> tagname;
                map<string, int>::iterator it;
                it = taghelper.find(tagname);
                if(it == taghelper.end()){
                    //invalid tag-name
                    throw std::invalid_argument(INVALID_OPTION);
                }else{
                    checkout(tagname);
                }
            }else{
                //an int is input
                if(!valid_commit(input)){
                    //invalid commit number
                    throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                }else{
                    checkout(input);
                }
                
            }
        }
        
    }else if(cmd == "diff"){
        if(ss.eof()){
            diff(head_);
            return false;
        }
        int input;
        ss >> input;
        if(ss.fail()){
            //not integer
            throw std::invalid_argument(INVALID_COMMIT_NUMBER);
        }
        if(valid_commit(input)){
            if(!ss.eof()){
                //two input
                int input2;
                ss >> input2;
                if(valid_commit(input2)){
                    if(input >= input2){
                        diff(input, input2);
                    }else{
                        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                    }
                }else{
                    throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                }
            }else{
                //one input
                diff(input);
            }
        }else{
            throw std::invalid_argument(INVALID_COMMIT_NUMBER);
        }
    }else{
        throw std::runtime_error(INVALID_COMMAND);
    }
    return quit;
}

void GitInt::create(const std::string& filename, int value){
    files.insert(make_pair(filename, value));
}

void GitInt::edit(const std::string& filename, int value){
    files[filename] = value;

}

void GitInt::display_commit(CommitIdx commit) const
{
    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    display_helper(commits_[commit].diffs_);
}


void GitInt::display_helper(const std::map<std::string, int>& dat) const
{
    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}

void GitInt::display(const std::string& filename) const{
    map<std::string,int>::const_iterator it = files.find(filename);
    cout << it->first << " : " << it->second << endl;
    
}

void GitInt::display_all() const{
    display_helper(files);
}

//Note: After adding a file it may still be edited and when it is committed the latest value //should be committed, not the value of the file when it was added.
void GitInt::add(string filename){
    staged_files.insert(filename);
}

/**
 * Commits all files staged since the last commit
 * [TO BE WRITTEN]
 *
 * @param[in] message
 *    Log message for this commit
 * @throws std::runtime_error -
 *    See homework writeup for details on error cases
 */
void GitInt::commit(std::string message){
    map<std::string, int> result;
    int store;
    map<std::string, int> built = buildState(head_);
    for(set<string>::iterator it=staged_files.begin();
                it != staged_files.end(); ++it){
       
        map<string, int>::iterator curr = files.find(*it);
        map<string, int>::iterator prev = built.find(*it);
        
        if(curr == files.end()){
            continue;
        }else{
            if(prev!= built.end()){
                store = curr->second - prev->second;
            }else{
                store = curr->second;
            }
        }
        result.insert(make_pair(*it, store));
    }
    staged_files.clear();
    CommitObj a(message, result, head_);
    commits_.push_back(a);
    head_ = int(commits_.size() - 1);
}

void GitInt::create_tag(const std::string& tagname, CommitIdx commit){
    taghelper.insert(make_pair(tagname, commit));
    tag_name.push_back(tagname);
}

void GitInt::tags() const{
    for(int i = int(tag_name.size() - 1); i >= 0; --i){
        cout << tag_name[i] << endl;
    }
}

bool GitInt::checkout(std::string tag){
    map<string,int>::iterator it = taghelper.find(tag);
    files.clear();
    staged_files.clear();
    files = buildState(it->second);
    head_ = it->second;
    return true;
}

bool GitInt::checkout(CommitIdx commitIndex){
    files.clear();
    staged_files.clear();
    files = buildState(commitIndex);
    head_ = commitIndex;
    return true;
}

void GitInt::log() const{
    int now = head_;
    while(now >= 1){
        cout << "Commit: " << now << endl;
        cout << commits_[now].msg_ << endl;
        cout << endl;
        now = commits_[now].parent_;
    }
}

void GitInt::diff(CommitIdx to) const{
    map<std::string, int> todata = buildState(to, 0);
    for (std::map<std::string, int>::const_iterator cit = files.begin();
    cit != files.end();
    ++cit) {
        map<std::string, int>::iterator it = todata.find(cit->first);
        if (it != todata.end()){
            if((cit->second - it->second) != 0){
                cout << cit->first << " : " << (cit->second - it->second) << endl;
            }
        }else{
            //not found
            cout << cit->first << " : " << cit->second << endl;
        }
    }
}

void GitInt::diff(CommitIdx from, CommitIdx to) const{
    map<std::string, int> todata = buildState(to);
    map<std::string, int> fromdata = buildState(from);
    
    for (std::map<std::string, int>::const_iterator cit = fromdata.begin(); cit != fromdata.end(); ++cit) {
        map<std::string, int>::iterator it = todata.find(cit->first);
        if (it != todata.end()){
            if(cit->second - it->second != 0){
                cout << cit->first << " : " << (cit->second - it->second) << endl;
            }
        }else{
            //not found
            cout << cit->first << " : " << cit->second << endl;
        }
    }
}

bool GitInt::valid_commit(CommitIdx commit) const{
   if(commit > int(commits_.size() - 1) || commit < 0){
       //invalid commit number
       return false;
   }else{
       return true;
   }
}

bool GitInt::valid_file(string name) const{
    map<string, int>::const_iterator it;
    it = files.find(name);
    if(it == files.end()){
        //invalid filename
        return false;
    }else{
        return true;
    }
}
void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}

//fix this to include past commited values
std::map<std::string, int> GitInt::buildState(CommitIdx from, CommitIdx to) const{
    int now = commits_[from].parent_;
    map<string, int> result = commits_[from].diffs_;

    while(now >= 1){
        map<string, int> temp = commits_[now].diffs_;
        for(map<string, int>::iterator it = temp.begin(); it != temp.end(); ++it)
        {
            map<string, int>::iterator itt= result.find(it->first);
            if(itt != result.end()){
                //found it in this commit
                itt->second = itt->second + it->second;
            }else{
                result.insert(make_pair(it->first, it->second));
            }
            
        }
        now = commits_[now].parent_;
    }
    return result;
}
