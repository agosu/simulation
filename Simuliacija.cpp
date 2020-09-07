#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "deque.h"
#include "deque.c"
#include "Bigint.h"
#include "Bigint.cpp"
#include "queue.c"
#include "queue.h"
#include "queue_data.h"

using namespace std;

typedef struct Darbuotoja{
	int laikas_tvarkymui;
	bool laisva;
	int darbas_su_studentais;
	int darbas_tvarkant_tarp;
	int darbas_tvarkant_po;
	int visas_darbo_laikas;
	int visas_poilsiavimo_laikas;
	int iki_studento_pabaigos;
	int iki_tvarkymo_pabaigos;
	int baigta;
	double uzimtumas;
} Darbuotoja;

void dirbk(Darbuotoja &darbuotoja, Bigint laikas, Bigint studentu_priemimo_pabaiga, queue &studentai, int laikas_studentui, deque *lentyna, bool frontas, string &to_file){
    string laikas_studentui_string = to_string(laikas_studentui);
	if(laikas < studentu_priemimo_pabaiga){
 			if(darbuotoja.laisva){ // jei laisva
 				if(!isEmpty(studentai) && laikas < (studentu_priemimo_pabaiga - (Bigint)laikas_studentui_string)){ // jei yra studentu eileje
 					darbuotoja.laisva = false;
 					darbuotoja.iki_studento_pabaigos = laikas_studentui - 1;
 					to_file = "laisva ir ima studenta, liko: " + to_string(darbuotoja.iki_studento_pabaigos + 1) + "\r\n";
 					darbuotoja.iki_tvarkymo_pabaigos = 0;
 					bool x;
 					dequeue(&studentai, &x);
 				}
 				else if(!deque_is_empty(lentyna)){ // jei yra tvarkymo
 					darbuotoja.laisva = false;
 					darbuotoja.iki_tvarkymo_pabaigos = darbuotoja.laikas_tvarkymui - 1;
 					to_file = "laisva ir ima tvarkyti, liko: " + to_string(darbuotoja.iki_tvarkymo_pabaigos + 1) + "\r\n";
 					darbuotoja.iki_studento_pabaigos = 0;
                    deque_pop_front(lentyna);
 				}
 				else{ // poilsiauja
 				    to_file = "poilsiauja\r\n";
                    darbuotoja.visas_poilsiavimo_laikas++;
 				}
 			}
 			else{ // uzimta (studentu arba tvarkymu)
 				if(darbuotoja.iki_studento_pabaigos != 0){ // jei uzsiemus studentu
 					darbuotoja.iki_studento_pabaigos--;
 					to_file = "uzimta studentu, liko: " + to_string(darbuotoja.iki_studento_pabaigos + 1) + "\r\n";
 					darbuotoja.darbas_su_studentais++;
 					if(darbuotoja.iki_studento_pabaigos == 0){ // jei baige su studentu
 						if(frontas){
 							deque_push_front(lentyna, true);
 						}
 						else{
 							deque_push_back(lentyna, true);
 						}
 						darbuotoja.laisva = true;
 					}
 				}
 				else{ // jei uzsiemus tvarkymu
 					darbuotoja.iki_tvarkymo_pabaigos--;
 					to_file = "uzimta tvarkymu, liko: " + to_string(darbuotoja.iki_tvarkymo_pabaigos + 1) + "\r\n";
 					darbuotoja.darbas_tvarkant_tarp++;
 					if(darbuotoja.iki_tvarkymo_pabaigos == 0){
 						darbuotoja.laisva = true;
 					}
 				}
 			}
 		}
 	else{
 		if(darbuotoja.laisva){ // jeigu baige dokumenta
 			if(!deque_is_empty(lentyna)){ // jei dar yra dokumentu lentynoje
 				darbuotoja.laisva = false;
 				darbuotoja.iki_tvarkymo_pabaigos = darbuotoja.laikas_tvarkymui - 1;
 				to_file = "po darbo laisva ir ima dokumenta, liko: " + to_string(darbuotoja.iki_tvarkymo_pabaigos + 1) + "\r\n";
 				deque_pop_front(lentyna);
 			}
 			else{ // jei baige dokumenta ir nebera daugiau
 			    to_file = "baige\r\n";
 				darbuotoja.baigta = true;
 			}
 		}
 		else{ // jeigu dar tvarko dokumenta
 			darbuotoja.iki_tvarkymo_pabaigos--;
 			to_file = "po darbo tvarko dokumentus, liko: " + to_string(darbuotoja.iki_tvarkymo_pabaigos + 1) + "\r\n";
 			darbuotoja.darbas_tvarkant_po++;
 			if(darbuotoja.iki_tvarkymo_pabaigos == 0){
 				darbuotoja.laisva = true;
 			}
 		}
 	}
}

