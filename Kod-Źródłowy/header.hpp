#pragma once
#ifndef header_hpp
#define header_hpp

#include <atomic>
#include <chrono>
#include <conio.h>
#include <future>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <Windows.h>

void Menu();
void Odczyt(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka, uint64_t & rekord);
void Tetris(bool plansza[][10], std::atomic_char * znak, std::atomic_bool * czyTrwaGra,
std::atomic_uint64_t * punkty, std::atomic_char * znakKlocka, std::atomic_short * kolorKlocka);
void Ustawienia(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka);
void Zapisz(std::atomic_char & znakKlocka, std::atomic_short & kolorKlocka, uint64_t & rekord);

#endif