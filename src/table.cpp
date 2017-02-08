#include "table.hpp"

Table::Table(const std::vector<Node*>& nodes) {
	//filtrowanie argumentów
	if (nodes.empty())
		throw new std::invalid_argument("Lista węzłów nie może być pusta");
	
	//inicjalizacja pól
	this->nodes = nodes;
	delta = 0;
	repetitions = 0;
	forceScientific = false;
	precision = 100;
	lineWidth = 0;
}

bool Table::setDelta(Node* delta) {
	if (!delta->x && !delta->y) {
		errorDesc = "delta nie może wynosić 0";
		return false;
	}

	this->delta = delta;
	return true;
}

bool Table::setRepetitions(size_t repetitions) {
	if (repetitions < 1) {
		errorDesc = "liczba powtórzeń musi być większa, niż 0";
		return false;
	}

	this->repetitions = repetitions;
	return true;
}

void Table::forceScientificNotation(bool state) {
	forceScientific = state;
}

bool Table::setPrecision(size_t precision) {
	if (precision > 9) {
		errorDesc = "maksymalna precyzja to 9";
		return false;
	}

	this->precision = precision;
	return true;
}

std::stringstream Table::generate() {
	//sprawdzenie, czy wszysto jest ustawione
	if (!delta || !repetitions)
		return std::stringstream("");

	//lista będzie lepsza do przechowywania współczynników
	std::list<std::vector<double>> values;
	//maksymalna szerokość kolejnych kolumn, zaczynając od
	//kolumny węzła (wliczając padding)
	std::vector<size_t> max_width(nodes.size() + 1);

	//zachowaj ostatni węzeł do generowania tabeli
	Node original_node = *nodes[nodes.size() - 1];

	//generowanie wyników
	for (size_t i = 0; i < repetitions; i++) {
		Lagrange lagrange(nodes);
		lagrange.compute();
		std::vector<double> indices = lagrange.getIndices();
		values.push_back(indices);
		
		//aktualizacja maksymalnej szerokości współczynników
		for (size_t j = 0; j < indices.size(); j++) {
			size_t i_size = getValue(indices[j]).length();
			if (i_size > max_width[j + 1])
				max_width[j + 1] = i_size;
		}

		//aktualizacja maksymalnej szerokości węzła
		size_t n_size = getValue(nodes[nodes.size() - 1]).length();
		if (n_size > max_width[0])
			max_width[0] = n_size;

		//dodanie delty
		nodes[nodes.size() - 1]->x += delta->x;
		nodes[nodes.size() - 1]->y += delta->y;
	}

	//dodaj padding dla wygody
	std::for_each(max_width.begin(), max_width.end(), [](size_t& s) { s += CELL_PADDING * 2; });

	//obliczenie szerokości pojedynczej linii
	//(włącznie ze znakiem nowej linii)
	size_t lp_length = getValue(repetitions).length() + 1; // liczba + kropka
	lineWidth = 3; //separatory + znak nowej linii
	lineWidth += lp_length; //liczba porządkowa
	for (size_t w : max_width)
		lineWidth += w + 1;


	//GENEROWANIE TABELI
	std::stringstream ss;

	//nagłówek tabeli
	ss << "+" << std::setw(lineWidth - 1) << std::setfill('=')
		<< std::right << "+\n";
	ss << "|" << getCentered("Lp.", lp_length) << "|"
		<< getCentered("Węzeł", max_width[0]) << "|";
	char c = 'a' - 1;
	for (size_t i = 1; i < max_width.size(); i++) {
		std::string letter;
		letter = c + (char) i;
		ss << getCentered(letter, max_width[i]) << "|";
	}
	ss << "\n+" << std::setw(lineWidth - 1) << std::setfill('=')
		<< std::right << "+\n";

	//wiersze tabeli
	size_t i = 0;
	for (auto row : values) {
		ss << "|" << getCentered(std::to_string(i + 1) + ".", lp_length) << "|";
		ss << getCentered(getValue(&original_node), max_width[0]) << "|";

		for (size_t j = 0; j < row.size(); j++)
			ss << getCentered(getValue(row[j]), max_width[j + 1]) << "|";

		ss << "\n";

		i++;
		original_node.x += delta->x;
		original_node.y += delta->y;
	}

	//stopka tabeli
	ss << "+" << std::setw(lineWidth - 1) << std::setfill('=')
		<< std::right << "+\n";

	return ss;
}

size_t Table::getLineWidth() const {
	return lineWidth;
}

std::string Table::getError() const {
	return errorDesc;
}

std::string Table::getValue(double value) {
	std::ostringstream ss;
	if (forceScientific)
		ss << std::setiosflags(std::ios::scientific);
	//ustaw precyzję, jeśli w zakresie
	if (precision < 10)
		ss << std::setprecision(precision);
	ss << value;
	return ss.str();
}

std::string Table::getValue(Node* node) {
	std::ostringstream ss;
	ss << "(" << node->x << ";" << node->y << ")";
	return ss.str();
}

std::string Table::getCentered(const std::string& str, size_t width) {
	size_t offset, space;
	if (width > str.length()) {
		offset = size_t(float(width - str.length()) / 2.f);
		space = width - offset - str.length();
	}
	else
		offset = space = 0;

	std::ostringstream ss;
	if (offset)
		ss << std::setw(offset + str.length()) << std::setfill(' ');
	ss << str;
	if (space > 0)
		ss << std::setw(space) << " ";
	return ss.str();
}
