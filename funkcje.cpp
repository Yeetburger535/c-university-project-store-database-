#include "baza.h"
#include <conio.h>
#include <limits>
#include <algorithm>

using namespace std;
// ********************** metody gra ************************//
gra::gra(){
    strcpy(nazwa, " ");
    cena = 0;
    sztuk = 0;
    rokWydania = 0;
    strcpy(gatunek, " ");
    strcpy(platforma, " ");
}

char* gra::getNazwa(){
    return nazwa;
}

float gra::getCena(){
    return cena;
}

int gra::getSztuk(){
    return sztuk;
}

int gra::getRok(){
    return rokWydania;
}

char* gra::getGatunek(){
    return gatunek;
}

char* gra::getPlatform(){
    return platforma;
}

void gra::getAll(char *naz, float cen, int szt, int rok, char *gat, char *plat){
    strcpy(nazwa, naz);
    cena = cen;
    sztuk = szt;
    rokWydania = rok;
    strcpy(gatunek, gat);
    strcpy(platforma, plat);
}

void gra::display(){
    cout << "Nazwa: " << getNazwa() << endl;
    cout << "Cena: " << getCena() << endl;
    cout << "Sztuk: " << getSztuk() << endl;
    cout << "Rok wydania: " << getRok() << endl;
    cout << "Gatunek: " << getGatunek() << endl;
    cout << "Platforma: " << getPlatform() << endl;
}

// **************************** metody bazaGra ******************************** //

bazaGra::bazaGra(){
    current = -1;
    currentFound = -1;
    currentKosz = -1;
}

int bazaGra::setCurrent(int index, vector<gra> typ, currentType rodzaj){

    if(typ.empty())
        return 0;       //brak elementow

    else if(index < 0)
        return 3;       //ujemny niedozwolony
    
    else if(index >= typ.size())
        return 2;      //zbyt wysoki

    else{
        getCurrentRef(rodzaj) = index;
        return 1;
    }
}

int bazaGra::getCurrent(currentType typ){
    switch(typ){
        case BAZA: return current;
        case FOUND: return currentFound;
        case KOSZ: return currentKosz;
        default: return -1;
    }
}

int& bazaGra::getCurrentRef(currentType typ){
    switch(typ){
        case BAZA: return current;
        case FOUND: return currentFound;
        case KOSZ: return currentKosz;
        default: throw out_of_range("invalid");
    }
}

vector<gra>& bazaGra::getVector(currentType typ){  
    switch(typ){
        case BAZA: return tab;
        case FOUND: return found;
        case KOSZ: return bin;
        default: throw out_of_range("invalid");
    }
}

