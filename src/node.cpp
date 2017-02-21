#include "node.hpp"

const std::string Nodes::PARENTHESIS_REGEX = "\\(.*?\\)";
const std::string Nodes::SINGLE_REGEX = "\\((.*?);(.*)\\)";

bool Nodes::parse(const std::string& str) {
	//główne wyrażenie regularne
	std::regex parenthesis_regex(PARENTHESIS_REGEX);

	//iteratory
	auto par_beg = std::sregex_iterator(str.cbegin(), str.cend(), parenthesis_regex);
	auto par_end = std::sregex_iterator();

	if (!std::distance(par_beg, par_end)) {
		errorDesc = "nie znaleziono żadnych węzłów";
		return false;
	}

	for (auto i = par_beg; i != par_end; i++) {
		//pojedynczy węzeł
		std::regex single_regex(SINGLE_REGEX);
		std::smatch single_match;
		std::string single_str = (*i).str();

		if (std::regex_match(single_str, single_match, single_regex)
			&& single_match.size() == 3) {
			try {
				std::string match_1 = single_match[1].str();
				std::string match_2 = single_match[2].str();

				//pobranie współrzędnych
				float x = convert(match_1);
				float y = convert(match_2);

				//dodanie współrzędnych do węzła
				Node* node = new Node;
				node->x = x;
				node->y = y;
				nodes.push_back(node);
			}
			catch (const std::invalid_argument& e) {
				errorDesc = "parametry węzła muszą być liczbami";
				return false;
			}
		}
		else {
			errorDesc = "niepoprawny format węzła " + std::distance(par_beg, i);
			return false;
		}
	}

	return true;
}

std::vector<Node*> Nodes::getNodes() const {
	return nodes;
}

std::string Nodes::getErrorDesc() const {
	return errorDesc;
}

float Nodes::convert(const std::string& input) const {
	/*
		Konwersja jest wykonywana ręczenie zamiast użycia funkcji std::stof z powodu
		różnic w zapisie częsci dziesiętnych. W zależności od języka używanego w systemie,
		separatorem części całkowitej od dziesiętnej może być przecinek lub kropka.
		Jako że funkcja std::stof uwzględnia ten separator przy konwersji, część dziesiętna
		mogła zostać odcięta w poprzednich wersjach programu.
	*/
	std::string str = input;
	std::replace(str.begin(), str.end(), ',', '.');
	if (std::count(str.cbegin(), str.cend(), '.') > 1)
		return false;

	size_t pos = input.find('.');
	if (pos == std::string::npos) {
		return std::stof(str);
	}
	else {
		float whole = std::stof(str.substr(0, pos));
		float fraction = std::stof(str.substr(pos + 1));
		size_t len = str.substr(pos + 1).size();
		float ret = whole;
		if (len > 0) {
			ret += fraction / pow(10, len);
		}
		return ret;
	}
}