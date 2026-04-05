#include <iostream>
using namespace std;

// Clase padre
class Vehiculo {
protected:
    string tipo;
    int velocidad;
    int id;

public:
    Vehiculo(string t = "", int v = 0, int i = 0) {
        tipo = t;
        velocidad = v;
        id = i;
    }

    virtual void mover() {
        cout << "Vehiculo moviendose a " << velocidad << " km/h" << endl;
    }

    virtual void detener() {
        cout << "Vehiculo detenido" << endl;
    }

    // 🔥 Método clave para polimorfismo
    virtual void accionEspecial() {
        cout << "Este vehiculo no tiene accion especial" << endl;
    }

    // Setters
    void setId(int i) { id = i; }
    void setVelocidad(int v) { velocidad = v; }

    // Getters
    int getId() { return id; }
    int getVelocidad() { return velocidad; }

    virtual ~Vehiculo() {}
};

// Clase hija Robot
class Robot : public Vehiculo {
public:
    Robot(int i, int v) : Vehiculo("robot", v, i) {}

    void mover() override {
        cout << "Robot moviendose automaticamente a " << velocidad << " km/h" << endl;
    }

    void accionEspecial() override {
        cout << "Robot ejecutando movimiento especial" << endl;
    }
};

// Clase hija Carro Refrigerado
class CarroRefrigerado : public Vehiculo {
public:
    CarroRefrigerado(int i, int v) : Vehiculo("carro_refrigerado", v, i) {}

    void mover() override {
        cout << "Carro refrigerado moviendose a " << velocidad << " km/h" << endl;
    }

    void accionEspecial() override {
        cout << "Calculando temperatura del carro refrigerado..." << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese la cantidad de vehiculos: ";
    cin >> n;

    Vehiculo** vehiculos = new Vehiculo*[n];

    for (int i = 0; i < n; i++) {
        int id, velocidad;
        string tipo;

        cout << "\nVehiculo #" << i + 1 << endl;
        cout << "ID: ";
        cin >> id;

        cout << "Velocidad: ";
        cin >> velocidad;

        cout << "Tipo (robot / carro): ";
        cin >> tipo;

        if (tipo == "robot") {
            vehiculos[i] = new Robot(id, velocidad);
        } else if (tipo == "carro") {
            vehiculos[i] = new CarroRefrigerado(id, velocidad);
        } else {
            vehiculos[i] = new Vehiculo(tipo, velocidad, id);
        }
    }

    // 🔥 Uso del polimorfismo limpio
    cout << "\n--- Acciones ---\n";
    for (int i = 0; i < n; i++) {
        vehiculos[i]->mover();
        vehiculos[i]->accionEspecial(); // 👈 aquí está la magia
        vehiculos[i]->detener();
        cout << endl;
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        delete vehiculos[i];
    }
    delete[] vehiculos;

    return 0;
}