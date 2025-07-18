#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include<windows.h>
using namespace std;


struct tarea{
	
	int numero_tarea;
	string tarea;
	bool estado;
};

vector<tarea>tareas = {}; 

void agregar_tarea(vector<tarea>& tareas){
	
	tarea nueva_tarea;
	nueva_tarea.numero_tarea = tareas.size() + 1;
	cout<<"Ingrese su nueva tarea aqui: "<<endl;
	cin.ignore();
	getline(cin, nueva_tarea.tarea);
	nueva_tarea.estado = true;
	
	tareas.push_back(nueva_tarea);
	cout<<"Su tarea ha sido agregada. ¡No olvides realizarla!"<<endl;
	
}
