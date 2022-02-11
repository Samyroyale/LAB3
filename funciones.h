#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;
void codificar2( unsigned long long tam, int n, string binarios);

void decodificar2( unsigned long long tam, int n, string codif );

string Leer(string nombre, int tipo);

void Escribir(string nombre, string texto, int tipo);

string buscarDatos(string __cedula__);

void restarSaldo(string __cedula__, int cantidad);

void mostrarSaldo();

void retirarSaldo();

string Cabin(string texto);

string Binca(string texto);

string Codificar1(string textobinario, int semilla);

string Decodificar1(string codificado, int semilla);

string Invertir(string binario, int num);

long Contar1y0(string binario, char numero);

string reverse(string cadena);

void menuCajero(void);

void menuOperador(void);

bool verificarContrasena();

void nuevoUsuario();

bool isNum(string cadena);


#endif // FUNCIONES_H

