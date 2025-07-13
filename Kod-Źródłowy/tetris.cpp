#include "header.hpp"

void Tetris(bool plansza[][10], std::atomic_char * znak, std::atomic_bool * czyTrwaGra, 
std::atomic_uint64_t * punkty, std::atomic_char * znakKlocka, std::atomic_short * kolorKlocka)
{
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	auto zegar = std::chrono::system_clock::now();
	bool klocek[4][4] {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	bool czyNowyKlocek = true;
	bool czyPowstalKlocek = true;
	bool czyWcisnietyKlawiszOpadania = false;
	int8_t indeksJedenKlocka = 3;	//Zmienna wykorzystywana do operacji z klockiem na planszy.
	int8_t obecnaPozycjaKlockaWPionie = 1;
	std::pair <short, short> pozycjaLewoPrawo {0, 0};	//first - lewo, second - prawo.
	auto ziarnoGenerowania = time(0);
	std::default_random_engine generator(ziarnoGenerowania);
	std::uniform_int_distribution <short> zakresKlocka(1, 10);
	std::uniform_int_distribution <short> zakresLewoPrawo(0, 6);
	while(* czyTrwaGra)
	{
		//Tworzenie klocka.
		if(czyNowyKlocek)
		{
			//Czysczenie klocka.
			for(int8_t indeksJeden = 0; indeksJeden < 4; indeksJeden ++)
			{
				for(int8_t indeksDwa = 0; indeksDwa < 4; indeksDwa ++)
				{
					klocek[indeksJeden][indeksDwa] = 0;
				}
			}
			obecnaPozycjaKlockaWPionie = 0;
			//Losowanie klocka.
			short wylosowanyKlocek = zakresKlocka(generator);
			if(wylosowanyKlocek <= 2)
			{

				klocek[3][0] = 1;
				klocek[3][1] = 1;
				klocek[3][2] = 1;
				klocek[3][3] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator);
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 3;
			}
			else if(wylosowanyKlocek <= 4)
			{
				klocek[0][0] = 1;
				klocek[1][0] = 1;
				klocek[2][0] = 1;
				klocek[3][0] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 3;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first;
			}
			else if(wylosowanyKlocek <= 6)
			{
				klocek[3][0] = 1;
				klocek[3][1] = 1;
				klocek[3][2] = 1;
				klocek[2][2] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 1;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 2;
			}
			else if(wylosowanyKlocek == 7)
			{
				klocek[3][0] = 1;
				klocek[3][1] = 1;
				klocek[3][2] = 1;
				klocek[2][0] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 1;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 2;
			}
			else if(wylosowanyKlocek == 8)
			{
				klocek[2][0] = 1;
				klocek[2][1] = 1;
				klocek[3][0] = 1;
				klocek[3][1] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 2;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 1;
			}
			else if(wylosowanyKlocek == 9)
			{
				klocek[3][0] = 1;
				klocek[3][1] = 1;
				klocek[2][1] = 1;
				klocek[2][2] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 1;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 2;
			}
			else
			{
				klocek[2][0] = 1;
				klocek[2][1] = 1;
				klocek[3][1] = 1;
				klocek[3][2] = 1;
				pozycjaLewoPrawo.first = zakresLewoPrawo(generator) + 1;
				pozycjaLewoPrawo.second = pozycjaLewoPrawo.first + 2;
			}
			czyNowyKlocek = false;
			czyPowstalKlocek = true;
		}
		system("cls");
		//Czyszczenie poprzedniego miejsca klocka.
		indeksJedenKlocka = 3;
		for(int8_t indeksJeden = obecnaPozycjaKlockaWPionie - 1; indeksJeden != -1
			&& indeksJeden >= obecnaPozycjaKlockaWPionie - 4; indeksJeden --)
		{
			int8_t indeksDwa = pozycjaLewoPrawo.first;
			for(int8_t indeksDwaKlocka = 0; indeksDwaKlocka < 4; indeksDwaKlocka ++)
			{
				if(klocek[indeksJedenKlocka][indeksDwaKlocka])
				{
					plansza[indeksJeden][indeksDwa] = 0;
				}
				indeksDwa ++;
			}
			indeksJedenKlocka --;
		}
		zegar = std::chrono::system_clock::now() + std::chrono::milliseconds(1100);
		//Sprawdzanie czy klocek nie jest na samym dole.
		if(obecnaPozycjaKlockaWPionie == 11)
		{
			czyNowyKlocek = true;
			if(czyWcisnietyKlawiszOpadania)
			{
				zegar -= std::chrono::milliseconds(1100);
				czyWcisnietyKlawiszOpadania = false;
			}
		}
		else
		{
			//Sprawdzanie czy pod klockiem jest inny klocek.
			for(int8_t indeksDwa = 0; indeksDwa < 4; indeksDwa ++)
			{
				if(indeksDwa + pozycjaLewoPrawo.first < 10 && (obecnaPozycjaKlockaWPionie + 1 < 12 
				&& plansza[obecnaPozycjaKlockaWPionie + 1][indeksDwa + pozycjaLewoPrawo.first] != 0
				&& klocek[3][indeksDwa] != 0) || (plansza[obecnaPozycjaKlockaWPionie][indeksDwa + pozycjaLewoPrawo.first] != 0
				&& klocek[2][indeksDwa] != 0))
				{
					if(obecnaPozycjaKlockaWPionie == 0)
					{
						std::cout << "Koniec rozgrywki" << '\n';
						std::cout << "Ilosc punktow: " << * punkty << '\n';
						* czyTrwaGra = false;
						return;
					}
					czyNowyKlocek = true;
					if(czyWcisnietyKlawiszOpadania)
					{
						zegar -= std::chrono::milliseconds(1100);
						czyWcisnietyKlawiszOpadania = false;
					}
					indeksDwa = 4;
				}
			}
		}
		//Sprawdzenie czy w jakiejœ linijce s¹ wszystkie klocki w szeregu 
		//(je¿eli tak - wzrastaj¹ punkty a klocki nad t¹ linijk¹ przemieszczaj¹ siê w dó³ o jeden).
		for(int8_t indeksJeden = 0; indeksJeden < 12; indeksJeden ++)
		{
			bool czyWszystkieKlockiWSzeregu = true;
			for(int8_t indeksDwa = 0; indeksDwa < 10; indeksDwa ++)
			{
				if(plansza[indeksJeden][indeksDwa] == 0)
				{
					czyWszystkieKlockiWSzeregu = false;
					indeksDwa = 10;
				}
			}
			if(czyWszystkieKlockiWSzeregu && czyPowstalKlocek)
			{
				* punkty += 10;
				//Opadanie klocków na dó³.
				for(int8_t indeksJedenKopia = indeksJeden; indeksJedenKopia > 0; indeksJedenKopia --)
				{
					for(int8_t indeksDwa = 0; indeksDwa < 10; indeksDwa ++)
					{
						plansza[indeksJedenKopia][indeksDwa] = plansza[indeksJedenKopia - 1][indeksDwa];
					}
				}
			}
		}
		if(czyPowstalKlocek)
		{
			czyPowstalKlocek = false;
		}
		//Wstawienie klocka na plansze.
		indeksJedenKlocka = 3;
		for(int8_t indeksJeden = obecnaPozycjaKlockaWPionie; indeksJeden != -1
			&& indeksJeden >= obecnaPozycjaKlockaWPionie - 3; indeksJeden --)
		{
			int8_t indeksDwa = pozycjaLewoPrawo.first;
			for(int8_t indeksDwaKlocka = 0; indeksDwaKlocka < 4; indeksDwaKlocka ++)
			{
				if(klocek[indeksJedenKlocka][indeksDwaKlocka])
				{
					plansza[indeksJeden][indeksDwa] = klocek[indeksJedenKlocka][indeksDwaKlocka];
				}
				indeksDwa ++;
			}
			indeksJedenKlocka --;
		}
		//Wypisanie planszy.
		for(int8_t indeksJeden = 0; indeksJeden < 12 && czyWcisnietyKlawiszOpadania == false; indeksJeden ++)
		{
			std::cout << std::string(10, ' ');
			std::cout << '|';
			for(int8_t indeksDwa = 0; indeksDwa < 10; indeksDwa ++)
			{
				if(plansza[indeksJeden][indeksDwa])
				{
					SetConsoleTextAttribute(kolor, * kolorKlocka);
					std::cout << * znakKlocka;
				}
				else
				{
					std::cout << ' ';
				}
				SetConsoleTextAttribute(kolor, 7);
			}
			std::cout << '|';
			if(indeksJeden == 0)
			{
				std::cout << " Twoje punkty: " << * punkty;
			}
			std::cout << '\n';
		}
		std::cout << std::string(11, ' ');
		std::cout << std::string(10, '-');
		std::cout << '\n';
		//Pêtla która oczekuje sekundê na klawisz.
		while(zegar > std::chrono::system_clock::now() && * czyTrwaGra && czyWcisnietyKlawiszOpadania == false)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			bool czyPrzesunacKlocek = false;
			bool czyWPrawo = false;
			switch(* znak)
			{
				//Ruch klocka w lewo.
				case 'a':
				case 'A':
				{
					//Sprawdzenie czy mo¿na przesun¹æ klocek w lewo.
					if(obecnaPozycjaKlockaWPionie < 10 && pozycjaLewoPrawo.first != 0 
					&& plansza[obecnaPozycjaKlockaWPionie + 1][pozycjaLewoPrawo.first - 1] == 0)
					{
						indeksJedenKlocka = 3;
						czyPrzesunacKlocek = true;
						for(int8_t indeksJeden = obecnaPozycjaKlockaWPionie + 1; indeksJeden != -1
						&& indeksJeden >= obecnaPozycjaKlockaWPionie - 4; indeksJeden --)
						{
							if(plansza[indeksJeden][pozycjaLewoPrawo.first - 1] == 1 && klocek[indeksJedenKlocka][0] == 1)
							{
								czyPrzesunacKlocek = false;
								indeksJeden = -1;
							}
							indeksJedenKlocka --;
						}
						if(czyPrzesunacKlocek)
						{
							pozycjaLewoPrawo.first --;
							pozycjaLewoPrawo.second --;
						}
					}
					* znak = 0;
					break;
				}
				//Ruch klocka w prawo.
				case 'd':
				case 'D':
				{
					//Sprawdzenie czy mo¿na przesun¹æ klocek w prawo.
					if(obecnaPozycjaKlockaWPionie < 10 && pozycjaLewoPrawo.second != 9 
					&& plansza[obecnaPozycjaKlockaWPionie + 1][pozycjaLewoPrawo.second + 1] == 0)
					{
						czyPrzesunacKlocek = true;
						indeksJedenKlocka = 3;
						for(int8_t indeksJeden = obecnaPozycjaKlockaWPionie + 1; indeksJeden != -1
						&& indeksJeden >= obecnaPozycjaKlockaWPionie - 4; indeksJeden --)
						{
							if(plansza[indeksJeden][pozycjaLewoPrawo.second + 1] == 1 && klocek[indeksJedenKlocka][3] == 1)
							{
								czyPrzesunacKlocek = false;
								indeksJeden = -1;
							}
							indeksJedenKlocka --;
						}
						if(czyPrzesunacKlocek)
						{
							czyWPrawo = true;
							pozycjaLewoPrawo.first ++;
							pozycjaLewoPrawo.second ++;
						}
					}
					* znak = 0;
					break;
				}
				//Opadniêcie natychmiastowe klocka.
				case 's':
				case 'S':
				{
					* znak = 0;
					czyWcisnietyKlawiszOpadania = true;
					zegar -= std::chrono::seconds(1);
					break;
				}
			}
			if(czyPrzesunacKlocek)
			{
				//Czyszczenie poprzedniej pozycji klocka.
				indeksJedenKlocka = 3;
				for(int8_t indeksJeden = obecnaPozycjaKlockaWPionie; indeksJeden != -1
				&& indeksJeden >= obecnaPozycjaKlockaWPionie - 3; indeksJeden --)
				{
					int8_t indeksDwa = pozycjaLewoPrawo.first;
					if(czyWPrawo)
					{
						indeksDwa --;
					}
					else
					{
						indeksDwa ++;
					}
					for(int8_t indeksDwaKlocka = 0; indeksDwaKlocka < 4; indeksDwaKlocka ++)
					{
						if(klocek[indeksJedenKlocka][indeksDwaKlocka])
						{
							plansza[indeksJeden][indeksDwa] = 0;
						}
						indeksDwa ++;
					}
					indeksJedenKlocka --;
				}
				czyPrzesunacKlocek = false;
				czyWPrawo = false;
			}
		}
		obecnaPozycjaKlockaWPionie ++;
	}
}