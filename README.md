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

`lagrange_polynomial.exe -n (2;4)(4;9)(2;3)(-0.4;2)(1;10) -d (0;1) -i 10`

#### Wynik programu:
Po wprowadzeniu powyższycha parametrów program zwróci następującą tabelę:

|Lp.| Węzeł  |    a     |    b    |    c     |    d    |    e    |
|---|--------|----------|---------|----------|---------|---------|
|1. | (1;10) | -2.15413 | 15.3455 | -30.6907 | 13.9654 | 13.5339 |
|2. | (1;11) | -2.39223 | 17.155  | -34.6907 | 15.8701 | 15.0577 |
|3. | (1;12) | -2.63032 | 18.9646 | -38.6907 | 17.7749 | 16.5815 |
|4. | (1;13) | -2.86842 | 20.7741 | -42.6907 | 19.6797 | 18.1053 |
|5. | (1;14) | -3.10651 | 22.5836 | -46.6907 | 21.5844 | 19.6292 |
|6. | (1;15) | -3.34461 | 24.3931 | -50.6907 | 23.4892 | 21.153  |
|7. | (1;16) | -3.5827  | 26.2027 | -54.6907 | 25.3939 | 22.6768 |
|8. | (1;17) | -3.8208  | 28.0122 | -58.6907 | 27.2987 | 24.2006 |
|9. | (1;18) | -4.05889 | 29.8217 | -62.6907 | 29.2035 | 25.7244 |
|10.| (1;19) | -4.29699 | 31.6312 | -66.6907 | 31.1082 | 27.2482 |


## Uwagi
1. Program do poprawnego działania wymaga podania węzłów *prawdziwej* funkcji, czyli takiej, która każdemu elementowi ze zbioru *x* przypisuje dokładnie jeden element ze zbioru *y*.
2. W przypadku wielomianów dużych stopnii może okazać się, że okno konsoli jest zbyt wąskie, aby zmieścić całą tabelę. W takim wypadku należy dopisać do paramterów parametr *-o*, który spowoduje zapisanie tabeli do pliku *output.txt*.


## Uruchamianie
Program można skompilować bezpośrednio ze źródeł znajdujących się w tym repozytorium. Jest on udostępniony jako projekt Microsoft Visual Studio 2015.

**Istnieje również możliwość pobrania gotowego pliku exe:** [LINK](https://drive.google.com/file/d/0ByHjPTrDWEJ1bWhUZ3RGWEs5blU/view?usp=sharing)

Jeśli podczas uruchamiania pojawia się błąd krytyczny, wymagane jest pobranie pakietów dystrybucyjnych z [TEJ](https://www.microsoft.com/pl-pl/download/details.aspx?id=48145) strony.
