#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <thread>
#include <time.h>

std::vector<std::vector<int> > generateRandomPageSequence()
{
	rand();
	std::vector<std::vector<int> > v;
	for (int i = 0; i < 100; i++) {
		std::vector<int> a;
		for (int j = 0; j < 1000; j++) {
			a.push_back(rand() % 250);
		}
		v.push_back(a);
	}
	return v;
}

bool checkForMiss(std::vector<int> q, int n) {
	for (auto e : q) {
		if (e == n) {
			return false;
		}
	}
	return true;
}

int getMisses(std::vector<std::vector<int> > &seq, unsigned int sequence, unsigned int frameSize) {
	int misses = 0;
	std::vector<int> qu;
	qu.clear();
		for (unsigned int j = 0; j < seq.at(sequence).size(); j++) {
			if (qu.size() > frameSize) {
				bool miss = checkForMiss(qu, seq.at(sequence).at(j));
				if (miss) { 
					misses++;
				}
				qu.pop_back();
			}
			qu.push_back(seq.at(sequence).at(j));
		}
	return misses;
}

std::vector<std::vector<int> > getResults(std::vector<std::vector<int> > s) {
	std::vector<std::vector<int> > res;
	for (unsigned int i = 0; i < 100; i++) {
		std::vector<int> subRes;
		for (unsigned int j = 0; j < 100; j++) {
			subRes.push_back(getMisses(s, j, i));
		}
		res.push_back(subRes);
	}
	return res;
}

void displayResults(std::vector<std::vector<int> > r) {
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
