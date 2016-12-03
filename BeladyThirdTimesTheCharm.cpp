#include <unordered_map>
#include <vector>
#include <cassert>
#include <queue>
#include <iostream>

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

bool isInMemory(int value, std::unordered_map<int, int> & memory){
 auto f = memory.find(value);
 if(f != memory.end()){
  return true;
 }
 else {
  return false;
 }
}

int getFramePageFaults(int i, std::vector<int>& sequence){
 assert(sequence.size() == 1000);
 std::queue<int> que;
 std::unordered_map<int, int> memory;
 int pageFaults = 0;
 for(int j = 0; j < 1000; j++){
  if(isInMemory(sequence.at(j), memory)){
   j++;  
  }
  else if(que.size() >= i){
   pageFaults++;
   memory.erase(que.front());
   que.pop();
   memory.insert({j, sequence.at(j)});
   que.push(sequence.at(j));
  }
  else{
   memory.insert({j, sequence.at(j)});
   que.push(sequence.at(j));
  }
 }
 return pageFaults;
}

std::vector<int> populateSingleSequencePageFaults(std::vector<int> &sequence){
 std::vector<int> thisSequence;
 for(int i = 1; i <= 100; i++){
  thisSequence.push_back(getFramePageFaults(i, sequence)); 
 }
 return thisSequence;
}

std::vector<std::vector<int> > populatePageFaults(std::vector<std::vector<int> >& sequences){
 std::vector<std::vector<int> > results;
 for(int i = 0; i < 100; i++){
  assert(!sequences.at(i).empty());
  auto thisSequence = sequences.at(i);
  assert(thisSequence.size() == 1000);
  results.push_back(populateSingleSequencePageFaults(thisSequence));
 }
 return results;
}

void printResults(std::vector<std::vector<int> > & results){
 int anomalyCounter = 0;
 for(int i = 0; i < 100; i++){
  for(int j = 0; j < 99; j++){
   if(results.at(i).at(j) < results.at(i).at(j+1)){
    std::cout << "Anomaly Discovered!" << std::endl;
    anomalyCounter++;
    std::cout << "\tSequence: " << (i+1) << std::endl;
    std::cout << "\tPage Faults: " << results.at(i).at(j) << "@ Frame Size: " << (j + 1) << std::endl;
    std::cout << "\tPage Faults: " << results.at(i).at(j + 1) << "@ Frame Size: " << (j + 2) << std::endl;
   }
  }
 }
 std::cout << "Anomaly Discovered " << anomalyCounter << " times." << std::endl;
}

int main(){
auto sequences = generateSequences();
auto results = populatePageFaults(sequences);
printResults(results); 
return 0;
}
