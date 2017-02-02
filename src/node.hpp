#pragma once

#include "stdafx.hpp"


extern struct Node;

/**
Klasa służy do konwersji ciągu znaków reprezentującego
węzły wielomianu na ich liczbowe odpowiedniki.

Ciąg znaków zawierający węzły ma następujący format:
(x_1;y_1)(x_2;y_2)...(x_n;y_n)
każdy nawias reprezentuje jeden węzeł.
*/
class Nodes {
private:
	static const std::string PARENTHESIS_REGEX;
	static const std::string SINGLE_REGEX;

	std::vector<Node*> nodes;
	std::string errorDesc;
public:
	/**
	Tworzy nowy obiekt klasy Node.
	*/
	Nodes() = default;
	~Nodes() = default;
	/**
	Przetwarza podany ciąg na węzły. Jeśli przetwarzanie
	się nie powiedzie, szczegóły można uzyskać za pomocą
	metody 'Node::getErrorDesc'.
	@param str ciąg znaków
	@return czy parsowanie się powiodło
	*/
	bool parse(const std::string& str);
	/**
	Zwraca wektor zawierający wszystkie węzły.
	*/
	std::vector<Node*> getNodes() const;
	/**
	Zwraca opis błędu, jeśli jakiś wystąpił.
	*/
	std::string getErrorDesc() const;
};

struct Node {
	float x;
	float y;
};