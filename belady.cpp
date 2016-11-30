#include <iostream>
#include <queue>
#include <deque>
#include <random>
#include <thread>
#include <time.h>

std::deque<int> generateRandomPageSequence()
{
	rand();
		std::deque<int> a;
		for (int j = 0; j < 1000; j++) {
			a.push_back(rand() % 250);
		}
	
	return a;
}

bool checkForMiss(std::deque<int> q, int n) {
	for (auto e : q) {
		if (e == n) {
			return false;
		}
	}
	return true;
}

int getMisses(std::deque<int> &seq, unsigned int sequence) {
	int misses = 0;
	std::deque<int> qu;
	qu.clear();
		for (unsigned int j = 0; j < seq.size(); j++) {
			if (qu.size() > sequence) {
				bool miss = checkForMiss(qu, seq.at(j));
				if (miss) { 
					misses++;
				}
				qu.pop_front();
			}
			qu.push_back(seq.at(j));
		}
		//std::cout << misses << std::endl;
	return misses;
}

std::deque<int> getResults(std::deque<int> s) {
	std::deque<int> res;
		for (unsigned int j = 0; j < 100; j++) {
			res.push_back(getMisses(s, j));
		}
	return res;
}

void displayResults(std::deque<int> r) {
	int anomalyCounter = 0;
		//
		for (unsigned int j = 0; j < (r.size()-1); j++) {
			if (r.at(j) < r.at(j + 1)) {
				anomalyCounter++;
				std::cout << "Anomaly Discovered!" << std::endl;
				std::cout << "\tSequence :" << (j+1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(j) << " @ Frame Size: " << (j+1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(j + 1) << " @ Frame Size: " << (j + 2) << std::endl << std::endl;
			}
			else{
			 std::cout <<(j+1)<< ": " <<  r.at(j) << " > " << r.at(j+1) << std::endl;
			}

	}
	std::cout << "Length of memory reference string: 1000" << std::endl;
	std::cout << "Frames of physical memory: 100" << std::endl;
	std::cout << "Anomaly detected " << anomalyCounter << " times." << std::endl;
}

int main() {
	srand(time(NULL));
	auto sequences = generateRandomPageSequence();
	auto results = getResults(sequences);
	displayResults(results);
}
