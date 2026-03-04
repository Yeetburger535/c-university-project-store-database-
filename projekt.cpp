#include "baza.h"
#include "funkcje.cpp"
#include <conio.h>
#include <limits>

using namespace std;

void menuSort(szukanie &baza){
    char w;
    if(!baza.sprawdzRozmiar(BAZA)){
        cout << "brak danych w bazie\n";
        return;
    }

    do{
        cout << "W jaki sposob chcesz posortowac baze?\n\n";
        cout << "1. Wg nazwy\n";
        cout << "2. Wg ceny\n";
        cout << "3. Wg daty wydania\n\n";
        cout << "x. anuluj sortowanie\n";  

        w=getch();

        system("cls");

        switch(w){
            case '1':{  char c;

                        do{
                            cout << "posortowac rosnaco (r) czy malejaco (m)?\n";
                            cout << "(r/m): ";
                            cin >> c;
                                
                            if(c == 'r'){
                                baza.sortujPoNazwie(true);
                                cout << "posortowano\n";
                            }   

                            else if(c == 'm'){
                                baza.sortujPoNazwie(false);
                                cout << "posortowano\n";
                            }

                            else 
                                cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                            cin.ignore();
                        }while (c != 'r' && c != 'm');
                        
                        break;

                    }
            
            case '2':{  char c;

                        do{
                            cout << "posortowac rosnaco (r) czy malejaco (m)?\n";
                            cout << "(r/m): ";
                            cin >> c;
                                
                            if(c == 'r'){
                                baza.sortujPoCenie(true);
                                cout << "posortowano\n";
                            }   

                            else if(c == 'm'){
                                baza.sortujPoCenie(false);
                                cout << "posortowano\n";
                            }

                            else 
                                cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                            cin.ignore();
                        }while (c != 'r' && c != 'm');

                        break;

                    }

            case '3':{  char c;

                        do{
                            cout << "posortowac rosnaco (r) czy malejaco (m)?\n";
                            cout << "(r/m): ";
                            cin >> c;
                                
                            if(c == 'r'){
                                baza.sortujPoDacie(true);
                                cout << "posortowano\n";
                            }   

                            else if(c == 'm'){
                                baza.sortujPoDacie(false);
                                cout << "posortowano\n";
                            }

                            else 
                                cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                            cin.ignore();
                        }while (c != 'r' && c != 'm');
                        
                        break;

                    }


        }


    }while(w != 'x');

}

