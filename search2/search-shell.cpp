#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "searchui.h"
#include "md_parser.h"
#include "txt_parser.h"
#include "cmdhandler.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Must provide an index file" << endl;
        return 1;
    }
    TXTParser txtparser;
    MDParser mdparser;
    // Declare the search engine
    SearchEng seng(&txtparser);
    // Create and register appropriate parsers for .md and .txt files
    
    seng.register_parser("md", &mdparser);
    seng.register_parser("txt", &txtparser);
    // Create the SearchUI object
    SearchUI ui(&seng);

    // Create and add appropriate Command Handlers to the SearchUI
    QuitHandler* qh = new QuitHandler();
    PrintHandler* ph = new PrintHandler();
    IncomingHandler* ih = new IncomingHandler();
    OutgoingHandler* ogh = new OutgoingHandler();
    AndHandler* ah = new AndHandler();
    OrHandler* oh = new OrHandler();
    DiffHandler* dh = new DiffHandler();
    PRAndHandler* pra = new PRAndHandler();
    PROrHandler* pro = new PROrHandler();
    
//    PrintHandler* qh = new PrintHandler(new QuitHandler(new IncomingHandler(new OutgoingHandler(new AndHandler(new OrHandler(new DiffHandler(NULL)))))));
    
    ui.add_handler(qh);
    ui.add_handler(ph);
    ui.add_handler(ih);
    ui.add_handler(ogh);
    ui.add_handler(ah);
    ui.add_handler(oh);
    ui.add_handler(dh);
    ui.add_handler(pra);
    ui.add_handler(pro);
    
   

    // ------------------------------------------------------------------------

    try {
        seng.read_pages_from_index(argv[1]);
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }

    bool result;
    if (argc == 2)
    {
        result = ui.run(cin, cout);

    }
    else if (argc == 3) {
        ifstream in_file(argv[2]);
        result = ui.run(in_file, cout);
    }
    else  {
        ifstream in_file(argv[2]);
        ofstream out_file(argv[3]);
        result = ui.run(in_file, out_file);
    }
    // You may add cleanup code here though you likely do not
    // need to.
    
    return result;
}
