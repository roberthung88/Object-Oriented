#include "cmdhandler.h"
#include "util.h"
#include "../mergesort/msort.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{
    
}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{
    
}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

IncomingHandler::IncomingHandler(){
    
}

IncomingHandler::IncomingHandler(Handler* next) : Handler(next){
   
}

bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string page;
    instr >> page;
    page = conv_to_lower(page);
    WebPageSet result;
    if(eng->retrieve_page(page) == NULL){
        return HANDLER_ERROR;
    }else{
        result = eng->retrieve_page(page)->incoming_links();
        ostr << result.size() << endl;
        for(set<WebPage*>::iterator it = result.begin(); it != result.end(); ++it){
            ostr << (*it)->filename() << endl;
        }
    }
    return HANDLER_OK;
}

OutgoingHandler::OutgoingHandler(){
    
}

OutgoingHandler::OutgoingHandler(Handler* next): Handler(next){

}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string page;
    instr >> page;
    page = conv_to_lower(page);
    WebPageSet result;
    if(eng->retrieve_page(page) == NULL){
        return HANDLER_ERROR;
    }else{
        result = eng->retrieve_page(page)->outgoing_links();
        ostr << result.size() << endl;
        for(set<WebPage*>::const_iterator it = result.begin(); it != result.end(); ++it){
            ostr << (*it)->filename() << endl;
        }
    }
    return HANDLER_OK;
}

AndHandler::AndHandler(){
    
}

AndHandler::AndHandler(Handler* next): Handler(next){
    
}

bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    //read in files
    vector<string> input;
    string temp;
    while(instr >> temp){
        input.push_back(conv_to_lower(temp));
    }
    ANDWebPageSetCombiner a;
    if(input.size() == 0){
        ostr << 0 << endl;
    }else{
        WebPageSet result;
        result = eng->search(input, &a);
        ostr << result.size() << endl;
        for(set<WebPage*>::const_iterator it = result.begin(); it != result.end(); ++it){
            cout << (*it)->filename() << endl;
        }
    }
    return HANDLER_OK;
}

OrHandler::OrHandler(){
    
}

OrHandler::OrHandler(Handler* next): Handler(next){
  
}

bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    //read in files
    vector<string> input;
    string temp;
    while(instr >> temp){
        input.push_back(conv_to_lower(temp));
    }
    ORWebPageSetCombiner a;
    if(input.size() == 0){
        ostr << 0 << endl;
    }else{
        WebPageSet result;
        result = eng->search(input, &a);
        ostr << result.size() << endl;
        for(set<WebPage*>::const_iterator it = result.begin(); it != result.end(); ++it){
            cout << (*it)->filename() << endl;
        }
    }
    return HANDLER_OK;
}

DiffHandler::DiffHandler(){
    
}

DiffHandler::DiffHandler(Handler* next): Handler(next){
   
}

bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";

}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    //read in files
    vector<string> input;
    string temp;
    while(instr >> temp){
        input.push_back(conv_to_lower(temp));
    }
    DiffWebPageSetCombiner a;
    if(input.size() == 0){
        ostr << 0 << endl;
    }else{
        WebPageSet result;
        result = eng->search(input, &a);
        ostr << result.size() << endl;
        for(set<WebPage*>::const_iterator it = result.begin(); it != result.end(); ++it){
            cout << (*it)->filename() << endl;
        }
    }
    return HANDLER_OK;
}

PRAndHandler::PRAndHandler(){
    
}

PRAndHandler::PRAndHandler(Handler* next): Handler(next){
    
}

bool PRAndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRAND";

}

Handler::HANDLER_STATUS_T PRAndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    
    string criteria;
    instr >> criteria;
    
    //read in files
    vector<string> input;
    string temp;
    while(instr >> temp){
        input.push_back(conv_to_lower(temp));
    }

    ANDWebPageSetCombiner a;
    if(input.size() == 0){
        ostr << 0 << endl;
    }else{
        WebPageSet result;
        result = eng->search(input, &a);
        
        //prepare WebPageSet in vector form
        vector<WebPage*> temp_result;
        for(set<WebPage*>::iterator it = result.begin(); it != result.end(); ++it){
            temp_result.push_back(*it);
        }
        
        if(criteria == "n"){
            NObj<pair<WebPage*, double>> comp;
            vector<pair<WebPage*, double>> rank = eng->pageRank(result);
            mergeSort(rank, comp);
            ostr << rank.size() << endl;
            for(vector<pair<WebPage*, double>>::iterator it = rank.begin(); it != rank.end(); ++it){
                cout << it->first->filename() << endl;
            }
        }else if(criteria == "r"){
            vector<pair<WebPage*, double>> rank = eng->pageRank(result);
            //sort result
            PRObj<pair<WebPage*, double>> sortPR;
            mergeSort(rank, sortPR);
            //print
            display_ranked_hits(rank, ostr);
        }
    }
    return HANDLER_OK;
}

PROrHandler::PROrHandler(){
    
}

PROrHandler::PROrHandler(Handler* next): Handler(next){
  
}

bool PROrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PROR";

}

Handler::HANDLER_STATUS_T PROrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string criteria;
    instr >> criteria;
       
    //read in files
    vector<string> input;
    string temp;
    while(instr >> temp){
        input.push_back(conv_to_lower(temp));
    }
    ORWebPageSetCombiner a;
    
    if(input.size() == 0){
        ostr << 0 << endl;
    }else{
        WebPageSet result;
        result = eng->search(input, &a);
        
        //prepare WebPageSet in vector form
        vector<WebPage*> temp_result;
        for(set<WebPage*>::iterator it = result.begin(); it != result.end(); ++it){
            temp_result.push_back(*it);
        }
        
        if(criteria == "n"){
            NObj<pair<WebPage*, double>> comp;
            vector<pair<WebPage*, double>> rank = eng->pageRank(result);
            mergeSort(rank, comp);
            ostr << rank.size() << endl;
            for(vector<pair<WebPage*, double>>::iterator it = rank.begin(); it != rank.end(); ++it){
                cout << it->first->filename() << endl;
            }
        }else if(criteria == "r"){
            vector<pair<WebPage*, double>> rank = eng->pageRank(result);
            //sort result
            PRObj<pair<WebPage*, double>> sortPR;
            mergeSort(rank, sortPR);
            //print
            display_ranked_hits(rank, ostr);
        }
    }
    return HANDLER_OK;
}
