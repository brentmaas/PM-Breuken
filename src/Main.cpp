/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: Main.cpp
 * Functie: Selectie voor een betastudie, of eventueel een alfastudie.
 * Getest met: g++ Assignment1 Main.cpp -std=c++17 -Wall
 * Laatst bewerkt: 06/09/2018
 */

#include <iostream>
#include <ctime>
#include <string>

const std::string infoBlokje = ""
		"////////////////////////////////////////////////\n"
		"Naam: Brent Maas\n"
		"Jaar van aankomst: 2016\n"
		"Studierichting: Natuur- & Sterrenkunde + minor Data Science\n"
		"Studentnummer: s1826247\n"
		"Opgave: Breuken\n"
		"\n"
		"In dit programma wordt van de gebruiker verwacht dat deze enkele vragen\n"
		"beantwoord. Aan de hand van deze antwoorden wordt bepaald of deze\n"
		"persoon een betastudie, of eventueel alfastudie, mag doen.\n"
		"\n"
		"Laatst bewerkt: 06/09/2018\n"
		"////////////////////////////////////////////////\n";

int main(int argc, char **argv){
	std::cout << infoBlokje << std::endl;
	
	std::time_t t = std::time(nullptr);
	char cstr[9]; //8 karakters + 1 nulltermination
	std::strftime(cstr, sizeof(cstr), "%d%m%Y", std::localtime(&t));
	std::string str(cstr);
	int jaarNu = std::atoi(str.substr(4, 4).c_str());
	int maandNu = std::atoi(str.substr(2, 2).c_str());
	int dagNu = std::atoi(str.substr(0, 2).c_str());
	
	int gebJaar, gebMaand, gebDag;
	std::cout << "Voer alstublieft uw geboortejaar in: ";
	std::cin >> gebJaar;
	if(gebJaar > jaarNu){
		std::cout << "Het is niet mogelijk een jaar in de toekomst in te vullen." << std::endl;
		return 1;
	}
	std::cout << "Voer alstublieft uw geboortemaand in: ";
	std::cin >> gebMaand;
	if(gebMaand < 0 || gebMaand > 12){
		std::cout << "De ingevoerde maand in ongeldig." << std::endl;
		return 1;
	}
	std::cout << "Voer alstublieft uw geboortedag in: ";
	std::cin >> gebDag;
	
	
	
	int jaren = jaarNu - gebJaar;
	int maanden1 = maandNu - gebMaand;
	if(maandNu < gebMaand){
		jaren--;
		maanden1 += 12;
	}
	if(dagNu < gebDag) maanden1--;
	while(maanden1 < 0) maanden1 += 12;
	while(maanden1 > 12) maanden1 -= 12;
	int maanden2 = maanden1 + jaren * 12;
}