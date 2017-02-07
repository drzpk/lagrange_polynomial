/**
Program pozwala na wyznaczenie wspolczynników wielomianu
za pomoca interpolacji wielomianowej metoda wielomianu Lagrange'a.

Aby obliczyć współczynniki wielomianu n-tego stopnia, należy podać n+1 węzłów
w następującym formacie:
(x_1;y_1)(x_2;y_2)...(x_n;y_n)

Autor: Dominik Rzepka
*/

#include "stdafx.hpp"
//#include "params.hpp"
#include "lagrange.hpp"

#define PARAM_

void print_usage(char* application_name) {
	std::cout << "Program pozwala za wyznaczenie współczynników wielomianu "
		<< "za pomoca interpolacji wielomianowej metoda wielomianu Lagrange'a.\n"
		<< "  Użycie programu: " << application_name << " (x;y)(x;y)...\n"
		<< "Dla obliczenia współczynników wielomianu n-tego stopnia należy podać n+1 węzłów";
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	if (argc < 2) {
		std::cout << "niepoprawna składnia. Aby uzyskać pomoc, napisz "
			<< argv[0] << " -h";
		return 1;
	}

	//wyświetlanie tekstu pomocy
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-h")) {
			print_usage(argv[0]);
			return 0;
		}
	}

	//obecnie nieużywane
	//Params params(false);

	//parsowanie węzłów
	Nodes nodes;
	if (!nodes.parse(std::string(argv[1]))) {
		std::cerr << "błąd przetwarzania węzłów: " << nodes.getErrorDesc();
		return 1;
	}
	std::vector<Node*> final_nodes = nodes.getNodes();

	//wygenerowanie współczynników
	Lagrange lagrange(std::move(final_nodes));
	lagrange.compute();
	std::vector<double> indices = lagrange.getIndices();

	//prezentacja wyniku
	char letter = 'a';
	std::cout << "Znalezione współczynniki:\n";
	for (double index : indices)
		std::cout << letter++ << ": " << std::setprecision(6) << index << std::endl;

	return 0;
}