void menuBaza(szukanie &baza){
    char w;
    int i;

    do{
        cout << "\n***** operacje na glownej bazie *****\n\n";
        cout << "Wybierz funkcje:\n";
        cout << "1. dodaj nowa pozycje do bazy\n";
        cout << "2. wyswietl zawartosc bazy\n";
        cout << "3. wyswietl aktualny element\n";
        cout << "4. usun aktualny element\n";
        cout << "5. usun wszystkie elementy\n";
        cout << "6. Przejdz do indeksu\n";
        cout << "7. Sortowanie bazy\n\n";

        cout << "z. zapis do pliku\n";
        cout << "o. odczyt z pliku\n\n";

        cout << "n. nastepny\n";
        cout << "p. poprzedni\n\n";
        cout << "x. powrot do menu glownego\n";
        w=getch();

        system("cls");

        switch(w){
            case '1':{
                        char naz[30], gat[20], plat[10];
                        char c;
                        gra g;

                        baza.getChar("podaj nazwe: ", "zbyt dluga nazwa. sprobuj ponownie\n", naz, 30);
                        float cen = baza.getFloat("podaj cene: ", "nieprawidlowa cena. podaj liczbe w przedziale 1 - 500\n", 0, 500);
                        int szt = baza.getInt("podaj ilosc sztuk: ", "ilosc nie moze byc ujemna. sprobuj ponownie\n", 0, 5000);
                        int rok = baza.getInt("podaj rok wydania: ", "nieprawidlowa data. sprobuj ponownie\n", 1970, 2025);
                        baza.getChar("podaj gatunek: ", "zbyt dluga nazwa gatunku. sprobuj ponownie\n", gat, 20);
                        baza.getChar("podaj platforme: ", "zbyt dluga nazwa platformy. sprobuj ponownie\n", plat, 10);

                        g.getAll(naz, cen, szt, rok, gat, plat);

                        cout << "\ndane gry, ktora chcesz dodac: \n\n";
                        g.display();
                        
                        do{
                            cout << "czy chcesz dodac ta pozycje do bazy?\n(t/n): ";
                            cin >> c;

                            if(c == 't'){
                                baza.dodaj(g);
                                cout << "pozycja zostala dodana\n";
                            }
                            else if(c == 'n'){
                                cout << "anulowano dodawanie pozycji\n";
                            }
                            else
                                cout << "nieprawidlowy znak. sprobuj ponownie\n\n";
                            
                            cin.ignore();
                        
                        }while (c != 't' && c != 'n');

                        break;
                    }
            
            case '2':   if (!baza.universalDisplay(baza.getVector(BAZA)))
                            cout << "Brak elementow do wyswietlenia\n";
                        break;

            case '3':   if(baza.getCurrent(BAZA) == -1)
                            cout << "brak elementow\n";
                        else
                            baza.showCurrent(baza.getCurrent(BAZA), baza.getVector(BAZA));
                        break;

            case '4':{  char c; 
                        if(!baza.sprawdzRozmiar(BAZA)){
                            cout << "Brak elementow do usuniecia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz usunac element: \n";
                                baza.showCurrent(baza.getCurrent(BAZA), baza.getVector(BAZA));
                                cout << "(t/n): ";
                                cin >> c;
    
                                if(c == 't'){
                                    baza.usun();
                                    cout << "usunieto\n";
                                }
                            
                            else if(c == 'n')
                                    cout << "Usuwanie anulowane\n";
        
                                else
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c !='n');
                        
                        break;
                    }

            case '5':{  char c;
                        if(!baza.sprawdzRozmiar(BAZA)){
                            cout << "Brak elementow do usuniecia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz przeniesc wszystko do kosza?\n";
                                cout << "(t/n): ";
                                cin >> c;
                                
                                if(c == 't'){
                                    baza.usunWszystko();
                                    cout << "usunieto\n";
                                }   

                                else if(c == 'n')
                                    cout << "Usuwanie anulowane\n";

                                else 
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c != 'n');

                        break;
                    }

            case '6':   cout << "Podaj indeks elementu, do ktorego chcesz przejsc: ";
                        cin >> i;
                        switch(baza.setCurrent(i, baza.getVector(BAZA), BAZA)){
                            case 0: cout << "Baza jest pusta\n"; break;
                            case 2: cout << "Podany indeks jest zbyt wysoki\n"; break;
                            case 3: cout << "Ujemny indeks jest niedozwolony\n"; break;
                            case 1: baza.showCurrent(baza.getCurrent(BAZA), baza.getVector(BAZA));
                        }
                        cin.ignore();
                        break;

            case '7':   menuSort(baza);
                        break;

            case 'z':{  char c;
                        

                        do{
                            cout << "czy chcesz zapisac aktualna baze do pliku?\n";
                            cout << "(t/n) :";
                            cin >> c;

                            if(c == 't'){
                                if(baza.saveFile())
                                    cout << "zapisano do pliku\n";
                                else
                                    cout << "blad zapisu\n";
                            }   

                            else if(c == 'n')
                                cout << "zapis anulowany\n";

                            else 
                                cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                            cin.ignore();

                        }while (c != 't' && c != 'n');

                        break;
                    }

            case 'o':   if(baza.readFile())
                            cout << "odczytano\n";
                        else
                            cout << "blad odczytu\n";
                        break;

            case 'n':   baza.next();
                        baza.showCurrent(baza.getCurrent(BAZA), baza.getVector(BAZA));
                        break;
            case 'p':   baza.previous();
                        baza.showCurrent(baza.getCurrent(BAZA), baza.getVector(BAZA));
                        break;

        }

    }while(w != 'x');
}

