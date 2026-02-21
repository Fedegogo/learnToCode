#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

 int days = 7;
 string daysOfWeek[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

int askNumberCars(){
    int numberCars;
    do {
        cout << "Type number car from 0 to 25: ";
        cin >> numberCars;

        if (numberCars < 0 || numberCars > 25) {
            cout << "Valor invalido. Intente nuevamente.\n";
        }

    } while (numberCars < 0 || numberCars > 25);

    cout << "Car number: " << numberCars << endl;
    return numberCars;
}
void registerId(string *ids, int numberCars){
    for (int i=0; i<numberCars; i++){
        cout<<"Type id to car #"<< i + 1 <<": "<<endl;
        cin >> *(ids + i);
    }
}

void addInitalDistance(int *km, int numberCars){
    for (int i=0; i<numberCars; i++){
        cout<<"Type initial kilometers by car #"<< i + 1 << ": " <<endl;
        cin >> *(km + i);
    }
}

void AddFuelConsuption(vector<vector<int>> &table, int numberCars){
    for (int i=0; i<numberCars; i++){
        cout << "\nCar #:" << i + 1 << endl;
        for (int j=0; j<days; j++){
            cout << "Add value on " << daysOfWeek[j] << ": " << endl;
            cin >> table[i][j];
        }
    }
}

void printData(string *ids, int *km, vector<vector<int>> &table, int numberCars){
    cout << "\n====================== VEHICLE DATA ======================\n\n";
    // Encabezado
    cout << left << setw(10) << "ID"
         << setw(18) << "Initial Km";
    for(int i = 0; i < days; i++)
        cout << setw(12) << daysOfWeek[i];

    cout << endl;
    cout << string(10 + 18 + (days * 12), '-') << endl;
    // Datos
    for(int i = 0; i < numberCars; i++) {
        cout << left << setw(10) << *(ids + i)
             << setw(18) << *(km + i);
        for(int j = 0; j < days; j++)
            cout << setw(12) << table[i][j];
        cout << endl;
    }
    cout << endl;
}

int getTotalFuel(int* row){
    int add = 0;

    for (int i=0; i<days; i++){
        add += *(row + i); 
    }
    return add;
}

int addKilometers(int *km, int numberCars){
    int add = 0;
    for (int i=0; i<numberCars; i++){
        add += *(km + i);
    }
    return add;
}

float averageFuel(vector<vector<int>> &table, int numberCars){
    int add = 0;
    float average = 0;

    for (int i=0; i<numberCars; i++){
        for (int j=0; j<days; j++){
            add += table[i][j];
        }
    }
    average = add / (numberCars * days);
    return average;
}
 pair<int, int>getHigherConsumption(vector<vector<int>> &table, int numberCars){
    int addConsumption[numberCars] = {0};
    int add = 0;
    int max = 0;
    int car = 0;
    for (int i=0; i<numberCars; i++){
        for (int j=0; j<days; j++){
            add += table[i][j];
        }
        addConsumption[i] = add;
        add = 0;
    }

    for (int i=0; i<numberCars; i++){
        if (addConsumption[i] > max){
            max = addConsumption[i];
            car = i;
        }
    }
    
    return {max, car};
}
int main() 
{
    int option = 0;
    int numberCars = 0;

    // Get number cars
    numberCars = askNumberCars();

    // Create dynamic arrays
    string* ids = new string[numberCars];
    int* km = new int[numberCars];
    vector<vector<int>> tableFuel(numberCars, vector<int>(days));

    // Register data
    registerId(ids, numberCars);
    addInitalDistance(km, numberCars);
    AddFuelConsuption(tableFuel, numberCars);

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Mostrar informacion tabular\n";
        cout << "2. Consumo total por vehiculo\n";
        cout << "3. Sumatoria de kilometros\n";
        cout << "4. Consumo promedio semanal\n";
        cout << "5. Vehiculo con mayor consumo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;

        switch(option) {
        case 1: printData(ids, km, tableFuel, numberCars); break;
        case 2: {
            int selectedCar;
            int totalFuel = 0;
            cout << "Input the number of car: ";
            cin >> selectedCar;
            totalFuel = getTotalFuel(tableFuel[selectedCar -1].data());
            cout << "The total fuel to the car "<<*(ids + (selectedCar - 1 ))<<" is: "<< totalFuel<<endl;
            break;
        }
        case 3: {
            int distance = 0;
            distance = addKilometers(km, numberCars);
            cout << "The total kilometers are: " << distance << endl;
            break;
        }
        case 4: {
            float average = 0;
            average = averageFuel(tableFuel, numberCars);
            cout << "The average weekly fuel consumption is: " << average << endl;
            break;
        } 
        case 5: {
            auto [max, car] = getHigherConsumption(tableFuel, numberCars);
            cout << "The car " << ids[car]<< " has the max consumption with: " << max << endl;
        }
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida\n";
        }
    } while(option != 0);

    // Free memory
    delete[] ids, km;
    km = nullptr;
    ids = nullptr; // Good practice
}