void bazaGra::clearInput(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void bazaGra::getChar(char *prompt, char *fail, char *dest, int max){
    do{
        char buf[200];
        cout << prompt;
        cin.getline(buf, 200);
        if(strlen(buf) > max){
            cout << fail;
            continue;
        }
        strcpy(dest, buf);

        break;

    }while(true);

}

float bazaGra::getFloat(char *prompt,char *fail, int min, int max){
    float val;
    do{   
        cout << prompt;
        cin >> val;
        if(cin.fail()){
            clearInput();
            cout << "wykryto niedozowlone znaki. podaj tylko liczbe\n";
            val = -1; //by petla sie powtorzyla
            continue;
        }
        if(val <= min || val > max){
            cout << fail;
        }
        
        clearInput();

    }while (val <= min || val > max);

    return val;
}

int bazaGra::getInt(char *prompt, char *fail, int min, int max){
    int val;
    do{
        cout << prompt;
        cin >> val;
        if(cin.fail()){
            clearInput();
            cout << "wykryto niedozwolone znaki. sprobuj ponownie\n";
            val = -1;
            continue;
        }
        if(val <= min || val > max){
            cout << fail;
        }

        clearInput();

    }while (val <= min || val > max);

    return val;
}


bool bazaGra::dodaj(gra g){
    
    tab.push_back(g);
    current = tab.size() -1;
    return true;
}


bool bazaGra::universalDisplay(vector <gra> typ){
    if(typ.empty()){
        return false;
    }
    
    for(int i = 0; i < typ.size(); i++){
        cout << "\nGra #" << i + 1 << ": \n";
        typ[i].display();
    }
    return true;
}

bool bazaGra::next(){
    if(current < tab.size() - 1){
        current++;
        return true;
    }
    return false;

    
}

bool bazaGra::previous(){
    if(current > 0){
        current--;
        return true;
    }
    return false;
}

void bazaGra::showCurrent(int current, vector<gra> typ){
    if(current >=0)
    typ[current].display();
}

bool bazaGra::sprawdzRozmiar(currentType typ){
    if(getVector(typ).size() == 0){
        return false;
    }
    return true;
}

bool bazaGra::usun(){
    bin.push_back(tab[current]);
    currentKosz = 0;
    tab.erase(tab.begin() + current);
    if(current == tab.size())
        current--;

    return true;
}


bool bazaGra::usunWszystko(){
    for(int i = 0; i < tab.size(); i++){
        bin.push_back(tab[i]);
    }
    tab.clear();
    current = -1;
    currentKosz = 0;
    return true;
}

bool bazaGra::saveFile(){
    FILE *fp = fopen("baza.txt", "wb");
    if(!fp){
        return false;
    }
    int a = tab.size();
    fwrite(&a, sizeof(a), 1, fp);
    for(int i =0; i < tab.size(); i++){
        fwrite (&tab[i], sizeof(tab[i]), 1, fp);
    }
    fclose(fp);
    return true;
}

bool bazaGra::readFile(){
    FILE *fp = fopen("baza.txt", "rb");
    if(!fp){
        return false;
    }
    tab.clear();
    current = -1;
    gra g;
    int liczba;
    fread(&liczba, sizeof(liczba), 1, fp);
    for(int i =0; i < liczba; i++){
        fread(&g, sizeof(gra), 1, fp);
        tab.push_back(g);
    }
    fclose(fp);
    if(!tab.empty())
        current = 0;
    return true;
}

bool bazaGra::sortujPoNazwie(bool rosnaco){

    if(rosnaco == true){    //rosnaco
        sort(tab.begin(), tab.end(), [](gra& a, gra& b){      //referencje sa po to, zeby przy kazdym porownaniu nie robila sie nowa kopia
            return strcmp(a.getNazwa(), b.getNazwa()) <0;       //porownujemy ze soba dwa pierwsze elementy, jezeli a < b to jest true, nie ma zamiany, jezeli a > b jest false i zamieniaja sie miejscami
        });                                                     //dwie referencje jako ze funkcja korzysta ze zwyklych algorytmow sortujacych, robi to w swojej tymczasowej zmiennej 
    }
    else{   //malejaco
        sort(tab.begin(), tab.end(), [](gra& a, gra& b){
            return strcmp(a.getNazwa(), b.getNazwa()) >0;
        });

    }
    return true;
    
}

bool bazaGra::sortujPoCenie(bool rosnaco){

    if(rosnaco == true){
        sort(tab.begin(), tab.end(), [](gra& a, gra& b){
            return a.getCena() < b.getCena();
        });
    }
    else{
        sort(tab.begin(), tab.end(), [](gra& a, gra& b){
            return a.getCena() > b.getCena();
        });
    }
    return true;
}

bool bazaGra::sortujPoDacie(bool rosnaco){

    if(rosnaco == true){
        sort(tab.begin(), tab.end(), [](gra& a, gra& b){
            return a.getRok() < b.getRok();
        });
    }
    else{
        sort(tab.begin(), tab.end(), [](gra& a, gra & b){
            return a.getRok() > b.getRok();
        });
    }
    return true;
}



// *************************** metody szukanie ******************************* //

szukanie::szukanie(){
   
}

bool szukanie::poNazwie(char szukana[]){
    currentFound = -1;
    found.clear();
    for(int i=0; i < tab.size(); i++){
        if (strcmp (tab[i].getNazwa(), szukana) == 0){
            found.push_back(tab[i]);
        }
    }
        if(!found.empty()){
            currentFound = 0;
            return true;
        }
        else
            return false;
}

bool szukanie::poCenie(float min, float max){
    found.clear();
    for(int i =0; i < tab.size(); i++){
        if (tab[i].getCena() >= min && tab[i].getCena() <= max){
            found.push_back(tab[i]);
        }
    }
        if(!found.empty()){
            currentFound = 0;
            return true;
        }
        else
            return false;
}

bool szukanie::poGatunku(char szukana[]){
    currentFound = -1;
    found.clear();
    for(int i=0; i < tab.size(); i++){
        if (strcmp (tab[i].getGatunek(), szukana) == 0){
            found.push_back(tab[i]);
        }
    }
        if(!found.empty()){
            currentFound = 0;
            return true;
        }
        else
            return false;
}

bool szukanie::poPlatformie(char szukana[]){
    currentFound = -1;
    found.clear();
    for(int i=0; i < tab.size(); i++){
        if (strcmp (tab[i].getPlatform(), szukana) == 0){
            found.push_back(tab[i]);
        }
    }
        if(!found.empty()){
            currentFound = 0;
            return true;
        }
        else
            return false;
}

bool szukanie::nextFound(){

    if(currentFound < found.size() - 1){
        currentFound++;
        return true;
    }
    return false;
    
}

bool szukanie::previousFound(){
    if(currentFound > 0){
        currentFound--;
        return true;
    }
    return false;
}

bool szukanie::czyscFound(){
    found.clear();
    currentFound = -1;
    return true;
}

// *************************** metody kosz ********************************** //

kosz::kosz(){
}

bool kosz::czyscKosz(){
    bin.clear();
    currentKosz = -1;
    return true;
}

bool kosz::nextKosz(){
    if(currentKosz < bin.size() -1){
        currentKosz++;
        return true;
    }
    return false;
    
}

bool kosz::previousKosz(){
    if(currentKosz > 0){
        currentKosz--;
        return true;
    }
    return false;
}

bool kosz::przywrocBiezacy(){
    tab.push_back(bin[currentKosz]);
    current = 0;
    bin.erase(bin.begin() + currentKosz);
    if(currentKosz == bin.size())
        currentKosz--;

    return true;
}

bool kosz::przywrocWszystko(){
        for(int i = 0; i < bin.size(); i++){
            tab.push_back(bin[i]);
        }
        bin.clear();
        currentKosz = -1;
        current = 0;
        return true;
}
