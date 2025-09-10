#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "libs4project/StructsUCI.hh"
#include <sstream>
#include "libs4project/Functionsold.hh"
using namespace std;

int main(void) {

    




    cout << "Bienvenido al sistema de procesamiento de datos de máquinas médicas" << endl;
    cout << "Seleccione una opción del menú:" << endl;
    cout << "1. Cargar archivo de configuración y datos de pacientes" << endl;
    cout << "2. Leer archivo " << endl;
    cout << "3. Generar reporte de anomalías" << endl;
    cout << "4. Calcular estadísticas" << endl;
    cout << "5. Exportar datos procesados" << endl;
    cout << "0. Salir" << endl;

    int option = 0;
    Room& salaDestino=*(new Room);
    Patient* patient=nullptr;

    do {
        cout << "Ingrese una opción: ";
        cin >> option;

        switch (option)
        {
            case 1: {
                cout << "Cargando archivo de configuración y datos de pacientes ..." << endl;
                readConfigFile(salaDestino);
                for(int i=0;i<5;i++){
                    printMachine(salaDestino.machines4configinfo[i]);
                }
                

                patient=cargarPacientesDesdeCSV();
                 
                cout<<"El primer paciente se llama: "<<patient[0].name<<endl;  
                cout<<"El segundo paciente se llama: "<<patient[1].name<<endl;             
                break;
            }
            case 2: {
                cout << "Leeyendo archivo de mediciones" << endl;
                cargarDatosBSF1(salaDestino);
                
                cout<<"El numero de lecturas de la primera maquina es: "<<static_cast<int>(salaDestino.machines[0].m[0].readingsamount)<<endl;
                cout<<"La primera lectura de la primera maquina es: "<<salaDestino.machines[0].m[0].reading[0].reading<<endl;
                cout<<"La primera lectura de la primera medicion de la segunda maquina es: "<<salaDestino.machines[1].m[0].reading[0].reading<<endl;
                

                
                break;
            }
            case 3: {
                cout << "Generando reporte de anomalías..." << endl;
                cout<<"inserte el numero del paciente a generar reporte(inicia desde 1) :";

                int numpaciente;
                cin>>numpaciente;
                GenerateReport(patient[numpaciente-1], salaDestino.machines, salaDestino);
                break;
            }
            case 4:
            {
                cout << "Calculando estadísticas..." << endl;
                generateAnomalyReport(salaDestino, patient,sizeof(patient));
                break;
            }
            case 5:
            {
                cout << "Exportando datos procesados..." << endl;
                cout<<"Inserte el numero del paciente a generar reporte binario de errores ECG(inicia desde 1) :";
                int numpaciente2;
                cin>>numpaciente2;
                generarreportebinarioerrorECG(patient[numpaciente2-1], salaDestino);
                break;
            }
            case 0:
            {
                cout << "Saliendo..." << endl;
                
                delete[] patient;
                delete[] salaDestino.machines->m->reading;
                delete[] salaDestino.machines->m;
                delete[] salaDestino.machines;
                delete[] salaDestino.machines4configinfo;
                delete& salaDestino;
                salaDestino.machines = nullptr;
                patient = nullptr;
                break;
            }
            default:
            {
                cout << "Opción inválida" << endl;
                break;
            }
        }

    } while (option != 0);

    return 0;
}


