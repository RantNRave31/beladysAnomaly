#include <iostream>
#include <queue>
#include <deque>
#include <random>
#include <thread>
#include <time.h>

std::deque<std::deque<int> > generateRandomPageSequence()
{
	rand();
	std::deque<std::deque<int> > v;
	for (int i = 0; i < 100; i++) {
		std::deque<int> a;
		for (int j = 0; j < 1000; j++) {
			a.push_back(rand() % 250);
		}
		v.push_back(a);
	}
	return v;
}

bool checkForMiss(std::deque<int> q, int n) {
	for (auto e : q) {
		if (e == n) {
			return false;
		}
	}
	return true;
}

int getMisses(std::deque<std::deque<int> > &seq, unsigned int sequence, unsigned int frameSize) {
	int misses = 0;
	std::deque<int> qu;
	qu.clear();
		for (unsigned int j = 0; j < seq.at(sequence).size(); j++) {
			if (qu.size() > frameSize) {
				bool miss = checkForMiss(qu, seq.at(sequence).at(j));
				if (miss) { 
					misses++;
				}
				qu.pop_front();
			}
			qu.push_back(seq.at(sequence).at(j));
		}
	return misses;
}

std::deque<std::deque<int> > getResults(std::deque<std::deque<int> > s) {
	std::deque<std::deque<int> > res;
	for (unsigned int i = 0; i < 100; i++) {
		std::deque<int> subRes;
		for (unsigned int j = 0; j < 100; j++) {
			subRes.push_back(getMisses(s, j, i));
		}
		res.push_back(subRes);
	}
	return res;
}

void displayResults(std::deque<std::deque<int> > r) {
	int anomalyCounter = 0;
	std::cout << "Length of memory reference string: 1000" << std::endl;
	std::cout << "Frames of physical memory: 100" << std::endl;
	for (unsigned int i = 0; i < r.size(); i++) {
		//
		for (unsigned int j = 0; j < (r.at(0).size()-1); j++) {
			if (r.at(i).at(j) < r.at(i).at(j + 1)) {
				anomalyCounter++;
				std::cout << "Anomaly Discovered!" << std::endl;
				std::cout << "\tSequence :" << (i+1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(i).at(j) << " @ Frame Size: " << (j+1) << std::endl;
				std::cout << "\tPage Faults: " << r.at(i).at(j + 1) << " @ Frame Size: " << (j + 2) << std::endl << std::endl;
			}
		}
	}
	std::cout << "Anomaly detected " << anomalyCounter << " times." << std::endl;
}

int main() {
	srand(time(NULL));
	auto sequences = generateRandomPageSequence();
	auto results = getResults(sequences);
	displayResults(results);
}


/*
 *
 * notes from class on 11/28
 *
 * Anomaly only occurs on FIFO
 *
 * break down{
 * 1000 touches of memory, these touches select numbers between 1 and 250
 * Simulate that 1000 length string over 1 frame of memory 
 * Simulate same string over two ... three ... four ... 100 count page faults that occur. 
 * ONLY ONE STRING :)
 * }
 *
 */
