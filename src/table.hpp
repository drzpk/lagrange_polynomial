#pragma once

#include "stdafx.hpp"
#include "lagrange.hpp"


// Klasa odpowiada za rysowanie tabeli zależności
// między zmieniającym się węzłem wielomianu
// a poszczególnymi współczynnikami.
class Table {
private:
	static const size_t CELL_PADDING = 1;

	std::vector<Node*> nodes;
	Node* delta;
	size_t repetitions;
	bool forceScientific;
	size_t precision;
	size_t lineWidth;
	std::string errorDesc;
public:
	// Tworzy nowy obiekt klasy Table
	// Params:
	// nodes - węzły jako źródło tabeli
	Table(const std::vector<Node*>& nodes);

	// Ustawia deltę, tzn, jak będzie się zmieniał
	// ostatni węzeł z listy podanej w konstruktorze.
	// Params:
	// delta - delta ostatniego węzła
	// Returns:
	// czy delta jest prawidłowa
	bool setDelta(Node* delta);

	// Ustawia ilość powtórzeń w zmianu węzła o deltę.
	// Params:
	// repetitions - ilość powtórzeń
	// Returns:
	// czy liczba powtórzeń jest prawidłowa
	bool setRepetitions(size_t repetitions);

	// Ustawia, czy tablica ma wymuszać zapisywanie
	// wyników w postaci notacji naukowej.
	void forceScientificNotation(bool state);

	// Ustawia precyzję znaków.
	// Params:
	// precision - precyzja znaków
	// Returns:
	// czy precyzja jest prawidłowa
	bool setPrecision(size_t precision);

	// Generuje i zwraca tabelę.
	std::stringstream generate();

	// Zwraca szerokość pojedynczej linii tabeli
	// po wygenerowaniu.
	size_t getLineWidth() const;

	// Zwraca opis ostatniego błędu.
	std::string getError() const;

private:
	std::string getValue(double value);
	std::string getValue(Node* node);
	std::string getCentered(const std::string& str, size_t width);
};