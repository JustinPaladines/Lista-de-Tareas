#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Tarea {
    int numero_tarea;
    string descripcion;
    bool estado; // false = Pendiente, true = Completada
};

void eliminarTarea(vector<Tarea>& tareas, int numero) {
    for (auto it = tareas.begin(); it != tareas.end(); ++it) {
        if (it->numero_tarea == numero) {
            tareas.erase(it);
            cout << "Tarea eliminada correctamente.\n";
            return;
        }
    }
    cout << "No se encontró una tarea con ese número.\n";
}
