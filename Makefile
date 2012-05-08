all:
	g++ -Wall -pedantic projekt.cpp -o projekt
clean:
	rm -rf *o *~ *.*~ *.*gch *.txt *.log