void menuSzukanie(szukanie &baza){
    char w, szukana[30];
    float min, max;
    int i;

    do{
        cout << "\n***** operacje wyszukiwania *****\n\n";
        cout << "Wybierz funkcje:\n";
        cout << "1. wyszukaj wg nazwy\n";
        cout << "2. wyszukaj wg ceny\n";
        cout << "3. wyszukaj wg gatunku\n";
        cout << "4. wyszukaj wg platformy\n";
        cout << "5. wyczysc wyszukiwanie\n";
        cout << "6. przejdz do indeksu\n";

        cout << "n. nastepny\n";
        cout << "p. poprzedni\n";
        cout << "x. powrot do menu glownego\n";
        w=getch();
        system("cls");

        switch(w){
            case '1':   cout << "Podaj szukana nazwe: ";
                        cin.getline(szukana, 30);;
                            if(!baza.poNazwie(szukana))
                                cout << "Niczego nie znaleziono\n";
                            else
                                baza.getVector(FOUND)[baza.getCurrent(FOUND)].display();
                            break;

            case '2':   cout << "Podaj cene minmimalna: ";
                        cin >> min;
                        cout << "Podaj cene maksymalna: ";
                        cin >> max;
                        if(!baza.poCenie(min, max))
                            cout << "Niczego nie znaleciono\n";
                        else
                            baza.getVector(FOUND)[baza.getCurrent(FOUND)].display();

                        break;

            case '3':   cout << "Podaj szukany gatunek: ";
                        cin.getline(szukana, 30);;
                            if(!baza.poGatunku(szukana))
                                cout << "Niczego nie znaleziono\n";
                            else
                                baza.getVector(FOUND)[baza.getCurrent(FOUND)].display();
                            break;

            case '4':   cout << "Podaj szukana nazwe: ";
                        cin.getline(szukana, 30);;
                            if(!baza.poPlatformie(szukana))
                                cout << "Niczego nie znaleziono\n";
                            else
                                baza.getVector(FOUND)[baza.getCurrent(FOUND)].display();
                            break;

            case '5':{  char c;
                        if(!baza.sprawdzRozmiar(FOUND)){
                            cout << "Brak elementow do usuniecia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz wyczyscic wyniki wyszukiwania?\n";
                                cout << "(t/n): ";
                                cin >> c;
                                
                                if(c == 't'){
                                    baza.czyscFound();
                                    cout << "usunieto\n";
                                }   

                                else if(c == 'n')
                                    cout << "Usuwanie anulowane\n";

                                else 
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c != 'n');

                        break;
                    }

            case '6':   cout << "Podaj indeks elementu, do ktorego chcesz przejsc: ";
                        cin >> i;
                        switch(baza.setCurrent(i, baza.getVector(FOUND), FOUND)){
                            case 0: cout << "Baza jest pusta\n"; break;
                            case 2: cout << "Podany indeks jest zbyt wysoki\n"; break;
                            case 3: cout << "Ujemny indeks jest niedozwolony\n"; break;
                            case 1: baza.showCurrent(baza.getCurrent(FOUND), baza.getVector(FOUND));
                        }
                        break;

            case 'n':   baza.nextFound();
                        baza.showCurrent(baza.getCurrent(FOUND), baza.getVector(FOUND));
                        break;
            case 'p':   baza.previousFound();
                        baza.showCurrent(baza.getCurrent(FOUND), baza.getVector(FOUND));
                        break;
        }

    }while(w != 'x');
}

