#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"
#include <utility>

using namespace std;


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary


}

SearchEng::~SearchEng(){
    for(map<string, WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it){
        delete it->second;
    }
}

void SearchEng::read_page(const std::string& filename){
    map<string, WebPage*>::iterator it = pages.find(filename);

    string extension = extract_extension(filename);
    set<std::string> allTerms;
    set<std::string> allOutLinks;
    if(extension == ""){
        noExtensionParser_->parse(filename, allTerms, allOutLinks);
    }else{
        map<std::string,PageParser*>::iterator it = parsers.find(extension);
        if(it == parsers.end()){
            noExtensionParser_->parse(filename, allTerms, allOutLinks);
        }else{
            it->second->parse(filename, allTerms, allOutLinks);
        }
    }
    
    if(it == pages.end()){
        //not found so add
        WebPage* temp = new WebPage(filename);
        temp->all_terms(allTerms);
        pages[filename] = temp;

        for(set<string>::iterator itlinks = allOutLinks.begin(); itlinks != allOutLinks.end(); ++itlinks){
            
            map<string, WebPage*>::iterator outlink = pages.find(*itlinks);
            //need to check if links already appear in pages
            if(outlink == pages.end()){
                WebPage* toAdd = new WebPage(*itlinks);
                temp->add_outgoing_link(toAdd);
                toAdd->add_incoming_link(temp);
                pages.insert(make_pair(*itlinks, toAdd));
            }else{
                temp->add_outgoing_link(outlink->second);
                outlink->second->add_incoming_link(temp);
            }
        }
            
        for(set<string>::iterator itterms = allTerms.begin(); itterms != allTerms.end(); ++itterms){
            map<string, set<string>>::iterator itt = terms_files.find(*itterms);
            if(itt != terms_files.end()){
                itt->second.insert(filename);
            }else{
                set<string> tempterm;
                tempterm.insert(filename);
                terms_files.insert(make_pair(*itterms, tempterm));
            }
        }
    }else{
        it->second->all_terms(allTerms);
        for(set<string>::iterator itlinks = allOutLinks.begin(); itlinks != allOutLinks.end(); ++itlinks){
            
            map<string, WebPage*>::iterator outlink = pages.find(*itlinks);
            //need to check if links already appear in pages
            if(outlink == pages.end()){
                WebPage* toAdd = new WebPage(*itlinks);
                it->second->add_outgoing_link(toAdd);
                toAdd->add_incoming_link(it->second);
                pages.insert(make_pair(*itlinks, toAdd));
            }else{
                it->second->add_outgoing_link(outlink->second);
                outlink->second->add_incoming_link(it->second);
            }
        }
            
        for(set<string>::iterator itterms = allTerms.begin(); itterms != allTerms.end(); ++itterms){
            map<string, set<string>>::iterator itt = terms_files.find(*itterms);
            if(itt != terms_files.end()){
                itt->second.insert(filename);
            }else{
                set<string> tempterm;
                tempterm.insert(filename);
                terms_files.insert(make_pair(*itterms, tempterm));
            }
        }
    }
}

void SearchEng::register_parser(const std::string& extension, PageParser* parser){
    map<string,PageParser*>::iterator it = parsers.find(extension);
    if(it == parsers.end()){
        parsers.insert(make_pair(extension, parser));
    }else{
        it->second = parser;
    }
}
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

WebPage* SearchEng::retrieve_page(const std::string& page_name) const{
    std::map<std::string, WebPage*>::const_iterator it = pages.find(page_name);
    if(it != pages.end()){
        return it -> second;
    }else{
        return NULL;
    }
}

void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const{
    //find extension, use specfic parser.display_text. Then ostr << that string.
    string extension = extract_extension(page_name);
    if(extension == ""){
        ostr << noExtensionParser_->display_text(page_name);
    }else{
        map<string,PageParser*>::const_iterator find_parser = parsers.find(extension);
        if(find_parser == parsers.end()){
            throw std::logic_error("Logic Error");
        }
        if(pages.find(page_name) == pages.end()){
            throw std::invalid_argument("Invalid Argument");
        }else{
            ostr << find_parser->second->display_text(page_name);
        }
       
    }
}
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const{
    WebPageSet temp1;
    WebPageSet temp2;
    int state = 1;
    bool filled = false;
   
    for(vector<string>::const_iterator it = terms.begin(); it != terms.end(); ++it){
        map<string, set<string>>::const_iterator findTerm = terms_files.find(*it);
        if(findTerm != terms_files.end()){
            //found it
            for(set<string>::iterator loopFiles = findTerm->second.begin(); loopFiles != findTerm->second.end(); ++loopFiles){
                //look it up using its string name
                if(state == 1){
                    map<string, WebPage*>::const_iterator  lookupPage = pages.find(*loopFiles);
                    temp1.insert(lookupPage->second);
                }else if(state == 2){
                    map<string, WebPage*>::const_iterator lookupPage = pages.find(*loopFiles);
                    temp2.insert(lookupPage->second);
                    filled = true;
                }
            }
            if(state == 2 && filled){
                state = 3;
                filled = false;
            }
            if(state == 1){
                state = 2;
            }else if(state == 3){
                temp1 = combiner->combine(temp1, temp2);
                temp2.clear();
                state = 2;
            }
        }
    }
    return temp1;
}

