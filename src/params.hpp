#pragma once

#include "stdafx.hpp"

/**
Klasa ma obsługiwać parametry wejściowe programu
*/
class Params {
private:
	bool caseSensitive;
	std::map<int, const char*> shortcuts;
	std::map<int, const char*> names;
	std::map<int, const char*> descriptions;
	std::map<int, std::string> values;
	std::set<int> withValues;

	bool error;
	std::string errorDescription;
public:
	/**
	Tworzy nowy obiekt klasy Params
	@param caseSensitive czy wielkość znaków ma znaczenie
	*/
	Params(bool caseSensitive = true) : caseSensitive(caseSensitive), error(false) {}
	/**
	Przetwarza parametry programu. Jeśli przetwarzanie
	nie powiodło się, zwracana jest wartość 'false'.
	Opis błędu można uzyskać za pomocą 'getErrorDescription()'.

	@param argc liczba parametrów
	@param argv podwójny wskaĹşnik na parametry
	@return czy przetwarzanie się powiodło
	*/
	bool parseParams(int argc, char** argv);
	/**
	Dodaje nowy parametr. Każdy parametr posiada
	identyfikator używany póĹşniej w innych metodach
	obiektu. Skrót i nazwa parametru powinny być
	podane bez wiodących myślników.

	@param id identyfikator parametru
	@param shortcut skrót parametru
	@param name pełna nazwa parametru
	@param desc opis parametru
	@param hasValue czy parametr ma wartość
	*/
	void addParameter(int id, const char* shortcut, const char* name, const char* desc, bool hasValue = true);
	/**
	Sprawdza, czy parametr o podanym identyfikatorze istnieje.
	@param id identyfikator parametru
	@return czy parametr istnieje
	*/
	bool hasParameter(int id) const;
	/**
	Sprawdza, czy wystąpił błąd
	@return status flagi błędu
	*/
	bool isError() const;
	/**
	Zwraca opis błędu przetwarzania parametrów.
	@return opis błędu
	*/
	std::string getErrorDescription() const;
	/**
	Wypisuje w konsoli wszyskie parametry, każdy
	w osobnej linii. Parametr indent służy do ustawienia
	wcięcia każdej linii.
	@param indent wcięcie linii
	@return parametry
	*/
	std::string printParams(int indent) const;
	/**
	Zwraca całkowitą wartość liczbową parametru.
	@param id identyfikator parametru
	@return wartość całkowita parametru
	*/
	int getInt(int id) const;
	/**
	Zwraca zmiennoprzecinkową wartość liczbową parametru.
	@param id identyfikator parametru
	@return wartość zmiennoprzecinkowa parametru
	*/
	float getFloat(int id) const;
	/**
	Zwraca wartość tekstową parametru.
	@param id identyfikator parametru
	@return wartość tekstowa parametru
	*/
	std::string getString(int id) const;
};