void menuKosz(szukanie &baza){
    char w;
    int i;

    do{
        cout << "\n***** operacje usuwania *****\n\n";
        cout << "Wybierz funkcje:\n";
        cout << "1. wyswietl zawartosc kosza\n";
        cout << "2. wyczysc zawartosc kosza\n";
        cout << "3. przywroc biezacy element\n";
        cout << "4. przywroc wszystkie elementy\n";
        cout << "5. przejdz do indeksu\n";

        cout << "n. nastepny\n";
        cout << "p. poprzedni\n";
        cout << "x. powrot do menu glownego\n";
        w=getch();

        system("cls");

        switch(w){
            case '1':   if(!baza.universalDisplay(baza.getVector(KOSZ)))
                            cout << "brak elementow do wyswietlenia\n";
                        break; 

            case '2':{  char c;
                        if(!baza.sprawdzRozmiar(KOSZ)){
                            cout << "Brak pozycji do wyczyszczenia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz oproznic kosz\n";
                                cout << "(t/n): ";
                                cin >> c;
                                
                                if(c == 't'){
                                    baza.czyscKosz();
                                    cout << "usunieto\n";
                                }   

                                else if(c == 'n')
                                    cout << "Usuwanie anulowane\n";

                                else 
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c != 'n');

                        break;
                    }
            case '3':{  char c;
                        if(!baza.sprawdzRozmiar(KOSZ)){
                            cout << "Brak elementow do przywrocenia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz przywrocic pozycje: \n";
                                baza.showCurrent(baza.getCurrent(KOSZ), baza.getVector(KOSZ));
                                cout << "(t/n): ";
                                cin >> c;
                                
                                if(c == 't'){
                                    baza.przywrocBiezacy();
                                    cout << "przywrocono\n";
                                }   

                                else if(c == 'n')
                                    cout << "przywracanie anulowane\n";

                                else 
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c != 'n');

                        break;
                    }

            case '4':{  char c;
                        if(!baza.sprawdzRozmiar(KOSZ)){
                            cout << "Brak elementow do przywrocenia\n";
                            break;
                        }
                        else
                            do{
                                cout << "Czy na pewno chcesz przywrocic wszystkie elementy z kosza?\n";
                                cout << "(t/n): ";
                                cin >> c;
                                
                                if(c == 't'){
                                    baza.przywrocWszystko();
                                    cout << "przywrocono\n";
                                }   

                                else if(c == 'n')
                                    cout << "przywracanie anulowane\n";

                                else 
                                    cout << "nieprawidlowy znak. Sprobuj ponownie\n\n";
                            
                                cin.ignore();
                            }while (c != 't' && c != 'n');

                        break;
                    }

            case '5':   cout << "Podaj indeks elementu, do ktorego chcesz przejsc: ";
                        cin >> i;
                        switch(baza.setCurrent(i, baza.getVector(KOSZ), KOSZ)){
                            case 0: cout << "Kosz jest pusty\n"; break;
                            case 2: cout << "Podany indeks jest zbyt wysoki\n"; break;
                            case 3: cout << "Ujemny indeks jest niedozwolony\n"; break;
                            case 1: baza.showCurrent(baza.getCurrent(KOSZ), baza.getVector(KOSZ));
                        }
                        break;

            case 'n':   baza.nextKosz();
                        baza.showCurrent(baza.getCurrent(KOSZ), baza.getVector(KOSZ));
                        break;
            case 'p':   baza.previousKosz();
                        baza.showCurrent(baza.getCurrent(KOSZ), baza.getVector(KOSZ));
                        break;
        }

    }while(w != 'x');
}



// *************************** main *************************************** //
int main(){
    char w, a; //w jak wybór, a jest tylko do wyjscia
    szukanie baza;

    do{
        cout << "Katalog gier komputerowych\n\n";
        cout << "Wybierz funkcje:\n";
        cout << "1. operacje na glownej bazie\n";
        cout << "2. wyszukiwanie\n";
        cout << "3. kosz\n";
        cout << "x. wyjscie z programu\n";
        w=getch();

        system("cls");

        switch(w){
            case '1': menuBaza(baza);
                    break;

            case '2': menuSzukanie(baza);
                    break;

            case '3': menuKosz(baza);
                    break;

            case 'x': cout << "czy na pewno chcesz opuscic program? (t/n)";
                    a=getch();
                    if(a == 't')
                        w = '|';    //dlaczego akurat ten znak? bo jest bardzo mala szansa ze go ktokolwiek nacisnie tak po prostu przy wyborze menu
                    break;

        }

    }while(w != '|');
}

