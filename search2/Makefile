all: search-shell crawl

search-shell: search-shell.cpp searcheng.cpp searchui.cpp webpage.cpp util.cpp combiners.cpp handler.cpp cmdhandler.cpp md_parser.cpp txt_parser.cpp
	g++ -g -Wall  --std=c++11 search-shell.cpp searcheng.cpp searchui.cpp webpage.cpp util.cpp combiners.cpp handler.cpp cmdhandler.cpp md_parser.cpp txt_parser.cpp -o search-shell
	
crawl: crawl.cpp md_parser.cpp txt_parser.cpp util.cpp webpage.cpp 
	g++ -g -Wall  --std=c++11 crawl.cpp md_parser.cpp txt_parser.cpp util.cpp webpage.cpp -o crawl

clean:
	rm -f *.o search-shell crawl
	
