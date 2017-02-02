 # lagrange_polynomial
Program służy do obliczania współczynników wielomianu n-tego stopnia na podstawie podanych węzłów.

## Zasada działania
Do wykonywania obliczeń wykorzystywana jest metoda interpolacji wielomianowej za pomocą wielomianu Lagrange'a. Szegółowe informacje o wielomianie Lagrange'a są dostępne [TUTAJ](https://pl.wikipedia.org/wiki/Interpolacja_wielomianowa#_Wielomian_Lagrange.27a). Dla *n* podanych węzłów (punktów, dla których wartości funkcji są znane) program oblicza *n* współczynników.

## Użycie programu
Program przyjmuje węzły w postaci argumentów linii poleceń. Pojedynczy węzeł to dwie liczby zapisane w nawiasach i oddzielone średnikiem:
`(x;y)`
Liczby *x* oraz *y* mogą zawierać część dziesiętną, oddzieloną przecinkiem lub kropką. Kolejne węzły muszą następować bezpośrednio po sobie:
`(x_1;y_1)(x_2;y_2)...`

##### Zwracana wartość
Jeśli dane wejściowe są poprawne, program zwróci *n* współczynników wielomianu n-tego stopnia, który przechodzi przez wszystkie podane węzły. Współczynniki są podane jako kolejne litery, rozpoczynając od *'a'*, która oznacza wyraz przy najwyższej potędze:
`ax^(n)+bx^(n-1)+cx(n-2)+...`
##### Przykłady użycia
`lagrange_polynomial (3;30.5)(0;-4)(40;4896)`
`lagrange_polynomial (2;3)(4;6)`
`lagrange_polynomial (28,5;1)(4;1)(6.6;2.2)(5;9)`

## Uruchamianie
Program można skompilować bezpośrednio ze źródeł znajdujących się w tym repozytorium. Jest on udostępniony jako projekt Microsoft Visual Studio.

**Istnieje również możliwość pobrania gotowego pliku exe:** [LINK](https://drive.google.com/file/d/0ByHjPTrDWEJ1bWhUZ3RGWEs5blU/view?usp=sharing)