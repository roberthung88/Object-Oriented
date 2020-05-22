#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;


void MDParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if(!wfile) {
        throw invalid_argument("Bad webpage filename in MDParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();
    if(state == NORMALTEXT && c == '['){
        state = LINKTEXT;
        c = wfile.get();
    }
    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            if(state == NORMALTEXT && c == '['){
                if(term != ""){
                    allSearchableTerms.insert(conv_to_lower(term));
                    term = "";
                }
                state = LINKTEXT;
                c = wfile.get();
                continue;
                
            }
            if(isalnum(c)){
                term = term + c;
            }else{
                if(term != ""){
                    allSearchableTerms.insert(conv_to_lower(term));
                    term = "";
                }
            }


        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            
          if(state == LINKTEXT && c == ']'){
                if(term != ""){
                    allSearchableTerms.insert(conv_to_lower(term));
                    term = "";
                }
                state = ISLINK;
                c = wfile.get();
                continue;
            }
            if(isalnum(c)){
                term = term + c;
            }else{
                if(term != ""){
                    allSearchableTerms.insert(conv_to_lower(term));
                    term = "";
                }
            }



        }
        else if( state == ISLINK )
        {
          
           if(state == ISLINK && c != '('){
                state = NORMALTEXT;
                continue;
            }else if(state == ISLINK && c == '('){
                state = LINKURL;
                c = wfile.get();
                continue;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            if(state == LINKURL && c == ')'){
                allOutgoingLinks.insert(link);
                link = "";
                state = NORMALTEXT;
                c = wfile.get();
                continue;
            }
            if(c != ')'){
                link = link + c;
            }
        }
        // Attempt to get another character from the file.
        c = wfile.get();
    }
    // ADD ANY REMAINING CODE HERE




    // Close the file.
    wfile.close();
}

std::string MDParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        // Logic for parsing a normal term.
        if (state == NORMALTEXT)
        {
            // The moment we hit a bracket, we input our current working term
            // into the allSearchableTerms set, reset the current term, and move into
            // parsing a link.
            if (c == '[')
            {
                state = LINKTEXT;
            }
            retval += c;
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // When we hit the closing bracket, then we must be finished getting the link.
            if (c == ']')
            {
                state = ISLINK;
            }
            retval += c;
        }
        else if (state == ISLINK) {
            if (c == '(') {
                state = LINKURL;
            }
            else
            {
                state = NORMALTEXT;
                retval += c;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // When we hit a closing parenthese then we are done, and the link can be inserted.
            if (c == ')')
            {
                state = NORMALTEXT;
            }
        }
        c = wfile.get();
    }
    return retval;
}


void MDParser::crawl(const std::map<std::string, PageParser*>& parsers,std::string filename, std::set<std::string>& processed, std::ostream& ofile){
    ifstream infile(filename); //open seed file
    if(infile.fail()){
        cout << "File Can't Be Opened! Skipping..." << endl;
        infile.clear();
        return;
    }
    
    set<string> links;
    set<string> terms;
    
    parse(filename, terms, links);
    
    for(set<string>::iterator it = links.begin(); it != links.end(); ++it){
       if(processed.find(*it) == processed.end()){
           map<string, PageParser*>::const_iterator itparsers = parsers.find(extract_extension(*it));
           if(itparsers != parsers.end()){
               processed.insert(*it);
               ofile << *it << endl;
               itparsers->second->crawl(parsers, *it, processed, ofile);
           }
        }
    }
   
}