/**
    * Performs the PageRank algorithm on the webpages in the input set
    * @param[in] in_pages
    *   Unexpanded candidate set of webpages to run the PageRank algorithm on
    *
    * @return vector of pairs of webpage pointers and their PageRank score
    */
vector<pair<WebPage*, double>> SearchEng::pageRank(const WebPageSet& in_pages){
    vector<pair<WebPage*, double>> result;
    WebPageSet expanded = in_pages;
    map<string, double> temp_result;
    map<string, double> priordone;
    StringSet names;
    double eps = 0.15;
    for(set<WebPage*>::const_iterator innames = in_pages.begin(); innames != in_pages.end(); ++innames){
        names.insert((*innames)->filename());
    }
    
    //create expanded WebPageSet
    for(set<WebPage*>::const_iterator it = in_pages.begin(); it != in_pages.end(); ++it){
        WebPageSet incoming = (*it)->incoming_links();
        WebPageSet outgoing = (*it)->outgoing_links();
        for(set<WebPage*>::const_iterator it1 = incoming.begin(); it1 != incoming.end(); ++it1){
            if(names.find((*it1)->filename()) == names.end()){
                expanded.insert(*it1);
                names.insert((*it1)->filename());
            }
        }
        for(set<WebPage*>::const_iterator it2 = outgoing.begin(); it2 != outgoing.end(); ++it2){
            if(names.find((*it2)->filename()) == names.end()){
                expanded.insert(*it2);
                names.insert((*it2)->filename());
            }
        }
    }
    
    //initialize mapping of string name to double value
    for(set<WebPage*>::const_iterator it = expanded.begin(); it != expanded.end(); ++it){
        double initval = 1.0/(expanded.size());
        temp_result.insert(make_pair((*it)->filename(), initval));
        priordone.insert(make_pair((*it)->filename(), initval));
        result.push_back(make_pair(*it, initval));
    }
    
    for(int i = 0; i < 20; ++i){
        for(vector<pair<WebPage*, double>>::iterator it = result.begin(); it != result.end(); ++it){
            
            WebPageSet incoming = it->first->incoming_links();
            
            double temp = 0;
            int countOut = 0;
            map<string, double>::iterator it2;
            for(set<WebPage*>::iterator it1 = incoming.begin(); it1 != incoming.end(); ++it1){
                countOut = 0;
                if(names.find((*it1)->filename()) != names.end()){
                    //count number of valid outgoing links
                    
                    for(set<WebPage*>::iterator it3 = (*it1)->outgoing_links().begin(); it3 != (*it1)->outgoing_links().end(); ++it3){
                        if(names.find((*it3)->filename()) != names.end()){
                            countOut++;
                        }
                    }
                    countOut++;//to account for self-loops
                    it2 = priordone.find((*it1)->filename());
                    temp += ((it2->second)/double(countOut));
                }
            }
            countOut = 0;
            //find number of outgoing links for itself
            for(set<WebPage*>::iterator it3 = it->first->outgoing_links().begin(); it3 != it->first->outgoing_links().end(); ++it3){
                if(names.find((*it3)->filename()) != names.end()){
                    countOut++;
                }
            }
            countOut++;
            
            it2 = priordone.find(it->first->filename());
            temp += (it2->second)/double(countOut);
            
            temp *= (1 - eps);
            temp += (eps/double(expanded.size()));
            it2 = temp_result.find(it->first->filename());
            it2->second = temp;
        }
        
        for(map<string,double>::iterator it = priordone.begin(); it != priordone.end(); ++it){
            map<string,double>::iterator exchange = temp_result.find(it->first);
            it->second = exchange->second;
        }
    }
    for(vector<pair<WebPage*, double>>::iterator it = result.begin(); it != result.end(); ++it){
        double toAdd = priordone.find(it->first->filename())->second;
        it->second = toAdd;
    }
    return result;
}

