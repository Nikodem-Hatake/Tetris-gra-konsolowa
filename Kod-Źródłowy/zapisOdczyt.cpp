#include "header.hpp"

//Zapis do pliku wszystkich danych gracza.
void Zapisz(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka, uint64_t & rekord)
{
	std::cout << "Trwa zapisywanie..." << '\n';
	std::fstream plik;
	plik.open("UstawieniaOrazRekord.txt", std::ios::out);
	if(plik.good())
	{
		plik << znakKlocka << '\n' << kolorKlocka << '\n' << rekord << '\n';
		plik.close();
		std::cout << "Zapisano ^^" << '\n';
	}
	else
	{
		std::cout << "Nieudalo sie zapisac ustawien oraz rekordu do pliku" << '\n';
		std::cout << "Sprawdz czy plik z tymi rzeczami jest w tej samej sciezce co plik Tetris.exe";
		std::cout << "oraz ma uprawnienia pozwalajace na zapis i odczyt" << '\n';
	}
}

//Wczytanie ustawieñ oraz rekordu gracza.
void Odczyt(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka, uint64_t & rekord)
{
	std::fstream plik;
	plik.open("UstawieniaOrazRekord.txt", std::ios::in | std::ios::binary);
	if(plik.good())
	{
		//Pomocnicze zmienne poniewa¿ niemo¿na zapisaæ odrazu do zmiennych typu atomic danych z pliku.
		char tempZnakKlocka = '1';
		short tempKolorKlocka = 3;
		plik >> tempZnakKlocka >> tempKolorKlocka >> rekord;
		znakKlocka = tempZnakKlocka;
		kolorKlocka = tempKolorKlocka;
		if(znakKlocka < 10)	//Je¿eli znak klocka by³ liczb¹, zostanie na ni¹ zamieniony jako char.
		{
			znakKlocka += 48;
		}
		plik.close();
	}
	else
	{
		std::cout << "Nieudalo sie otworzyc pliku z ustawieniami oraz zapisanym rekordem :(" << '\n';
		std::cout << "Sprawdz czy plik z tymi rzeczami jest w tej samej sciezce co plik Tetris.exe";
		std::cout << "oraz ma uprawnienia pozwalajace na zapis i odczyt" << '\n';
	}
}