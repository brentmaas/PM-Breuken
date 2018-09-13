/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: Main.cpp
 * Functie: Selectie voor een betastudie, of eventueel een alfastudie.
 * Getest op: Windows 10 + MSys2 (MinGW), gcc 8.2.0
 * Getest met: g++ Assignment1 Main.cpp -std=c++17 -Wall
 * Laatst bewerkt: 13/09/2018
 */

#include <iostream>
#include <ctime>
#include <string>

const std::string infoBlokje = ""
		"/////////////////// INFOBLOK ///////////////////\n"
		"Naam: Brent Maas (s1826247)\n"
		"Jaar van aankomst: 2016\n"
		"Studierichting: Natuur- & Sterrenkunde + minor Data Science\n"
		"Studentnummer: s1826247\n"
		"Opgave: Breuken\n"
		"\n"
		"In dit programma wordt van de gebruiker verwacht dat deze enkele vragen\n"
		"beantwoord. Aan de hand van deze antwoorden wordt bepaald of deze\n"
		"persoon een betastudie, of eventueel alfastudie, mag doen.\n"
		"\n"
		"Laatst bewerkt: 13/09/2018\n"
		"////////////////////////////////////////////////\n";

//Dagen per maand als getal, met een nul ervoor om niet telkens dagenInMaand[maand-1] te hoeven doen
const int dagenInMaand[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::string dagenVanWeek[] = {"m", "di", "w", "do", "v", "za", "zo"};

int main(int argc, char **argv){
	std::cout << infoBlokje << std::endl;
	
	std::time_t t = std::time(nullptr);
	char cstr[9]; //8 karakters + 1 nulltermination voor de tijd
	std::strftime(cstr, sizeof(cstr), "%d%m%Y", std::localtime(&t)); //Vraag huidige ddmmyyyy op
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
	int jaren = jaarNu - gebJaar;
	if(jaren < 10){ //Persoon is uiterlijk 8 of 9
		std::cout << "Sorry, je bent te jong voor deze opleiding." << std::endl;
		return 1;
	}else if(jaren > 102){ //Persoon is minimaal 101 of 102
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	std::cout << "Voer alstublieft uw geboortemaand in: ";
	std::cin >> gebMaand;
	if(gebMaand < 1 || gebMaand > 12){
		std::cout << "De ingevoerde maand in ongeldig." << std::endl;
		return 1;
	}
	int maanden = maandNu - gebMaand;
	if(maanden < 0) jaren--; //Nog niet jarig geweest dit jaar
	if(jaren < 10 && maanden < 0){ //Persoon is zeker 9
		std::cout << "Sorry, je bent te jong voor deze opleiding." << std::endl;
		return 1;
	}else if(jaren > 100 && maanden > 0){ //Persoon is zeker 101
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	std::cout << "Voer alstublieft uw geboortedag in: ";
	std::cin >> gebDag;
	
	int maxDag = dagenInMaand[gebMaand];
	if(gebJaar % 4 == 0 && gebMaand == 2) maxDag++; //Februari van een schrikkeljaar
	if(gebDag < 1 || gebDag > maxDag){
		std::cout << "De ingevoerde dag is ongeldig." << std::endl;
		return 1;
	}
	int dagen = dagNu - gebDag;
	if(dagen < 0) maanden--; //Nog niet maandig geweest deze maand
	if(maanden == -1 && dagen < 0) jaren--; //Nog niet jarig geweest, maar niet eerder gecorrigeerd
	
	if(maanden < 0) maanden += 12; //Check om de maand geldig te houden (jaar al gecorrigeerd)
	
	if(jaren < 10){ //Persoon is zeker 9
		std::cout << "Sorry, je bent te jong voor deze opleiding." << std::endl;
		return 1;
	}else if(jaren > 100){ //Persoon is zeker 101
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	
	int leeftijdMaanden = maanden + jaren * 12;
	
	std::cout << "Leeftijd: " << jaren << " jaar en " << maanden << " maanden. Of " << leeftijdMaanden << " maanden." << std::endl;
	
	std::string onderwerp = jaren >= 30 ? "u" : "jij";
	std::string onderwerpCap = jaren >= 30 ? "U" : "Jij";
	std::string bezittelijkVnw = jaren >= 30 ? "uw" : "je";
	std::string bezittelijkVnwCap = jaren >= 30 ? "Uw" : "Je";
	
	//Jarig
	if(gebMaand == maandNu && gebDag == dagNu) std::cout << "Gefeliciteerd met " << bezittelijkVnw << " verjaardag!" << std::endl;
	//Maandig
	else if(gebDag == dagNu) std::cout << "Gefeliciteerd met " << bezittelijkVnw << " vermaandag!" << std::endl;
	
	std::string dagVanWeek;
	std::cout << "Op welke dag van de week bent u geboren [m,di,w,do,v,za,zo]? " << std::endl;
	std::cin >> dagVanWeek;
	
	//Nu pas uitrekenen zodat de gebruiker niet vals kan spelen door in het geheugen te kijken
	
	int geboortedagVanWeek = 1; //Begin op dinsdag 1 januari 1901 (dagenVanWeek[1] = "di")
	geboortedagVanWeek += gebJaar - 1901; //1 dag verder in de week per jaar
	//1 extra dag verder in de week per schrikkeljaar (1901, 1905, 1909,... worden hier als schikkeljaren gerekend omdat daar de schrikkeldag al is gebeurd
	geboortedagVanWeek += (gebJaar - 1901) / 4;
	for(int i = 1;i < gebMaand;i++) geboortedagVanWeek += dagenInMaand[i]; //Per maand de dagen optellen
	geboortedagVanWeek += gebDag - 1; //Tel dag op (-1, want we begonnen op de eerste van de maand)
	if(gebJaar % 4 == 0 && (gebMaand > 2 || (gebMaand == 2 && gebDag == 29))) geboortedagVanWeek++; //Een dag verder als 29 februari al geweest is dit jaar
	geboortedagVanWeek = geboortedagVanWeek % 7; //Terugbrengen in [0,6]
	if(dagVanWeek != dagenVanWeek[geboortedagVanWeek]){ //Als de gebruiker het fout heeft
		std::cout << "Fout, het antwoord is \'" << dagenVanWeek[geboortedagVanWeek] << ".\' " << onderwerpCap << " bent geweigerd." << std::endl;
		return 1;
	}else std::cout << "Correct!" << std::endl;
	
	srand(std::time(0)); //Initialiseer de random-generator met de systeemtijd
	//Willekeurige getallen voor tellers [0,19] en noemers [1,19]
	int teller1 = rand() % 20, teller2 = rand() % 20, noemer1 = rand() % 19 + 1, noemer2 = rand() % 19 + 1, plusmin = 1 - 2 * (rand() % 2);
	const float antwoord = (float) teller1 / noemer1 + plusmin * (float) teller2 / noemer2;
	const float maxFout = 0.1;
	std::cout << "Wat is " << teller1 << "/" << noemer1 << (plusmin == 1 ? "+" : "-") << teller2 << "/" << noemer2 << "?" << std::endl;
	std::cout << teller1 << " " << teller2 << " " << noemer1 << " " << noemer2 << " " << plusmin << " " << antwoord << std::endl;
	int tellerAntwoord = teller1 * noemer2 + plusmin * teller2 * noemer1, noemerAntwoord = noemer1 * noemer2;
	int ggv = 1; //Grootst gemeenschappelijke veelvoud
	//Bereken de ggv, de maximaal mogelijke ggv is de kleinste van de noemer en de teller
	for(int i = 1;i < std::min(tellerAntwoord, noemerAntwoord);i++) if(tellerAntwoord % i == 0 && noemerAntwoord % i == 0) ggv = i;
	tellerAntwoord /= ggv;
	noemerAntwoord /= ggv;
	
}