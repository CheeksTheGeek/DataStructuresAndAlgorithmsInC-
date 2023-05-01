all: test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp
	g++ -std=c++11 -O3 test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp

debug: test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp
	g++ -std=c++11 -Wextra -Wall -O3 -Og -g test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp

clean:
	rm a.out

nowarn: test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp
	g++ -std=c++11 -O3 test_main.cpp power_grid_graph.cpp edges_priority_queue.cpp

nwrun: nowarn
	./a.out

tar: Makefile illegal_exception.hpp power_grid_graph.cpp power_grid_graph.hpp test_main.cpp edges_priority_queue.cpp c34sharm_design_p4.pdf design_document.tex PowerGridGraph.puml PowerGridGraph.png
	tar -cvzf c34sharm_p4.tar.gz Makefile illegal_exception.hpp power_grid_graph.cpp power_grid_graph.hpp test_main.cpp power_grid_graph.hpp edges_priority_queue.cpp c34sharm_design_p4.pdf design_document.tex PowerGridGraph.puml PowerGridGraph.png
	mkdir temp_test_cpp
	tar -xf c34sharm_p4.tar.gz -C temp_test_cpp
	cd temp_test_cpp
	make
	cd ..
	rm -rf temp_test_cpp
	
test: tar
	mv c34sharm_p4.tar.gz ../ece250-testcases

untar: c34sharm_p4.tar.gz
	mkdir temp_test_cpp
	tar -xf c34sharm_p4.tar.gz -C temp_test_cpp
	cd temp_test_cpp
	ls

untarClean:
	cd ..
	rm -rf temp_test_cpp