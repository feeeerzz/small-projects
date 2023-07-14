#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;


struct Parqueo {
    string numPlaca;
    chrono::time_point<chrono::system_clock> tiempoEntrada;
    int estado;
};

int parqueosDisponibles = 30;
int parqueosEspeciales = 5;
int parqueosMotocicletas = 15;

void limpiarTerminal() {
    system("cls");
}

// Opcion 1
double calcularCostoParqueo(double tiempoUso) {
    // Valor QUEMADO del costo del parqueo
    double costoHora = 1.5;
    return tiempoUso * costoHora;
}

void emitirTiquete(const string& numeroPlaca, const Parqueo& parqueo, vector<Parqueo>& registros) {
    while (true) {
        limpiarTerminal();
        cout << "Tiquete de Parqueo" << endl;
        cout << "Numero de placa: " << numeroPlaca << endl;
        auto tiempoEntrada = chrono::system_clock::to_time_t(parqueo.tiempoEntrada);
        cout << "Hora de entrada: " << put_time(localtime(&tiempoEntrada), "%d/%m/%Y, %H:%M:%S") << endl;

        cout << "Elija una opcion:" << endl;
        cout << "1. Emitir tiquete de salida" << endl;
        cout << "2. Volver al menu principal" << endl;

        int opcion;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            auto tiempoSalida = chrono::system_clock::now();

            // Tiempo de uso
            double duracion = chrono::duration<double>(tiempoSalida - parqueo.tiempoEntrada).count();
            double tiempoUso = duracion / 3600.0;

            double parqueoCosto = calcularCostoParqueo(tiempoUso);

            limpiarTerminal();
            cout << "Tiquete de Parqueo" << endl;
            cout << "Numero de placa: " << numeroPlaca << endl;
            cout << "Hora de entrada: " << put_time(localtime(&tiempoEntrada), "%d/%m/%Y, %H:%M:%S") << endl;
            auto tiempoSalidaLocal = chrono::system_clock::to_time_t(tiempoSalida);
            cout << "Hora de salida: " << put_time(localtime(&tiempoSalidaLocal), "%d/%m/%Y, %H:%M:%S") << endl;
            cout << "Tiempo dentro del estacionamiento: " << fixed << setprecision(2) << tiempoUso << " horas" << endl;
            cout << "Costo del parqueo: $" << parqueoCosto << endl;

            //Eliminacion de los registros al emitir el ticket de salida
            for (auto it = registros.begin(); it != registros.end(); ++it) {
                if (it->numPlaca == numeroPlaca) {
                    registros.erase(it);
                    break;
                }
            }
            break;
        } else if (opcion == 2) {
            break;
        } else {
            cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
            cin.ignore();
            cin.get();
        }
    }
}

// Opcion 2
void DisponibilidadParqueos(int parqueosDisponibles, int parqueosEspeciales, int parqueosMotocicletas) {
    limpiarTerminal();
    cout << "Parqueos disponibles: " << parqueosDisponibles << endl;
    cout << "Parqueos especiales disponibles: " << parqueosEspeciales << endl;
    cout << "Parqueos de motocicletas disponibles: " << parqueosMotocicletas << endl;

    cout << endl << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

// Opcion 3
void buscarAutoEnParqueo(const string& numeroPlaca, const vector<Parqueo>& registros) {
    bool encontrado = false;

    for (const Parqueo& parqueo : registros) {
        if (parqueo.numPlaca == numeroPlaca) {
            encontrado = true;
            cout << "El vehículo con número de placa " << numeroPlaca << " está en el parqueo." << endl;
            cout << endl << "Presione cualquier tecla para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
    }

    if (!encontrado) {
        cout << "El vehículo con número de placa " << numeroPlaca << " no se encuentra en el parqueo." << endl;
        cout << endl << "Presione cualquier tecla para continuar...";
        cin.ignore();
        cin.get();
    }
}


// Hora en el menu principal
void mostrarHoraEntrada(const chrono::time_point<chrono::system_clock>& tiempoEntrada) {
    auto tiempoLocal = chrono::system_clock::to_time_t(tiempoEntrada);
    cout << "Hora de entrada: " << put_time(localtime(&tiempoLocal), "%d/%m/%Y, %H:%M:%S") << endl;
}

// Menú principal
int main() {
    vector<Parqueo> registros;

    while (true) {
        limpiarTerminal();
        cout << "Bienvenido a Plaza Multicinema" << endl;
        cout << "1. Ingresar vehiculo" << endl;
        cout << "2. Emitir y mostrar tiquete de parqueo" << endl;
        cout << "3. Verificar disponibilidad de parqueo" << endl;
        cout << "4. Buscar auto en el parqueo" << endl;
        cout << "5. Salir" << endl;

        int opcion;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        limpiarTerminal();

        if (opcion == 1) {
            string numeroPlaca;
            cout << "Ingrese el numero de placa: ";
            cin >> numeroPlaca;

            int longitudPlaca = numeroPlaca.length();
            if (longitudPlaca == 8) {
                cout << "Vehiculo registrado: Auto" << endl;

                
                Parqueo parqueo;
                parqueo.numPlaca = numeroPlaca;
                parqueo.tiempoEntrada = chrono::system_clock::now();
                registros.push_back(parqueo);

                cout << "Vehiculo ingresado exitosamente." << endl;
                mostrarHoraEntrada(parqueo.tiempoEntrada);
            } else if (longitudPlaca == 6) {
                cout << "Vehiculo registrado: Moto" << endl;


                Parqueo parqueo;
                parqueo.numPlaca = numeroPlaca;
                parqueo.tiempoEntrada = chrono::system_clock::now();
                registros.push_back(parqueo);

                cout << "Vehiculo ingresado exitosamente." << endl;
                mostrarHoraEntrada(parqueo.tiempoEntrada);
            } else if (longitudPlaca == 4) {
                cout << "Vehiculo registrado: Especial" << endl;


                Parqueo parqueo;
                parqueo.numPlaca = numeroPlaca;
                parqueo.tiempoEntrada = chrono::system_clock::now();
                registros.push_back(parqueo);

                cout << "Vehiculo ingresado exitosamente." << endl;
                mostrarHoraEntrada(parqueo.tiempoEntrada);
            } else {
                cout << "Numero de placa invalido." << endl;
                continue;
            }
        } else if (opcion == 2) {
            if (registros.empty()) {
                cout << "No hay vehiculos en el parqueo." << endl;
            } else {
                string numeroPlaca;
                cout << "Ingrese el numero de placa: ";
                cin >> numeroPlaca;

                bool encontrado = false;
                for (const Parqueo& parqueo : registros) {
                    if (parqueo.numPlaca == numeroPlaca) {
                        emitirTiquete(numeroPlaca, parqueo, registros);
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) { 
                    cout << "No se encontró el vehículo con número de placa " << numeroPlaca << "." << endl;
                }
            }
        } else if (opcion == 3) {
            DisponibilidadParqueos(parqueosDisponibles, parqueosEspeciales, parqueosMotocicletas);
        } else if (opcion == 4) {
            if (registros.empty()) {
                cout << "No hay vehiculos en el parqueo." << endl;
cout << "Presione cualquier tecla para continuar..." << endl;
cin.ignore();
cin.get();
                 } else {
                string numeroPlaca;
                cout << "Ingrese el numero de placa: ";
                cin >> numeroPlaca;

                buscarAutoEnParqueo(numeroPlaca, registros);
            }       
        } else if (opcion == 5) {
            break;
        } else {
            cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
        }
    }

    return 0;
}
