/**
Program pozwala na wyznaczenie wspolczynników wielomianu
za pomoca interpolacji wielomianowej metoda wielomianu Lagrange'a.

Aby obliczyć współczynniki wielomianu n-tego stopnia, należy podać n+1 węzłów
w następującym formacie:
(x_1;y_1)(x_2;y_2)...(x_n;y_n)

Autor: Dominik Rzepka
*/

#include "stdafx.hpp"
#include "params.hpp"
#include "lagrange.hpp"
#include "table.hpp"

#define PARAM_NODES			0
#define PARAM_DELTA			1
#define PARAM_ITERATIONS	2
#define PARAM_SCIENTIFIC	3
#define PARAM_PRECISION		4
#define PARAM_OUTPUT		5
#define PARAM_HELP			6
#define PARAM_VERSION		7

#define VERSION				"1.1"

void print_usage(char* application_name, Params& params) {
	std::cout << "Program pozwala za wyznaczenie współczynników wielomianu "
		<< "za pomoca interpolacji wielomianowej metoda wielomianu Lagrange'a.\n"
		<< "  Użycie programu: " << application_name << " [-dioh] -k (x;y)(x;y)...\n"
		<< "Dla obliczenia współczynników wielomianu n-tego stopnia należy podać n+1 węzłów\n"
		<< "  Dostępne parametry:\n" << params.printParams(4) << "\n";
}

void print_wrong_syntax(char* application_name) {
	std::cerr << "niepoprawna składnia. Aby uzyskać pomoc, napisz "
		<< application_name << " -h\n";
}

void single_mode(std::vector<Node*>& nodes) {
	//wygenerowanie współczynników
	Lagrange lagrange(nodes);
	lagrange.compute();
	std::vector<double> indices = lagrange.getIndices();

	//prezentacja wyniku
	char letter = 'a';
	std::cout << "Znalezione współczynniki:\n";
	for (double index : indices)
		std::cout << letter++ << ": " << std::setprecision(6) << index << std::endl;
}

bool will_fit_in_console(size_t width) {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	return info.srWindow.Right - info.srWindow.Left + 1 >= (int)width;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    return w.ws_col >= width;
#endif
}

int table_mode(std::vector<Node*>& nodes, size_t iterations, Node* delta, bool scientific, bool output, int precision) {
	Table table(nodes);
	if (!table.setDelta(delta) || !table.setRepetitions(iterations)
		|| (precision > -1 && !table.setPrecision((size_t)precision))) {
		std::cerr << "Błąd tabeli: " << table.getError();
		return 1;
	}
	table.forceScientificNotation(scientific);
	std::stringstream ss = table.generate();

	//sprawdzenie, czy wynik może zostać wyświetlony
	size_t line_width = table.getLineWidth();
	if (!output) {
		if (will_fit_in_console(line_width))
			std::cout << ss.str();
		else {
			std::cerr << "Tabela jest za szeroka, aby zmieścić się w oknie konsoli. "
				<< "Poszerz okno lub użyj parametru -o, aby zapisać wynik do pliku\n";
			return -1;
		}
	}
	else {
		std::ofstream file;
		file.open("output.txt", std::ios::out | std::ios::trunc);
		if (!file.good()) {
			std::cerr << "Błąd: nie udało się otworzyć pliku\n";
			return 1;
		}

		file << ss.str();
		file.close();
		std::cout << "Wynik został zapisany do pliku\n";
	}

	return 0;
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	if (argc < 2) {
		print_wrong_syntax(argv[0]);
		return 1;
	}

	Params params(false);
	params.addParameter(PARAM_NODES, "n", "nodes", "węzły wielomianu", true);
	params.addParameter(PARAM_DELTA, "d", "delta", "delta ostatniego węzła", true);
	params.addParameter(PARAM_ITERATIONS, "i", "iterations", "liczba iteracji", true);
	params.addParameter(PARAM_SCIENTIFIC, "s", "scientific", "pokaż tabelę w notacji naukowej", false);
	params.addParameter(PARAM_PRECISION, "P", "precision", "ustawia precyzję znaków", true);
	params.addParameter(PARAM_OUTPUT, "o", "output", "zapisz wyjście do pliku", false);
	params.addParameter(PARAM_HELP, "h", "help", "wyświetla ten tekst pomocy", false);
	params.addParameter(PARAM_VERSION, "v", "version", "wyświetla informacje o wersji", false);

	if (!params.parseParams(argc, argv)) {
		std::cerr << "Błąd: " << params.getErrorDescription();
		return 1;
	}

	//wyświetl pomoc
	if (params.hasParameter(PARAM_HELP)) {
		print_usage(argv[0], params);
		return 0;
	}

	//wyświetl informacje o wersji
	if (params.hasParameter(PARAM_VERSION)) {
		std::cout << "lagrange_polynomial, wersja " << VERSION
			<< "\nstworzone przez: Dominik Rzepka\n";
		return 0;
	}

	//sprawdź, czy jest parametr -n
	if (!params.hasParameter(PARAM_NODES)) {
		print_wrong_syntax(argv[0]);
		return 1;
	}

	//parsowanie węzłów
	Nodes nodes;
	if (!nodes.parse(params.getString(PARAM_NODES))) {
		std::cerr << "Błąd przetwarzania węzłów: " << nodes.getErrorDesc() << "\n";
		return 1;
	}
	std::vector<Node*> final_nodes = nodes.getNodes();

	//sprawdzenie, czy dla jednego x nie przyporządkowano więcej,
	//niż jeden y
	std::set<double> function_params;
	for (auto node : final_nodes) {
		if (function_params.count(node->x)) {
			std::cerr << "Dla jednego x nie może być zdefiniowane więcej, niż jeden y!\n";
			return 1;
		}
		function_params.insert(node->x);
	}

	if (!params.hasParameter(PARAM_DELTA) && !params.hasParameter(PARAM_ITERATIONS)) {
		//tryb jednego wielomianu
		single_mode(final_nodes);
	}
	else {
		//tryb tablicy
		if (!params.hasParameter(PARAM_DELTA)) {
			std::cerr << "Nie podano delty (-d)\n";
			return 1;
		}
		if (!params.hasParameter(PARAM_ITERATIONS)) {
			std::cerr << "Nie podano liczby iteracji (-i)\n";
			return 1;
		}

		//węzeł delta
		Nodes delta_node;
		if (!delta_node.parse(params.getString(PARAM_DELTA))) {
			std::cerr << "Błąd delty: " << delta_node.getErrorDesc() << "\n";
			return 1;
		} 
		std::vector<Node*> delta_nodes = delta_node.getNodes();
		if (delta_nodes.size() != 1) {
			std::cerr << "Musi być podana dokładnie jedna delta\n";
			return 1;
		}
		
		//liczba iteracji
		int iterations = params.getInt(PARAM_ITERATIONS);
		if (iterations < 1) {
			std::cerr << "Liczba iteracji nie może być mniejsza, niż 1\n";
			return 1;
		}

		//notacja naukowa
		bool scientific = params.hasParameter(PARAM_SCIENTIFIC);

		int precision = -1;
		if (params.hasParameter(PARAM_PRECISION)) {
			precision = params.getInt(PARAM_PRECISION);
			if (precision < 0) {
				std::cerr << "Prezycja nie może być mniejsza, niż 0\n";
				return 1;
			}
		}

		//wyjście do pliku
		bool output = params.hasParameter(PARAM_OUTPUT);

		//uruchom tryb tablicy
		return table_mode(final_nodes, (size_t)iterations, delta_nodes[0], scientific, output, precision);
	}

	return 0;
}
