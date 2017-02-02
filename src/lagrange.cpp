#include "lagrange.hpp"

Lagrange::Lagrange(std::vector<Node*>&& nodes) {
	if (nodes.size() < 2)
		throw std::invalid_argument("liczba węzłów nie może być mniejsza, niż 2");

	this->nodes = nodes;
}

void Lagrange::compute() {
	//wyczyszczenie wyniku, w razie ponownego wykonywania metody
	indices.clear();

	//stworzenie głównego chunka i dodanie do niego elementu,
	//aby mnożenie było możliwe
	Chunk chunk = new nChunk;
	Unit* base_unit = new Unit;

	//obliczenie wielomianu Lagrange'a
	//segmenty L0 + L1 + ...
	size_t len = nodes.size();
	for (size_t i = 0; i < len; i++) {
		Chunk mul = multiply(i);
		for (auto unit : *mul)
			chunk->push_back(unit);
	}

	//redukcja wyrazów podobnych
	chunk = reduce(chunk);

	//uporządkowanie wielomianu
	std::sort(chunk->begin(), chunk->end(), unitComparator);

	//debug
	dumpChunk("Finalny chunk", chunk);

	len = chunk->size();
	for (size_t i = 0; i < len; i++)
		indices.push_back(chunk->at(i)->value);
}

std::vector<float> Lagrange::getIndices() const {
	return indices;
}

Chunk Lagrange::multiply(size_t index) {
	//zwraca chunk z pojedynczej funkcji Lagrange'a

	//stworzenie głównego chunka
	Chunk chunk = new nChunk;
	Unit* base_unit = new Unit;
	base_unit->value = 1.f;
	chunk->push_back(base_unit);

	size_t len = nodes.size();

	for (size_t j = 0; j < len; j++) {
		//pominięcie zgodnie z definicją
		if (j == index)
			continue;

		//mianownik
		int denominator = nodes[index]->x - nodes[j]->x;

		//jednostka z iksem
		Unit* x_unit = new Unit;
		x_unit->value = 1.f / (float) denominator;
		x_unit->x = true;
		x_unit->power = 1;

		//wolny wyraz
		Unit* app_unit = new Unit;
		app_unit->value = -nodes[j]->x / denominator;

		//stworzenie nowego chunka
		Chunk multiplier = new nChunk;
		multiplier->push_back(x_unit);
		multiplier->push_back(app_unit);

		//wymnożenie ze sobą dwóch wielomianów
		chunk = getChunk(chunk, multiplier);
	}

	//pomnożenie przez y
	Unit* y_unit = new Unit;
	y_unit->value = nodes[index]->y;
	Chunk multiplier = new nChunk;
	multiplier->push_back(y_unit);
	chunk = getChunk(chunk, multiplier);

	return chunk;
}

Chunk Lagrange::getChunk(Chunk chunk_1, Chunk chunk_2) {
	//mnożenie chunków
	Chunk new_chunk = new nChunk;
	for (size_t i = 0; i < chunk_1->size(); i++) {
		for (size_t j = 0; j < chunk_2->size(); j++) {
			Unit* new_unit = new Unit;
			new_unit->value = chunk_1->at(i)->value * chunk_2->at(j)->value;
			new_unit->x = chunk_1->at(i)->x || chunk_2->at(j)->x;
			new_unit->power = chunk_1->at(i)->power + chunk_2->at(j)->power;

			//dodanie wyrazu do chunka
			new_chunk->push_back(new_unit);
		}
	}

	size_t tmp1 = chunk_1->size();
	size_t tmp2 = chunk_2->size();

	//usunięcie niepotrzebnych chunków
	deleteChunk(chunk_1);
	deleteChunk(chunk_2);

	return reduce(new_chunk);
}

Chunk Lagrange::reduce(Chunk chunk) {
	//redukcja wyrazów podobnych
	Chunk new_chunk = new nChunk;

	//może być maksymalnie tyle stopni, co wyrazów
	size_t len = chunk->size();

	Unit* new_unit = new Unit;
	bool changed = false;

	//i - stopnie wielomianu
	//j - elementy chunka
	for (size_t i = 0; i < len; i++) {
		//ustawienie stopnia wyrazu
		new_unit->power = i;
		changed = false;

		for (size_t j = 0; j < len; j++) {
			//dodawaj tylko pasujące stopnie wielomianów
			if (chunk->at(j)->power != i)
				continue;

			new_unit->value += chunk->at(j)->value;
			changed = true;
		}

		if (changed) {
			new_chunk->push_back(new_unit);
			new_unit = new Unit;
		}
	}

	//usuń niewykorzystaną jednostkę
	if (!changed)
		delete new_unit;

	return new_chunk;
}

void Lagrange::deleteChunk(Chunk chunk) {
	for (auto c : *chunk)
		delete c;
	delete chunk;
}

void Lagrange::dumpChunk(const std::string& title, Chunk chunk) {
#ifdef DEBUG_INFO
	std::cout << title << ":\n";
	for (auto c : *chunk) {
		std::cout << c->value
			<< (c->power > 0 ? ("x^" + c->power) : "") << std::endl;
	}
#endif
}

bool unitComparator(Unit* unit_1, Unit* unit_2) {
	return unit_1->power > unit_2->power;
}