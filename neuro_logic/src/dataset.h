#pragma once

#ifdef DATA_FOR_NETWORK
bool points_data[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

// Threshold (14 функций)
bool NO_etalons[4] = { 0, 0, 0, 0 }; // логическая функция лжи
bool AND_etalons[4] = { 0, 0, 0, 1 }; // логическое и (конъюнкция)
bool NIMP_etalons[4] = { 0, 0, 1, 0 }; // обратная негация 
bool FIRST_etalons[4] = { 0, 0, 1, 1 }; // логическая функция первого аргумента
bool NRIMP_etalons[4] = { 0, 1, 0, 0 }; // обратная негация 
bool SECOND_etalons[4] = { 0, 1, 0, 1 }; // логическая функция второго аргумента
bool OR_etalons[4] = { 0, 1, 1, 1 }; // логическое или (дизъюнкция)
bool PIRS_etalons[4] = { 1, 0, 0, 0 }; // стрелка Пирса
bool NFIRST_etalons[4] = { 1, 1, 0, 0 }; // логическая функция первого аргумента
bool NSECOND_etalons[4] = { 1, 0, 1, 0 }; // логическая функция второго аргумента
bool RIMP_etalons[4] = { 1, 0, 1, 1 }; // обратная импликация
bool IMP_etalons[4] = { 1, 1, 0, 1 }; // импликация
bool SHEFFER_etalons[4] = { 1, 1, 1, 0 }; // стрелка Шеффера
bool YES_etalons[4] = { 1, 1, 1, 1 }; // логическая функция правды

// Signal (2 функции)
bool XOR_etalons[4] = { 0, 1, 1, 0 }; // исключающее или
bool EQ_etalons[4] = { 1, 0, 0, 1 }; // логическая эквиваленция

#endif