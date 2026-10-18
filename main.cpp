#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura para almacenar los datos de cada Pokémon según el CSV
struct Pokemon {
    int pokedex;
    string nombre;
    string tipo1;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defensa;
    int ataqueEsp;
    int defensaEsp;
    int velocidad;
    int generacion;
    string legendario;
};

// Función para cargar los datos desde el archivo CSV
vector<Pokemon> cargarPokemones() {
    vector<Pokemon> lista;
    ifstream archivo("pokemon_150_registros.csv");
    string linea;

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo pokemon_150_registros.csv" << endl;
        return lista;
    }

    // Omitir la primera línea (cabecera)
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        Pokemon p;

        getline(ss, dato, ','); 
        if (dato.empty()) continue;
        p.pokedex = stoi(dato);

        getline(ss, p.nombre, ',');
        getline(ss, p.tipo1, ',');
        getline(ss, p.tipo2, ','); // Puede venir vacía

        getline(ss, dato, ','); p.total = stoi(dato);
        getline(ss, dato, ','); p.hp = stoi(dato);
        getline(ss, dato, ','); p.ataque = stoi(dato);
        getline(ss, dato, ','); p.defensa = stoi(dato);
        getline(ss, dato, ','); p.ataqueEsp = stoi(dato);
        getline(ss, dato, ','); p.defensaEsp = stoi(dato);
        getline(ss, dato, ','); p.velocidad = stoi(dato);
        getline(ss, dato, ','); p.generacion = stoi(dato);
        getline(ss, dato, ','); p.legendario = dato;

        lista.push_back(p);
    }

    archivo.close();
    return lista;
}

// Función auxiliar para mostrar la información detallada de un Pokémon
void mostrarPokemon(const Pokemon& p) {
    cout << "\n----------------------------------------" << endl;
    cout << " Nro Pokedex: " << p.pokedex << endl;
    cout << " Nombre:      " << p.nombre << endl;
    cout << " Tipo 1:      " << p.tipo1 << endl;
    cout << " Tipo 2:      " << (p.tipo2.empty() ? "Ninguno" : p.tipo2) << endl;
    cout << " Total Stats: " << p.total << endl;
    cout << " HP:          " << p.hp << endl;
    cout << " Ataque:      " << p.ataque << endl;
    cout << " Defensa:     " << p.defensa << endl;
    cout << " Atq. Esp.:   " << p.ataqueEsp << endl;
    cout << " Def. Esp.:   " << p.defensaEsp << endl;
    cout << " Velocidad:   " << p.velocidad << endl;
    cout << " Legendario:  " << p.legendario << endl;
    cout << "----------------------------------------" << endl;
}

// 1. Ver info de pokemon por número de pokedex
void buscarPorNumero(const vector<Pokemon>& lista) {
    int num;
    cout << "\nIngrese el numero de Pokedex del Pokemon: ";
    cin >> num;

    bool encontrado = false;
    for (const auto& p : lista) {
        if (p.pokedex == num) {
            mostrarPokemon(p);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se encontro ningun Pokemon con el numero " << num << "." << endl;
    }
}

// 2 y 4. Buscar / Ver info de pokemon por nombre
void buscarPorNombre(const vector<Pokemon>& lista) {
    string nombreBuscado;
    cout << "\nIngrese el nombre del Pokemon: ";
    cin >> nombreBuscado;

    bool encontrado = false;
    for (const auto& p : lista) {
        // Comparamos ignorando un poco las mayúsculas/minúsculas básicas o de forma exacta
        if (p.nombre == nombreBuscado) {
            mostrarPokemon(p);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se encontro ningun Pokemon con el nombre '" << nombreBuscado << "'." << endl;
    }
}

// 3. Ver pokemons de un tipo seleccionado por el usuario
void buscarPorTipo(const vector<Pokemon>& lista) {
    string tipo;
    cout << "\nIngrese el tipo a buscar (ej. Grass, Fire, Water, Normal...): ";
    cin >> tipo;

    cout << "\n--- Pokemones de tipo " << tipo << " ---" << endl;
    int contador = 0;
    for (const auto& p : lista) {
        if (p.tipo1 == tipo || p.tipo2 == tipo) {
            cout << "- " << p.nombre << " (Pokedex #" << p.pokedex << ")" << endl;
            contador++;
        }
    }
    if (contador == 0) {
        cout << "No se encontraron Pokemones con ese tipo." << endl;
    } else {
        cout << "Total encontrados: " << contador << endl;
    }
}

// 5. Ver pokemon con estadísticas más fuertes (top 3) y top débiles
void mostrarTopEstadisticas(vector<Pokemon> lista) {
    if (lista.empty()) return;

    // Ordenar de mayor a menor según el campo 'Total'
    sort(lista.begin(), lista.end(), [](const Pokemon& a, const Pokemon& b) {
        return a.total > b.total;
    });

    cout << "\n=== TOP 3 POKEMON MAS FUERTES ===" << endl;
    for (int i = 0; i < 3 && i < lista.size(); i++) {
        cout << i + 1 << ". " << lista[i].nombre << " (Total Stats: " << lista[i].total << ")" << endl;
    }

    cout << "\n=== TOP 3 POKEMON MAS DEBILES ===" << endl;
    // Los más débiles están al final del vector ordenado de mayor a menor
    int n = lista.size();
    for (int i = 0; i < 3 && i < n; i++) {
        cout << i + 1 << ". " << lista[n - 1 - i].nombre << " (Total Stats: " << lista[n - 1 - i].total << ")" << endl;
    }
}

int main() {
    vector<Pokemon> pokemones = cargarPokemones();

    if (pokemones.empty()) {
        cout << "Verifique que el archivo 'pokemon_150_registros.csv' este en la misma carpeta." << endl;
        return 1;
    }

    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "        GESTION DE POKEMON - URU        " << endl;
        cout << "========================================" << endl;
        cout << "1. Ver info de Pokemon por numero de Pokedex" << endl;
        cout << "2. Buscar Pokemon por nombre" << endl;
        cout << "3. Ver Pokemones por tipo" << endl;
        cout << "4. Ver info completa de Pokemon por nombre" << endl;
        cout << "5. Ver Top 3 mas fuertes y Top 3 mas debiles" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                buscarPorNumero(pokemones);
                break;
            case 2:
            case 4: // Las opciones 2 y 4 piden buscar/ver por nombre, usan la misma función detallada
                buscarPorNombre(pokemones);
                break;
            case 3:
                buscarPorTipo(pokemones);
                break;
            case 5:
                mostrarTopEstadisticas(pokemones);
                break;
            case 6:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);

    return 0;
}