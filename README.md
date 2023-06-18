# Grupowa-miara-centralnosci
Implementacja algorytmów obliczania grupowej centralności łączenia i znajdowania grupy maksymalizującej grupową centralność łączenia w języku C++.

Implementacje te opierają się na reprezentacji grafu za pomocą list sąsiedztwa. Grafy wczytywane są z
pliku .txt. Format takiego pliku "dane1.txt"jest następujący:


a_1 a_2 ... a_n -1

b_1 b_2 ... b_n -1

.
.
.

k_1 k_2 ... k_n -1


gdzie każdy wiersz pliku odpowiada wierzchołkowi grafu, a elementy w wierszach to jego
sąsiedzi, tzn. według powyższego schematu sąsiedzi wierzchołka 0 to a1, a2, ..., an. Numery
wierzchołków w wierszach muszą być oddzielone spacjami, a każdy wiersz musi się kończyć
liczbą -1.

Liczba wierzchołków w grafie jest odgórnie ustalona przez zmienną globalną n. Do rozpatrywania wszystkich podgrafów wykorzystana została binarna reprezentacja podzbiorów.
Narzuca jednak ona pewne ograniczenia, rozpatrywane za pomocą programów grafy nie mogą
mieć więcej niż 32 wierzchołki, zatem również n ≤ 32. Do reprezentacji grup używana jest
struktura danych vector, która jest o tyle wygodniejsza od tablic, że nie wymaga deklaracji
rozmiaru. Elementy grupy, dla której obliczana jest grupowa centralność łączenia deklaruje
użytkownik podczas obsługi programu. Podobnie w programie znajdującym grupę maksymalizującą grupową centralność łączenia użytkownik wprowadza rozmiar, dla którego ma być
znaleziona grupa maksymalizująca wartość grupowej centralności łączenia.

Programy są wystarczające do rozpatrywania niewielkich grafów do jakich został stworzony. Dla większych grafów algorytm nie działa zadowalająco. W szczególności program znajdujący grupę maksymalizującą grupową centralność łączenia ma dużą złożoność obliczeniową.
O ile z grafami o 12 wierzchołkach program sobie jeszcze radzi, to z grafami większymi już
niekoniecznie.
