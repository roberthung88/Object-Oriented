#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "md_parser.h"
#include "txt_parser.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Must provide an index file and output file" << endl;
        return 1;
    }

    // ---------------------- [TO BE COMPLETED] -------------------------------
    ifstream in_file(argv[1]); //open seed file
    ofstream out_file(argv[2]); //output file
    
    string temp;
    //register parsers
    map<string, PageParser*> parsers;
    TXTParser txtparser;
    MDParser mdparser;
    parsers.insert(make_pair("md", &mdparser));
    parsers.insert(make_pair("txt", &txtparser));
    
    set<string> done;
    done.clear();

    if(in_file.fail()){
        cout << "Couldn't open seed file!" << endl;
        return 1;
    }
    while(in_file >> temp){
        if(done.find(temp) == done.end()){
            //get extension
            map<string, PageParser*>::iterator it = parsers.find(extract_extension(temp));
            if(it != parsers.end()){
                done.insert(temp);
                out_file << temp << endl;
                it->second->crawl(parsers, temp, done, out_file);
            }
        }
    }
    
    // You may add cleanup code here if necessary

    return 0;
}
