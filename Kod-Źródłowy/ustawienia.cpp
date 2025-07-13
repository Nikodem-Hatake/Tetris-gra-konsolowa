#include "header.hpp"

void Ustawienia(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka)
{
	bool czyWyjsc = false;
	char wybor = 0;
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	while(czyWyjsc == false)
	{
		std::cout << "1. Zmien znak klocka. Obecny znak: " << znakKlocka << '\n'; \
		std::cout << "2. Zmien kolor klocka. Obecny kolor: ";
		SetConsoleTextAttribute(kolor, kolorKlocka);
		switch(kolorKlocka)
		{
			case 1:
			{
				std::cout << "Niebieski" << '\n';
				break;
			}
			case 2:
			{
				std::cout << "Limonkowy" << '\n';
				break;
			}
			case 3:
			{
				std::cout << "Cyjanowy" << '\n';
				break;
			}
			case 4:
			{
				std::cout << "Czerwony" << '\n';
				break;
			}
			case 5:
			{
				std::cout << "Fioletowy" << '\n';
				break;
			}
			case 6:
			{
				std::cout << "Zolty" << '\n';
				break;
			}
			case 7:
			{
				std::cout << "Bialy" << '\n';
				break;
			}
			case 8:
			{
				std::cout << "Szary" << '\n';
				break;
			}
		}
		SetConsoleTextAttribute(kolor, 7);
		std::cout << "3. Wyjdz" << '\n';
		std::cout << "Dokonaj wyboru: ";
		wybor = _getch();
		system("cls");
		switch(wybor)
		{
			//Zmiana znaku u¿ywanego do wypisania klocka.
			case '1':
			{
				char tempZnakKlocka = znakKlocka;
				std::cout << "Wprowadz nowy znak dla klocka: ";
				tempZnakKlocka = _getch();
				std::cout << '\n';
				while(tempZnakKlocka <= 32 || tempZnakKlocka >= 128)
				{
					std::cout << "Wprowadz inny znak: ";
					tempZnakKlocka = _getch();
					std::cout << '\n';
				}
				znakKlocka = tempZnakKlocka;
				break;
			}
			//Zmiana koloru klocka.
			case '2' :
			{
				char tempKolorKlocka = 0;
				std::cout << "Dostepne kolory: " << '\n';
				SetConsoleTextAttribute(kolor, 1);
				std::cout << "1. Niebieski" << '\n';
				SetConsoleTextAttribute(kolor, 2);
				std::cout << "2. Limonkowy" << '\n';
				SetConsoleTextAttribute(kolor, 3);
				std::cout << "3. Cyjanowy" << '\n';
				SetConsoleTextAttribute(kolor, 4);
				std::cout << "4. Czerwony" << '\n';
				SetConsoleTextAttribute(kolor, 5);
				std::cout << "5. Fioletowy" << '\n';
				SetConsoleTextAttribute(kolor, 6);
				std::cout << "6. Zolty" << '\n';
				SetConsoleTextAttribute(kolor, 7);
				std::cout << "7. Bialy" << '\n';
				SetConsoleTextAttribute(kolor, 8);
				std::cout << "8. Szary" << '\n';
				SetConsoleTextAttribute(kolor, 7);
				std::cout << "Dokonaj wyboru: ";
				tempKolorKlocka = _getch();
				while(tempKolorKlocka < 49 || tempKolorKlocka > 56)
				{
					std::cout << '\n' << "Dokonaj poprawnego wyboru: ";
					tempKolorKlocka = _getch();
				}
				tempKolorKlocka -= 48;
				kolorKlocka = tempKolorKlocka;
				break;
			}
			case '3':
			{
				system("cls");
				czyWyjsc = true;
				break;
			}
			default:
			{
				std::cout << "Dokonano zlego wyboru" << '\n';
				break;
			}
		}
		wybor = 0;
	}
}