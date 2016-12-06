#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<random>
#include<time.h>

void printAnomaly(int i, int j, int faultStorage, int faultCounter){
 std::cout << "Anomaly Discovered" << std::endl;
 std::cout << "Sequence:" << i << std::endl;
 std::cout << "\tPage Faults:" << faultStorage << " @ Frame Size: " << (j) << std::endl;
 std::cout << "\tPage Faults:" << faultCounter << " @ Frame Size: " << j+1 << std::endl << std::endl;
}

int main(){

// anomalyCounter holds the total number of anomalies 
 int anomalyCounter = 0;
//seeding random
 srand(time(NULL));

//for 100 sequences
 for(int i = 0; i < 100; i++){
 //generate a sequence
  std::vector<int> sequence;
  for(int g = 0; g < 1000; g++){
   sequence.push_back(rand() %250);
  }

//faultCounter should hold the number of page faults on the current iteration
  int faultCounter = 0;

//faultStorage should hold the number of page faults on the previous iteration 
//It is set to 9999 so that on the very first iteration it will be greater than
//the faultCounter iterator
  int faultStorage = 9999;

//for page sizes from 1 to 100
  for(int j = 1; j < 101; j++){

//Sanity check: making sure faultStorage is going to be the larger value on the first iteration
   if(j == 1){
    faultStorage = 9999;
   }

//Keep the current values in a hash table
   std::unordered_map<int,int> memory;

//Impliment FIFO with a std::queue
   std::queue<int> q;

//For every number in the sequence
   for(int h = 0; h < 1000; h++){

//check whether it is in memory
    auto found = memory.find(sequence.at(h));

//if it is NOT in memory,
    if(found == memory.end()){

//and if the size of the queue is greater than the number of pages
    if(q.size() >= j){

//delete the first element from memory
      memory.erase(q.front());

//Pop the first element off of the queue
      q.pop();
     }

//(we fall back into scope of the first if statement) If it is not in memory, insert that element of the sequence into memory
     memory.insert(std::make_pair(h, sequence.at(h)));

//push it onto the queue
     q.push(sequence.at(h));

//any time we have to insert something into memeory, that counts as a page fault
     faultCounter++;
    }
   }

//If the number of faults from the previous iteration exceeds that of the current iteration,
   if(faultStorage > faultCounter){

//An anomaly happened
    printAnomaly(i, j, faultStorage, faultCounter);
    anomalyCounter++;
   }

//faultStorage gets fault Counter
   faultStorage = faultCounter;

//faultCounter is zero for the next round
   faultCounter = 0;

//clear out the queue
   std::queue<int> empty;
   std::swap(q,empty);

//clear out memeory 
   memory.clear();

//go to the next iteration
  }

//this is more tidying than anything, but clear the sequence
 sequence.clear();

//start again.
 }
 std::cout << anomalyCounter << std::endl;
 return 0;
}
   
