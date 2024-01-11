Program Symulujacy dzialanie mrowki Langtona.
=============================================
Program w pełni działa tylko na komputerach z systemem operacyjnyn Windows, na innych komputerach moze nie dzialac za sprawa biblioteki windows.h z ktorej korzystalismy.
=============================================
Aby skompliowac program: gcc main.c funkcje.c znaczki.c -lgdi32 -o plansza
=============================================
Nastepnie komenda chcp 65001, aby przelaczyc na znaki biale
=============================================
Uruchamianie programu: 
Flagi obowiązkowe:
-f nazwa_folderu (flaga do której zapisywane będą iteracje)
Flagi opcjonalne:
-w  liczba_wierszy (liczba wierszy planszy dla mrówki, domyślnie ustawiona na 10)
- k  liczba_kolumn (liczba kolumn planszy dla mrówki, domyślnie 20)
- i  liczba_iteracji_mrowki (Liczba ruchów jakie wykona mrówka, również posiada domyślna wartość)
- m 0/1 (Tryb 0 – wypisuje plansze w specjalnym oknie – powłoka graficzna, tryb 1 – wypisuje na stdout plansze)
 - d 0/1/2/3 ( Kierunki w jakich mrówka będzie ustawiona na początku kierunki są ustawione jak godziny zegara co oznacza ( w gore – 0 +1 = ruch w prawo + 1 ruch w prawo ) 
- r  0 – 100 ( Randomize, % zrandomizowania mapy z przeszkodami dla mrówki)
- p nazwa_pliku (plik z ciągiem zer i jedynek jest interpretowany jako mapa i dostarczany mrówce)
Przykładowe uruchomienie programu:
./plansza.exe -i 20 -m 0 -k 55 -w 60 -f folder1 -p mapa.txt -d 0 -r 20
Wartosci flag mozna dostosowac, stosujac sie do zalecen by uzyskac rozne efekty.

Jesli chce sie wygenerowac nowa plansze do pliku korzystamy z programu gen.c:
==============================================
gcc gen.c
./a.exe pliktestowy.txt
W ten sposob program wygeneruje nam plansze 0 i 1 ( pola biale i czarne)
Taki plik potem mozemy wykorzystac w naszym glownym programie
./plansza.exe -i 40 -m 0 -k 55 -w 60 -f folder2 -p pliktestowy.txt -d 2 -r 0
