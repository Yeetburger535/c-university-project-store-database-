#pragma once
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

enum currentType {BAZA, FOUND, KOSZ};

class gra{
    protected: 
        char nazwa[30]; 
        float cena;
        int sztuk;
        int rokWydania;
        char gatunek[20];
        char platforma[10];

    public:
        gra();

    //settery:
       /*bool setNazwa(char *naz);
        bool setCena();
        bool setSztuk();
        bool setRok();
        bool setGatunek();
        bool setPlatform();*/  //na razie bez tego, zobaczymy czy bedzie sie dało

    //gettery:
        char* getNazwa();  
        float getCena();
        int getSztuk();
        int getRok();
        char* getGatunek();
        char* getPlatform();

        void getAll(char *naz, float cen, int szt, int rok, char *gat, char *plat); //bedzie zbierac wszystko, parametry do zrobienia
        void display(); //temporarne

        

};

class bazaGra:public gra{ 
    protected:
        int current; //indeks aktualny
        int currentFound; 
        int currentKosz;

        vector <gra> tab;
        vector <gra> found;
        vector <gra> bin;

    public:
        bazaGra();
        

        int setCurrent(int index, vector<gra> typ, currentType rodzaj);
        int getCurrent(currentType typ);
        int& getCurrentRef(currentType typ);


        bool universalDisplay(vector <gra> typ);
        vector<gra>& getVector(currentType typ);

        void clearInput();

        void getChar(char *prompt, char *fail, char *dest, int max);
        int getInt(char *prompt, char *fail, int min, int max);
        float getFloat(char *prompt, char *fail, int min, int max);

        //bool zbierzDane();
        bool dodaj(gra g);

        bool sprawdzRozmiar(currentType typ);

        bool sortujPoNazwie(bool rosnaco);
        bool sortujPoCenie(bool rosnaco);
        bool sortujPoDacie(bool rosnaco);

        bool usun();
        bool usunWszystko();

        bool saveFile();
        bool readFile();

        bool next();
        bool previous();
        void showCurrent(int current, vector<gra> typ);

};

class kosz:public bazaGra{
    
    public:
        kosz();

        bool czyscKosz();
        bool przywrocBiezacy();
        bool przywrocWszystko();

        bool nextKosz();
        bool previousKosz();
};

class szukanie:public kosz{

    public:
        szukanie();
        //void menuSzukanie();

        bool poNazwie(char szukana[]);
        bool poCenie(float min, float max);
        bool poGatunku(char szukana[]);
        bool poPlatformie(char szukana[]);

        bool czyscFound();

        bool nextFound();
        bool previousFound();


};

