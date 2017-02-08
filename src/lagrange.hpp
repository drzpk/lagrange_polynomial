#pragma once

#include "stdafx.hpp"
#include "node.hpp"


struct Unit;

typedef std::vector<Unit*> nChunk;
typedef nChunk* Chunk;

// Klasa służąca do obliczania współczynników wielomianu
// n-tego stopnia.
class Lagrange {
private:
	std::vector<Node*> nodes;
	std::vector<double> indices;
public:
	// Tworzy nowy obiekt klasy Lagrange.
	// Jeśli liczba węzłów jest mniejsza niż 2,
	// generowany jest wyjątek.
	// Params:
	// nodes - węzły wielomianu
	Lagrange(std::vector<Node*>& nodes);
	Lagrange(const Lagrange&) = delete;
	Lagrange(Lagrange&&) = delete;

	// Oblicza współczynniki funkcji. Współczynniki można 
	// później otrzymać za pomocą metody Lagrange::getIndices.
	void compute();

	// Zwraca wektor zawierający współczynniki obliczone
	// wcześniej za pomocą metody Lagrange::compute.
	// Returns:
	// współczynniki wielomianu
	std::vector<double> getIndices() const;
private:
	Chunk multiply(size_t index);
	Chunk getChunk(Chunk chunk_1, Chunk chunk_2);
	Chunk reduce(Chunk chunk);
	void deleteChunk(Chunk chunk);

	void dumpChunk(const std::string& title, Chunk chunk);
};

struct Unit {
	float value = 0.f;
	//todo: x może być zbędny
	bool x = false;
	int power = 0;
};


static bool unitComparator(Unit* unit_1, Unit* unit_2);