int main() {
	Bigint laikas("1");
	deque *lentyna = deque_alloc();
	int laikas_studentui;
	bool baigta = false;
	Bigint studentu_priemimo_pabaiga;

	ifstream duomenys("duomenys.txt");
	duomenys >> laikas_studentui;
	string x;
	duomenys >> x;
	studentu_priemimo_pabaiga = (Bigint)x;
	int tikimybe;
	duomenys >> tikimybe;

	string to_file;
	ofstream rez_kiekviena_akimirka("rez_kiekviena_akimirka.txt");
    ofstream rez_galutiniai_duomenys("rez_galutiniai_duomenys.txt");

	Darbuotoja darbuotoja1;
	duomenys >> darbuotoja1.laikas_tvarkymui;
	darbuotoja1.laisva = true;
	darbuotoja1.darbas_su_studentais = 0;
	darbuotoja1.darbas_tvarkant_po = 0;
	darbuotoja1.darbas_tvarkant_tarp = 0;
	darbuotoja1.visas_poilsiavimo_laikas = 0;
	darbuotoja1.baigta = false;

	Darbuotoja darbuotoja2;
	duomenys >> darbuotoja2.laikas_tvarkymui;
	darbuotoja2.laisva = true;
	darbuotoja2.darbas_su_studentais = 0;
	darbuotoja2.darbas_tvarkant_po = 0;
	darbuotoja2.darbas_tvarkant_tarp = 0;
	darbuotoja2.visas_poilsiavimo_laikas = 0;
	darbuotoja2.baigta = false;

 	queue studentai;
 	create(&studentai);

 	duomenys.close();

    int r = 12;
    double atejo = 0;
    double neatejo = 0;
 	for(; !baigta; laikas = laikas + (Bigint)"1", r++){ // kiekvienu laiko momentu iki kol abi baigs
        rez_kiekviena_akimirka << laikas << endl;
        srand(time(nullptr) - r);
 		if(laikas < studentu_priemimo_pabaiga){
 			if(rand() % (100 / tikimybe) == 0){
 			    rez_kiekviena_akimirka << "Atėjo studentas" << endl;
 			    atejo++;
                enqueue(&studentai, true);
 			}
 			else{
                rez_kiekviena_akimirka << "Neatėjo studentas" << endl;
                neatejo++;
            }
 		}
 		dirbk(darbuotoja1, laikas, studentu_priemimo_pabaiga, studentai, laikas_studentui, lentyna, true, to_file);
 		rez_kiekviena_akimirka << "Pirma darbuotoja: " << to_file;
 		dirbk(darbuotoja2, laikas, studentu_priemimo_pabaiga, studentai, laikas_studentui, lentyna, false, to_file);
 		rez_kiekviena_akimirka << "Antra darbuotoja: " << to_file << endl;
 		if(darbuotoja1.baigta && darbuotoja2.baigta){
 			baigta = true;
 		}
 	}

    destroy(&studentai);

 	darbuotoja1.visas_darbo_laikas = darbuotoja1.darbas_su_studentais + darbuotoja1.darbas_tvarkant_tarp; // be darbo po studentu priemimo laiko
    darbuotoja1.uzimtumas = (double)darbuotoja1.visas_darbo_laikas / ((double)darbuotoja1.visas_darbo_laikas + (double)darbuotoja1.visas_poilsiavimo_laikas);
    darbuotoja2.visas_darbo_laikas = darbuotoja2.darbas_su_studentais + darbuotoja2.darbas_tvarkant_tarp; // be darbo po studentu priemimo laiko
    darbuotoja2.uzimtumas = (double)darbuotoja2.visas_darbo_laikas / ((double)darbuotoja2.visas_darbo_laikas + (double)darbuotoja2.visas_poilsiavimo_laikas);

 	rez_galutiniai_duomenys << "Papildomas darbo laikas prašymų tvarkymui po studentų priėmimo pabaigos:" << endl;
 	rez_galutiniai_duomenys << "pirma darbuotoja: " << darbuotoja1.darbas_tvarkant_po << endl;
 	rez_galutiniai_duomenys << "antra darbuotoja: " << darbuotoja2.darbas_tvarkant_po << endl << endl;
 	rez_galutiniai_duomenys << "Užimtumas:" << endl;
 	rez_galutiniai_duomenys << "pirma darbuotoja: " << darbuotoja1.uzimtumas * 100 << "%" << endl;
 	rez_galutiniai_duomenys << "antra darbuotoja: " << darbuotoja2.uzimtumas * 100 << "%" << endl;

 	rez_galutiniai_duomenys.close();
 	rez_kiekviena_akimirka.close();
 	//cout << atejo / (atejo + neatejo) * 100;
}}}}}
