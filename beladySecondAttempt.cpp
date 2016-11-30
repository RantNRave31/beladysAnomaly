#include <iostream>
#include <deque>
#include <vector>
#include <random>

std::vector<std::vector<int> > generateSequences(){
 srand(time(NULL));
 std::vector<std::vector<int> > v;
 for (int i = 0; i < 100; i++){
  std::vector<int> subV;
  for(int j = 0; j < 1000; j++){
   subV.push_back(rand() % 250);
  }
  v.push_back(subV);
 }
return v;
}

bool check(int sequenceItem, std::deque<int> q){
 for(auto&& item : q){
  if(item == sequenceItem){
   return false;
  }
 }
 return true;
}

std::vector<std::vector<int> > runSimulation(std::vector<std::vector<int> > sequences){
 std::vector<std::vector<int> > results;
 for(unsigned int sequenceCounter = 0; sequenceCounter < 100; sequenceCounter++){
 auto mySequence = sequences.at(sequenceCounter);
 std::deque<int> q;
  std::vector<int> sequencePageFaults; 
  for(unsigned int frame = 1; frame <= 100; frame++){
   //What am I doing?
   //check whether the value is already on the queue.
   //if it is, miss is false
   //if it isn't miss is true
   //if miss is false: do nothing, the page is already loaded
   //if miss is true: check whether the queue is full
   //if the queue is full: page fault!! pop off the first element, enqueue the current one
   //if the queue is not full: enqueue the element 
   int pageFaultCounter = 0;
   for(unsigned int sequenceIterator = 0; sequenceIterator < mySequence.size(); sequenceIterator++){
    auto miss = check(mySequence.at(sequenceIterator), q);
    if(miss){
     if(q.size() >= frame){
//      std::cout << "page fault" << std::endl;
      pageFaultCounter++;
      q.pop_front();
      q.push_back(mySequence.at(sequenceIterator));
     }
     else{
      q.push_back(mySequence.at(sequenceIterator));
     }
    }
   }
   sequencePageFaults.push_back(pageFaultCounter);
   pageFaultCounter = 0;
  }
 results.push_back(sequencePageFaults);
 }
return results;
}

void displayResults(std::vector<std::vector<int> > r) {
	int anomalyCounter = 0;
	std::cout << "Length of memory reference string: 1000" << std::endl;
	std::cout << "Frames of physical memory: 100" << std::endl;
	for (unsigned int i = 0; i < r.size(); i++) {
		//
		for (unsigned int j = 0; j < (r.at(0).size() - 1); j++) {
			if (r.at(i).at(j) < r.at(i).at(j + 1)) {
				anomalyCounter++;
				std::cout << "Anomaly Discovered!" << std::endl;
				std::cout << "\tSequence :" << (i + 1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(i).at(j) << " @ Frame Size: " << (j + 1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(i).at(j + 1) << " @ Frame Size: " << (j + 2) << std::endl << std::endl;
			}
		}
	}
	std::cout << "Anomaly detected " << anomalyCounter << " times." << std::endl;
}
int main(){
 // make a vector of vectors to hold 100 strings of 1000 length
 //insert 100 strings of 1000 length with random numbers between 0 and 250
 std::vector<std::vector<int> > sequences = generateSequences();
 // for each of the 100 strings: simulate frames from size 1 to size 100 in the form of a queue
 //if it isn't already there, enqueue each element, and kick out the first in!  
 auto res = runSimulation(sequences);
 displayResults(res); 
 return 0;
}
