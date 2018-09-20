/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maas1.cc
 * Functie: Selectie voor een betastudie, of eventueel een alfastudie.
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 7.3.0
 *            Ubuntu 16.04 LTS met g++ 5.4.0
 * Getest met: g++ -o Assignment1 maas1.cc -std=c++17 -Wall -Wextra
 *             g++ -o Assignment1 maas1.cc -std=c++11 -Wall -Wextra
 * Laatst bewerkt: 20/09/2018
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
		"In dit programma wordt van de gebruiker verwacht dat deze enkele\n"
		"vragen beantwoord. Aan de hand van deze antwoorden wordt bepaald of\n"
		"deze persoon een betastudie, of eventueel een alfastudie, mag doen.\n"
		"\n"
		"Laatst bewerkt: 20/09/2018\n"
		"////////////////////////////////////////////////\n";

//Dagen per maand als getal, met een nul ervoor om niet telkens
//dagenInMaand[maand-1] te hoeven doen
const int dagenInMaand[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::string dagenVanWeek[] = {"m", "di", "w", "do", "v", "za", "zo"};

int main(){
	srand(std::time(0)); //Initialiseer de random-generator met de systeemtijd
	
	std::cout << infoBlokje << std::endl;
	
	const std::time_t t = std::time(nullptr); //Creeer een tijdsinstantie
	char cstr[9]; //8 karakters + 1 nulltermination voor de tijd
	//Vraag huidige datum in ddmmyyyy op
	std::strftime(cstr, sizeof(cstr), "%d%m%Y", std::localtime(&t));
	//Maak er een c++-string van, in plaats van een c-string
	std::string str(cstr);
	//Haal dd, mm en yyyy los van elkaar uit de string en maak er integers van
	const int jaarNu = std::atoi(str.substr(4, 4).c_str());
	const int maandNu = std::atoi(str.substr(2, 2).c_str());
	const int dagNu = std::atoi(str.substr(0, 2).c_str());
	
	int gebJaar, gebMaand, gebDag; //Geboortejaar, -maand, -dag
	//Vraag het geboortejaar aan
	std::cout << "Voer alstublieft uw geboortejaar in: ";
	std::cin >> gebJaar;
	if(gebJaar > jaarNu){ //Test of een toekomstig jaar is ingevuld
		std::cout << "Het is niet mogelijk een jaar "
				"in de toekomst in te vullen." << std::endl;
		return 1;
	}
	int jaren = jaarNu - gebJaar; //Jarencomponent van de leeftijd
	if(jaren < 10){ //Persoon is uiterlijk 8 of 9
		std::cout << "Sorry, je bent te jong voor deze opleiding" << std::endl;
		return 1;
	}else if(jaren > 101){ //Persoon is minimaal 101 of 102
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	//Vraag de geboortemaand aan
	std::cout << "Voer alstublieft uw geboortemaand in: ";
	std::cin >> gebMaand;
	if(gebMaand < 1 || gebMaand > 12){ //Controleer op ongeldige maand
		std::cout << "De ingevoerde maand in ongeldig." << std::endl;
		return 1;
	}
	int maanden = maandNu - gebMaand; //Maandencomponent van de leeftijd
	if(maanden < 0) jaren--; //Nog niet jarig geweest dit jaar
	if(jaren < 10 && maanden < 0){ //Persoon is zeker 9 of jonger
		std::cout << "Sorry, je bent te jong voor deze opleiding" << std::endl;
		return 1;
	}else if(jaren > 100 && maanden > 0){ //Persoon is zeker 101 of ouder
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	//Vraag de geboortedag aan
	std::cout << "Voer alstublieft uw geboortedag in: ";
	std::cin >> gebDag;
	
	int maxDag = dagenInMaand[gebMaand]; //De laatste dag in de maand
	//Februari van een schrikkeljaar
	if(gebJaar % 4 == 0 && gebMaand == 2) maxDag++;
	if(gebDag < 1 || gebDag > maxDag){ //Controleer op ongeldige dag
		std::cout << "De ingevoerde dag is ongeldig." << std::endl;
		return 1;
	}
	int dagen = dagNu - gebDag; //Dagencomponent van de leeftijd
	if(dagen < 0) maanden--; //Nog niet maandig geweest deze maand
	//Nog niet jarig geweest, maar niet eerder gecorrigeerd
	if(maanden == -1 && dagen < 0) jaren--;
	
	//Check om de maand geldig te houden (jaar al gecorrigeerd)
	if(maanden < 0) maanden += 12;
	
	if(jaren < 10){ //Persoon is zeker 9 of jonger
		std::cout << "Sorry, je bent te jong voor deze opleiding" << std::endl;
		return 1;
	}else if(jaren > 100){ //Persoon is zeker 101 of ouder
		std::cout << "Sorry, u bent te oud voor deze opleiding" << std::endl;
		return 1;
	}
	
	int leeftijdMaanden = maanden + jaren * 12; //Leeftijd in maanden
	
	//Print de leeftijden
	std::cout << "Leeftijd: " << jaren << " jaar en " << maanden << " maanden."
			" Of " << leeftijdMaanden << " maanden." << std::endl;
	
	//Bereken de zinsdelen die gebruikt gaan worden
	std::string onderwerp = jaren >= 30 ? "u" : "jij";
	std::string onderwerpCap = jaren >= 30 ? "U" : "Jij";
	std::string bezittelijkVnw = jaren >= 30 ? "uw" : "je";
	
	//Jarig
	if(gebMaand == maandNu && gebDag == dagNu) std::cout << "Gefeliciteerd "
			"met " << bezittelijkVnw << " verjaardag!" << std::endl;
	//Maandig
	else if(gebDag == dagNu) std::cout << "Gefeliciteerd "
			"met " << bezittelijkVnw << " vermaandag!" << std::endl;
	
	//Vraag dag van de week op geboortedag aan
	std::string dagVanWeek;
	std::cout << "Op welke dag van de week bent " << onderwerp << " geboren "
			"[m,di,w,do,v,za,zo]? " << std::endl;
	std::cin >> dagVanWeek;
	
	//Nu pas uitrekenen zodat de gebruiker niet vals kan spelen door
	//in het geheugen te kijken
	
	//Begin op dinsdag 1 januari 1901 (dagenVanWeek[1] = "di")
	int geboortedagVanWeek = 1;
	geboortedagVanWeek += gebJaar - 1901; //1 dag verder in de week per jaar
	//1 extra dag verder in de week per schrikkeljaar (1901, 1905, 1909,...
	//worden hier als schikkeljaren gerekend omdat daar de schrikkeldag
	//al is geweest
	geboortedagVanWeek += (gebJaar - 1901) / 4;
	//Per maand de dagen optellen
	for(int i = 1;i < gebMaand;i++) geboortedagVanWeek += dagenInMaand[i];
	//Tel dag op (-1, want we begonnen op de eerste van de maand)
	geboortedagVanWeek += gebDag - 1;
	//Een dag verder als 29 februari al geweest is dit jaar
	if(gebJaar % 4 == 0 && (gebMaand > 2 || (gebMaand == 2 && gebDag == 29)))
		geboortedagVanWeek++;
	geboortedagVanWeek = geboortedagVanWeek % 7; //Terugbrengen in [0,6]
	//Als de gebruiker het fout heeft
	if(dagVanWeek != dagenVanWeek[geboortedagVanWeek]){
		std::cout << "Fout, het antwoord is \'" <<
			dagenVanWeek[geboortedagVanWeek] << ".\' " << onderwerpCap <<
			" bent geweigerd." << std::endl;
		return 1;
	}else std::cout << "Correct!" << std::endl; //Anders goed
	
	//Willekeurige getallen voor tellers in [0,19] en noemers in [1,19]
	int teller1 = rand() % 20, teller2 = rand() % 20, noemer1 = rand() % 19 + 1
			, noemer2 = rand() % 19 + 1, plusmin = 1 - 2 * (rand() % 2);
	
	//Stel de vraag en vraag antwoorden op
	std::cout << "Wat is " << teller1 << "/" << noemer1 <<
			(plusmin == 1 ? "+" : "-") << teller2 << "/" << 
			noemer2 << "?" << std::endl;
	int teller, noemer;
	std::cout << "Teller: ";
	std::cin >> teller;
	std::cout << "Noemer: ";
	std::cin >> noemer;
	
	//Bereken de teller en noemer van het antwoord
	int tellerAntwoord = teller1 * noemer2 + plusmin * teller2 * noemer1, 
		noemerAntwoord = noemer1 * noemer2;
	int ggv = 1; //Grootst gemeenschappelijke veelvoud
	//Bereken de ggv,
	//de maximaal mogelijke ggv is de kleinste van de noemer en de teller
	for(int i = 2;i < std::min(abs(tellerAntwoord), abs(noemerAntwoord))+1;i++)
		if(abs(tellerAntwoord) % i == 0 && abs(noemerAntwoord)%i == 0) ggv = i;
	//Vereenvoudig het antwoord
	tellerAntwoord /= ggv;
	noemerAntwoord /= ggv;
	
	int ggv2 = 1; //Doe ggv opnieuw met antwoord van gebruiker
	for(int i = 2;i < std::min(abs(teller), abs(noemer)) + 1;i++)
		if(abs(teller) % i == 0 && abs(noemer) % i == 0) ggv2 = i;
	//Vereenvoudig
	teller /= ggv2;
	noemer /= ggv2;
	
	const double maxFout = 0.1;
	//Bereken het antwoord als decimaal getal
	const double antwoord = (double) teller1 / noemer1 
			+ plusmin * (double) teller2 / noemer2;
	//Als het antwoord van de gebruiker goed was
	if(teller == tellerAntwoord && noemer == noemerAntwoord){
		std::cout << "Correct! En nu als decimaal getal (+/- " <<
				maxFout << ")? ";
		double dec; //Antwoord van gebruiker als decimaal getal
		std::cin >> dec; //Vraag antwoord van gebruiker aan
		//Als het antwoord binnen de grenzen goed is
		if(dec - maxFout <= antwoord && antwoord <= dec + maxFout){
			std::cout << "Gefeliciteerd! " << onderwerpCap <<
				" bent toegelaten tot de betastudie!" << std::endl;
			return 0; //Beeindig het programma
		}
	}
	//Vanaf hier waren niet alletwee de antwoorden goed
	std::cout << "Fout! Het antwoord was " << tellerAntwoord << "/" <<
		noemerAntwoord << " = " << antwoord << std::endl;
	std::cout << "Om nog toegelaten te worden tot een alfastudie, "
			"beantwoord de volgende vraag:" << std::endl;
	if(jaren >= 30){ //Vraag voor 30+
		std::cout << "Wie is de schrijver van \"Het Behouden Huis\"?"
			<< std::endl;
		std::cout << "A) Harry Mulisch" << std::endl;
		std::cout << "B) Willem Frederik Hermans" << std::endl; //Antwoord
		std::cout << "C) Gerard van het Reve" << std::endl;
		std::cout << "D) Jan Wolkers" << std::endl;
	}else{ //Vraag voor 29-
		std::cout << "Wie is de schrijver van \"De Ontdekking van de Hemel\"?"
				<< std::endl;
		std::cout << "A) Willem Frederik Hermans" << std::endl;
		std::cout << "B) Harry Mulisch" << std::endl; //Antwoord
		std::cout << "C) Jan Wolkers" << std::endl;
		std::cout << "D) Gerard van het Reve" << std::endl;
	}
	std::string antw; //Het antwoord van de gebruiker
	std::cin >> antw; //Vraag antwoord aan
	if(antw == "B" || antw == "b"){ //Als het antwoord goed is
		std::cout << "Gefeliciteerd! " << onderwerpCap << " bent toegelaten "
				"voor een alfastudie!" << std::endl;
		return 0; //Beeindig
	}
	//Vanaf hier was het antwoord fout
	std::cout << "Fout! Het antwoord is B. " << onderwerpCap << " bent ook "
			"voor de alfastudie geweigerd." << std::endl;
	return 1;
}