#include "mpi.h"
#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/*
Estructura lista invertida
*/
struct indice_inverso
{
	string palabra;
	set<string> doc;
};

bool comparar (const indice_inverso first, const indice_inverso second)
{
	return (first.palabra < second.palabra);
}

void buscar_consulta(int cant_terminos, set<string> consultas, indice_inverso vector_index )
{
	set<string>::iterator iterador;
	for (i = 0; i < cant_terminos; i++)
	{
		for (j = 0; j < (consultas).size(); j++)
		{
			int palabra_encontrada = 0;
			for (k = 0; k != (vector_index).size(); k++)
			{
				if (palabra_encontrada.comparar(vector_index[k].palabra) == 0)
				{
					palabra_encontrada = 1;
					iterador = vector_index[k].doc.begin();
					while( iterador != vector_index[k].doc.end())
					{
						cout << *iterador << " ";
						iterador++;
					}
				}
				
			}
			
		}

	}
}
main (int argc, char **argv)
{
	map<string, vector<string> > Documentos;
	set<string> lista_consultas;
	int ID, nproc,  num_documentos, i, j, cant_consultas, cant_terminos;
	char titulo[1000];
	char termino[1000];
	char consulta[1000];
	FILE *pf;

	pf = fopen("test.txt", "r");

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);


	fscanf(pf, "%d", &num_documentos);
	cout <<"num_documentos = " << num_documentos << endl;

	for (i=0; i < num_documentos; i++)
	{
		fgetc(pf); //Lectura de enter
		fscanf(pf, "%s", titulo); //Leyendo titulo de documento
		cout << "titulo = " << titulo << endl;
		Documentos[string(titulo)] = vector<string>();
		fscanf(pf, "%d", &cant_terminos); //Leyendo cantidad de terminos
		cout << "cant_terminos = " << cant_terminos << endl;
		fgetc(pf); //Lectura de enter
		(Documentos[string(titulo)]).reserve(cant_terminos); // Se reserva memoria para la cantidad de terminos

		for(j=0; j < cant_terminos; j++)
		{
			fscanf(pf, "%s", termino);
			cout << "termino = " << termino << endl;
			(Documentos[string(titulo)]).push_back(string(termino)); //Agrega termino al documento
		}
	}
	fscanf(pf, "%d", &cant_consultas);
	fgetc(pf);
	for (i=0; i < cant_consultas; i++)
	{
		fscanf(pf, "%s", consulta);
		cout << "consulta = " << consulta << endl;
		(lista_consultas[i]).push_back(string(consulta)) // Agrega consulta a una lista.
	}

fflush(stdout);
MPI_Barrier(MPI_COMM_WORLD);

pair<string, vector<string> > objeto_par;
map<string, vector<string> >:: iterator It;

if (ID==3)
{
	for(It = Documentos.begin(); It != Documentos.end(); It++)
	{
		objeto_par = *It;
		cout << endl << "Nodo[" << ID << "] :: Titulo = " << objeto_par.first << endl;
		for (i = 0; i < (objeto_par.second).size(); i++)
		{
			cout << (objeto_par.second)[i] << endl;
		}
		
	}
}
MPI_Finalize();

fclose(pf);

return 0;
}
