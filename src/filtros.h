#ifndef FILTROS_H
#define FILTROS_H

#include "csv.h"

// Filtra por letra inicial de município ou bioma
int filtrarPorLetra(const LinhaCSV* linha, int campo, char letra);

// Filtra por ano 
int filtrarPorAno(const LinhaCSV* linha, int ano);

#endif
