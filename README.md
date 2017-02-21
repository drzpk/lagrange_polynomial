# lagrange_polynomial
Program służy do obliczania współczynników wielomianu dowolnego  stopnia na podstawie podanych węzłów.

## Zasada działania
Do wykonywania obliczeń wykorzystywana jest metoda interpolacji wielomianowej za pomocą wielomianu Lagrange'a. Szegółowe informacje o wielomianie Lagrange'a są dostępne [TUTAJ](https://pl.wikipedia.org/wiki/Interpolacja_wielomianowa#_Wielomian_Lagrange.27a). Dla *n* podanych węzłów (punktów, dla których wartości funkcji są znane) program oblicza *n* współczynników.

## Użycie programu
Program przyjmuje węzły w postaci argumentów linii poleceń. Pojedynczy węzeł to dwie liczby zapisane w nawiasach i oddzielone średnikiem:
`(x;y)`
Liczby *x* oraz *y* mogą zawierać część dziesiętną, oddzieloną przecinkiem lub kropką. Kolejne węzły muszą następować bezpośrednio po sobie:
`(x_1;y_1)(x_2;y_2)...`

Program może działać w dwóch trybach: zwykłym i tabeli. Każdy z trybów jest opisany poniżej.

### Tryb zwykły
W tym trybie zwracana po podaniu węzłów zwracane są współczynniki wielomianu. Jeśli dane wejściowe są poprawne, program zwróci *n+1* współczynników wielomianu *n-tego* stopnia, który przechodzi przez wszystkie podane węzły. Współczynniki są podane jako kolejne litery, rozpoczynając od *'a'*, która oznacza wyraz przy najwyższej potędze:
`ax^(n)+bx^(n-1)+cx(n-2)+...`


#### Przykład użycia:

`lagrange_polynomial.exe -n (2;4)(4;5)` 

#### Wynik programu:
```
Znalezione współczynniki:
a: 0.5
b: 3
```
### Tryb tabeli
W tym trybie program na podstawie podanych węzłów generuje tabelę, w której każdy następny wiersz zawiera współczynniki dla nieco zmodyfikowanej wersji wielomianu.
Modyfikacja polega na podaniu **delty, czyli wartości, o jakie będzie zmieniał się ostatni podany węzeł wielomianu**. Ten tryb pozwala również na zmianę sposobu
wyświetlania wyników na notację naukową oraz na wybór precyzji.

**Parametry obsługiwane w trybie tabeli:**
* -n  -  węzły wielomianu
* -d  -  delta ostatniego węzła wielomianu
* -i  -  liczba iteracji, czyli wierszy tabeli
* -s  -  zapisywanie wyniku w notacji naukowej
* -p  -  ustawienie prezycji wyników
* -o  -  zapisanie tabeli do pliku *output.txt*

Trzy pierwsze parametry są wymagane, reszta jest obowiązkowa.

#### Przykład użycia:
Powiedzmy, że chcemy wygenerować tabelę dla dla wielomianu o węzłach *(2;4)(4;9)(2;3)(-0.4;2)(1;10)*. Chcemy, aby w każdej kolejnej iteracji wartość y ostatniego
węzła rosła o 1, a wszystkich iteracji ma być 10. W takim razie musimy podać następujące parametry:

`lagrange_polynomial.exe -n (2;4)(4;9)(3;3)(-0.4;2)(1;10) -d (0;1) -i 10`

#### Wynik programu:
Po wprowadzeniu powyższycha parametrów program zwróci następującą tabelę:

|Lp.| Węzeł  |     a     |    b    |    c     |    d    |    e    |
|---|--------|-----------|---------|----------|---------|---------|
|1. | (1;10) | -0.417622 | 4.50955 | -14.1168 | 11.0477 | 8.97708 |
|2. | (1;11) | -0.536669 | 5.53336 | -16.7834 | 12.6668 | 10.1199 |
|3. | (1;12) | -0.655717 | 6.55717 | -19.4501 | 14.2858 | 11.2628 |
|4. | (1;13) | -0.774764 | 7.58098 | -22.1168 | 15.9049 | 12.4057 |
|5. | (1;14) | -0.893812 | 8.60479 | -24.7834 | 17.5239 | 13.5485 |
|6. | (1;15) | -1.01286  | 9.6286  | -27.4501 | 19.143  | 14.6914 |
|7. | (1;16) | -1.13191  | 10.6524 | -30.1168 | 20.762  | 15.8342 |
|8. | (1;17) | -1.25096  | 11.6762 | -32.7834 | 22.3811 | 16.9771 |
|9. | (1;18) |   -1.37   |  12.7   | -35.4501 | 24.0001 | 18.1199 |
|10.| (1;19) | -1.48905  | 13.7238 | -38.1168 | 25.6192 | 19.2628 |


## Uwagi
1. Program do poprawnego działania wymaga podania węzłów *prawdziwej* funkcji, czyli takiej, która każdemu elementowi ze zbioru *x* przypisuje dokładnie jeden element ze zbioru *y*.
2. W przypadku wielomianów dużych stopnii może okazać się, że okno konsoli jest zbyt wąskie, aby zmieścić całą tabelę. W takim wypadku należy dopisać do paramterów parametr *-o*, który spowoduje zapisanie tabeli do pliku *output.txt*.


## Uruchamianie
Program można skompilować bezpośrednio ze źródeł znajdujących się w tym repozytorium. Jest on udostępniony jako projekt Microsoft Visual Studio 2015.

**Istnieje również możliwość pobrania gotowego pliku exe:** [LINK](https://drive.google.com/file/d/0ByHjPTrDWEJ1bWhUZ3RGWEs5blU/view?usp=sharing)

Jeśli podczas uruchamiania pojawia się błąd krytyczny, wymagane jest pobranie pakietów dystrybucyjnych z [TEJ](https://www.microsoft.com/pl-pl/download/details.aspx?id=48145) strony.

### Linux
Program został przystosowany do uruchamiania w systemie Linux. W tym celu trzeba go ręcznie skompilować. Aby to zrobić, należy pobrać repozytorium i w jego głównym katalogu uruchomić
polecenie `make`. Spowoduje to kompilację i utworzenie pliku wykonywalnego `lagrange_polynomial`. Składnia programu jest identyczna, z tą różnicą, że w celu uruchomienia programu
koniecznie będzie poprzedzenie jego nazwy symbolem bieżącego folderu: `./lagrange_polynomial`.
