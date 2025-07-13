#include "header.hpp"

int main()
{
	std::atomic_bool czyTrwaGra(true);
	std::atomic_char znak(0);
	std::atomic_uint64_t punkty(0);
	std::fstream plik;
	std::atomic_char znakKlocka('1');
	std::atomic_short kolorKlocka(3);
	uint64_t rekord = 0;
	bool plansza[12][10];
	char wybor = 0;
	Odczyt(znakKlocka, kolorKlocka, rekord);
	//Pêtla g³ówna gry.
	while(wybor != '3')
	{
		Menu();
		wybor = _getch();
		system("cls");
		switch(wybor)
		{
			case '1':
			{
				czyTrwaGra = true;
				punkty = 0;
				//Czyszczenie planszy przed uruchomieniem gry.
				for(uint8_t indeksJeden = 0; indeksJeden < 12; indeksJeden ++)
				{
					for(uint8_t indeksDwa = 0; indeksDwa < 10; indeksDwa ++)
					{
						plansza[indeksJeden][indeksDwa] = 0;
					}
				}
				std::future <void> gra = std::async(std::launch::async, Tetris, plansza, & znak, & czyTrwaGra, & punkty, & znakKlocka, & kolorKlocka);
				while(czyTrwaGra)
				{
					znak = _getch();	//Pobieranie znaku z klawiatury w trakcie gry.
				}
				if(punkty > rekord)
				{
					std::cout << "Nowy rekord!!!" << '\n';
					rekord = punkty;
					Zapisz(znakKlocka, kolorKlocka, rekord);
				}
				break;
			}
			case '2':
			{
				system("cls");
				Ustawienia(znakKlocka, kolorKlocka);
				Zapisz(znakKlocka, kolorKlocka, rekord);
				break;
			}
			case '3':
			{
				Zapisz(znakKlocka, kolorKlocka, rekord);
				std::cout << "Mozesz bezpiecznie zamknac gre ^^.";
				break;
			}
			default:
			{
				std::cout << "Dokonaj poprawnego wyboru" << '\n';
				break;
			}
		}
		if(wybor != '3')
		{
			wybor = 0;
		}
	}
	_getch();	//Dopiero wciœniêcie klawisza zamknie program.
}