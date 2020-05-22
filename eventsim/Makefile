all: eventsim

eventsim: derived_events.cpp eventsim.cpp input_reader.cpp streetgrid.cpp 
	g++ -g -Wall  --std=c++11 derived_events.cpp eventsim.cpp input_reader.cpp streetgrid.cpp -o eventsim

clean:
	rm -f *.o eventsim
	
