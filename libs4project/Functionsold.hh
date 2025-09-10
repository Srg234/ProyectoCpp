






#include <iostream>
#include <string>
#include <fstream>
#include "StructsUCI.hh"

#include <sstream>


using namespace std;

const int EXIT_ERROR_CODE = -1;
Machine* AddMachine(Machine* maquinanueva, int& contadorMaquinas) {
        Machine* nuevoArray = new Machine[contadorMaquinas+1];
        for (int i = 0; i < contadorMaquinas; i++) {
            nuevoArray[i] = maquinanueva[i];
        }
        delete[] maquinanueva; // Liberar la memoria del array antiguo
        return nuevoArray;
        

    }
    measurements* Addmeasurements(measurements* medidanueva, int& contadormedidas) {
        measurements* nuevoArray = new measurements[contadormedidas+1];
        for (int i = 0; i < contadormedidas; i++) {
            nuevoArray[i] = medidanueva[i];
        }
        delete[] medidanueva; // Liberar la memoria del array antiguo
        return nuevoArray;
        

    }
    Machinereading* Addreading(Machinereading* lecturanueva, uint32_t& contadorlecturas) {
        Machinereading* nuevoArray = new Machinereading[contadorlecturas];
        
        cout<<"contador lecturas: "<<contadorlecturas<<endl;
        for (int i = 0; i < contadorlecturas ; i++) {
            nuevoArray[i] = lecturanueva[i];
            if(nuevoArray[i].SensorType=='P'){
            cout<<"Lectura numero:"<<i<<"Lectura de presion: "<<nuevoArray[i].auxreading4pdia;}
            else{

            cout<<"lectura numero"<<i<<nuevoArray[i].reading<<endl;}
        }
        if(contadorlecturas==0){
        delete lecturanueva; 
        return nuevoArray;
        }
        else{
        delete[] lecturanueva; // Liberar la memoria del array antiguo
        return nuevoArray;}
        

    }

void printMachine(Machine& Machine){
  
    cout << "min: " << Machine.min << endl;
    cout << "max: " << Machine.max << endl;
    cout << "id: " << Machine.id << endl << endl; 
}
int CompareTwodates(const measurements& measure1, const measurements& measure2) {
    char date1[12];
    char date2[12];
    //copia los datos de la memoria de cada elemento
    memcpy(date1, measure1.date, 12);
    memcpy(date2, measure2.date, 12);

    return memcmp(date1, date2, 12);

    };
void arrangeMeasurementsByDate(measurements& measurementsArray,int sizetoget) {
    //Uso swap para ordenar las mediciones por fecha
    measurements temp;
    for (int i = 0; i < sizetoget - 1; i++) {
        measurements& currentMeasurement = *(&measurementsArray + i);
        for (int j = i + 1; j < sizetoget; j++) {
            measurements& comparedMeasurement = *(&measurementsArray + j);
            if (CompareTwodates(currentMeasurement, comparedMeasurement) > 0) 
            {
                temp = currentMeasurement;
                currentMeasurement = comparedMeasurement;
                comparedMeasurement = temp;
            }
        }}}

bool detectAnomaly(Machinereading& lectura, Room& Maquinas) {
    //Si no hay lectura, da falso
    
for (int i = 0; i < 5; i++){
    Machine* maquinasparachequeo = Maquinas.machines4configinfo + i;
    measurements* medidasparachequeo = maquinasparachequeo->m;
    Machinereading* lecturasparachequeo = medidasparachequeo->reading;
    if (lectura.SensorType== lecturasparachequeo->SensorType){
    if(lectura.SensorType=='P'){
        if (lectura.auxreading4pdia < maquinasparachequeo->min||lectura.auxreading4pdia > maquinasparachequeo->max){
        return true;
        }else if(lectura.auxreading4psis < maquinasparachequeo->min||lectura.auxreading4psis > maquinasparachequeo->max){
            return true;}
        }else if (lectura.reading < maquinasparachequeo->min||lectura.reading > maquinasparachequeo->max){
        
        return true;
    }else{ return false;}
  }
}

cout<<"Warning: It has not been found a machine with the ID"<< lectura.machine_id << "in the machine list"<<endl;
return false;}

void GenerateReport(const Patient& patient, 
                     Machine* maquinas,Room& salaDestino) {    

    ofstream reportFile("report.txt", ios::app);
    if (!reportFile.is_open()) {
        cerr << "Error: No se pudo abrir report.txt para escritura." <<endl;
        return; 
    }
     reportFile << "==============================";
    reportFile << "Reporte del Paciente: " << patient.name << " " << patient.last_name << "\n";
    reportFile << "ID del Paciente: " << patient.id_type << "\n";
    reportFile << "-------------------------------";
    reportFile << "Mediciones Registradas:"<< "\n";
    int medicionesEncontradas = 0;
    for(int w=0;w<salaDestino.machine_number;w++){
 
        Machine* lamaquinaachequear = maquinas + w;
        
    for(int l=0; l < lamaquinaachequear->measurements_number; ++l) {
    measurements& medidasachequear = maquinas->m[l];
    
    

    arrangeMeasurementsByDate(medidasachequear,lamaquinaachequear->measurements_number);

    
    for (int i = 0; i < lamaquinaachequear->measurements_number; ++i) {
            measurements& medidasordenadas = maquinas->m[i];
        for (int k = 0; k <medidasordenadas.readingsamount ; ++k) {
            Machinereading& lecturaordenada = medidasordenadas.reading[k];
            
        char idPacienteCompleto[256];
        //strcpy(idPacienteCompleto, patient.id_type);
        //strcat(idPacienteCompleto, patient.id_number);
        if (strcmp(patient.id_number, medidasordenadas.patient_id) == 0) {
             medicionesEncontradas++;
            reportFile << "  - Maquina: " << lamaquinaachequear->id
            << ", Tipo de Sensor: " << lecturaordenada.SensorType
            << ", Lectura: " << lecturaordenada.reading
            << ", Fecha: " << medidasordenadas.date;
            
         bool esAnomalia = detectAnomaly(lecturaordenada,salaDestino); 

            if (esAnomalia) {
                reportFile << "¡Anomalia Detectada!"<<endl;
            } else {
                reportFile << " (Normal)" << endl;
            }
            //reportFile << "Encontrado en la iteración: " << i << ", medición: " << k << ", lectura: " << j << endl;
        }
    }}}}
    if(medicionesEncontradas == 0) {
        reportFile << "No se encontraron mediciones para este paciente." << endl;
    }

    

    reportFile << "========================\n";

    reportFile.close();

}

//FUNCION PARA REPORTE GENERAL DE TODAS LAS ANOMALIAS DE TODOS LOS PACIENTES


// Función para buscar el nombre de un paciente a partir de su ID.
// Devuelve un puntero al nombre o "Desconocido" si no lo encuentra.
const char* findPatientNameById(const char* patientId, const Patient* patientList, int totalPatients) {
    for (int i = 0; i < totalPatients; i++) {
        if (strcmp(patientList[i].patient_number, patientId) == 0) {
            return patientList[i].name;
        }
    }
    return "Paciente Desconocido";
}

// Función para encontrar los rangos min/max de un sensor desde la configuración.
void findMachineConfig(char sensorId, const Room& sala, double& minVal, double& maxVal) {
    for (int i = 0; i < 5; i++) { // Asumiendo que hay 5 ranuras de configuración
        if (sala.machines4configinfo[i].id == sensorId) {
            minVal = sala.machines4configinfo[i].min;
            maxVal = sala.machines4configinfo[i].max;
            return;
        }
    }
    // Valores por defecto si no se encuentra la configuración
    minVal = 0.0;
    maxVal = 0.0;
}

// El comparador para qsort. Ordena en dos niveles.
int compareAnomalies(const void* a, const void* b) {
    const AnomalyRecord* recordA = (const AnomalyRecord*)a;
    const AnomalyRecord* recordB = (const AnomalyRecord*)b;

    // ordenar por ID de paciente.
    int patientCompare = strcmp(recordA->patientId, recordB->patientId);
    if (patientCompare != 0) {
        return patientCompare; // Si los pacientes son diferentes, ese es nuestro orden.
    }

    
    measurements tempA, tempB;
    strcpy(tempA.date, recordA->date);
    strcpy(tempB.date, recordB->date);
    return CompareTwodates(tempA, tempB);
}




void generateAnomalyReport(Room& sala, const Patient* listaPacientes, int totalPacientes){
    
    
    
    AnomalyRecord* anomalias = nullptr;
    int anomaliasCount = 0;

    for (int i = 0; i < sala.machine_number; i++) {
        Machine& maquinaActual = sala.machines[i];
        for (int j = 0; j < maquinaActual.measurements_number; j++) {
            measurements& medicionActual = maquinaActual.m[j];
            for (int k = 0; k < medicionActual.readingsamount; k++) {
                Machinereading& lecturaActual = medicionActual.reading[k];

                
                if (lecturaActual.SensorType != 'E' && detectAnomaly(lecturaActual, sala)) {
                    
                
                    AnomalyRecord newRecord = {};

                    
                    strcpy(newRecord.patientId, medicionActual.patient_id);
                    strcpy(newRecord.patientName, findPatientNameById(medicionActual.patient_id, listaPacientes, totalPacientes));
                    strcpy(newRecord.date, medicionActual.date);
                    newRecord.sensorType = lecturaActual.SensorType;
                    
                    if (lecturaActual.SensorType == 'P') {
                        
                        newRecord.value = lecturaActual.auxreading4pdia;
                    } else {
                        newRecord.value = lecturaActual.reading;
                    }
                    
                    findMachineConfig(lecturaActual.SensorType, sala, newRecord.minRange, newRecord.maxRange);

                    
                    AnomalyRecord* nuevoArray = new AnomalyRecord[anomaliasCount + 1];
                    for(int n = 0; n < anomaliasCount; n++) nuevoArray[n] = anomalias[n];
                    nuevoArray[anomaliasCount] = newRecord;
                    delete[] anomalias;
                    anomalias = nuevoArray;
                    anomaliasCount++;
                }
            }
        }
    }

    
    
    if (anomaliasCount > 0) {
        qsort(anomalias, anomaliasCount, sizeof(AnomalyRecord), compareAnomalies);
    }

    

    ofstream reportFile("anomalias.txt"); 
    if (!reportFile.is_open()) {
        cerr << "Error: No se pudo crear anomalias.txt" <<endl;
        delete[] anomalias;
        return;
    }

    reportFile<< "REPORTE DE LECTURAS ANOMALAS";

    if (anomaliasCount == 0) {
        reportFile << "No se encontraron anomalias en los datos procesados.";
    } else {
        char lastPatientId[20] = ""; // Para controlar cuándo imprimir un nuevo encabezado de paciente
        
        for (int i = 0; i < anomaliasCount; i++) {
            const AnomalyRecord& record = anomalias[i];

            if (strcmp(record.patientId, lastPatientId) != 0) {
                reportFile << "-----------------------------------------";
                reportFile << "Paciente: " << record.patientName << " (ID: " << record.patientId << ")";
                reportFile << "-----------------------------------------";
                strcpy(lastPatientId, record.patientId);
            }
            reportFile << "  - Fecha: " << record.date
                     << " | Sensor: " << record.sensorType
                     << " | Valor Registrado: " << record.value
                     << " | Rango Normal: (" << record.minRange << " - " << record.maxRange << ")";
        }
    }

    reportFile << "Fin del Reporte.";
    reportFile.close();

    
    
    delete[] anomalias; //Liberamos la memoria del arreglo temporal.
    cout << "Reporte 'anomalias.txt' generado exitosamente." <<endl;
}





                



               
        
    
    void readConfigFile(Room& machinesparaconfig) {
    const char* filename = "configuracion.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    string line;
    int contadorMaquinas = 0;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string tipoSensor, minStr, maxStr;

        if (getline(ss, tipoSensor, ',') && getline(ss, minStr, ',') && getline(ss, maxStr)) {
            Machine& maquina = machinesparaconfig.machines4configinfo[contadorMaquinas];

            // Crear al menos un measurement para esa máquina
            maquina.measurements_number = 1;
            maquina.m = new measurements[1];

            // Dentro del measurement, crear una lectura
            maquina.m[0].readingsamount = 1;
            maquina.m[0].reading = new Machinereading[1];

            // Llenar datos
            maquina.m[0].reading[0].SensorType = tipoSensor[0];
            maquina.id = tipoSensor[0];  

            maquina.min = stof(minStr);
            maquina.max = stof(maxStr);

            cout << "Configuración cargada para máquina " << contadorMaquinas+1 << endl;
            printMachine(maquina);

            contadorMaquinas++;
            if (contadorMaquinas >= 5) break;
        }
    }

    file.close();
}

    

    


Patient* AddPatient(Patient* pacientenuevo, int& contadorPacientes) {
        Patient* nuevoArray = new Patient[contadorPacientes];
        for (int i = 0; i < contadorPacientes - 1; i++) {
            nuevoArray[i] = pacientenuevo[i];
        }
        delete[] pacientenuevo; // Liberar la memoria del array antiguo
        return nuevoArray;
        

    }

    Patient* cargarPacientesDesdeCSV( ) {
    fstream file;
    string line;
    const char* filename ="pacientes.csv";

    file.open(filename, ios::in);
    if (file.fail()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return nullptr;
    }

    int totalPacientes = 0;
    while (getline(file, line)) {
        totalPacientes++;
    }
    file.close();

    if (totalPacientes == 0) {
        return nullptr;
    }

    Patient* arregloDePacientes = new Patient[totalPacientes];

    file.open(filename, ios::in);
    int pacienteActual = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int patientelement = 0;

        while (getline(ss, token, ';')) {
            switch (patientelement) {
                case 0:
                    strncpy(arregloDePacientes[pacienteActual].patient_number, token.c_str(), 4);
                    break;
                case 1:
                    strncpy(arregloDePacientes[pacienteActual].id_type, token.c_str(), 2);
                    break;
                case 2:
                    strncpy(arregloDePacientes[pacienteActual].id_number, token.c_str(), 20);
                    break;
                case 3:
                    strncpy(arregloDePacientes[pacienteActual].name, token.c_str(), 20);
                    break;
                case 4:
                    strncpy(arregloDePacientes[pacienteActual].last_name, token.c_str(), 20);
                    break;
                case 5:
                    strncpy(arregloDePacientes[pacienteActual].date, token.c_str(), 12);
                    break;
                case 6:
                    strncpy(arregloDePacientes[pacienteActual].phone_number, token.c_str(), 15);
                    break;
                case 7:
                    strncpy(arregloDePacientes[pacienteActual].email, token.c_str(), 50);
                    break;
                case 8:
                    strncpy(arregloDePacientes[pacienteActual].bloodtype, token.c_str(), 3);
                    break;
                case 9:
                    strncpy(arregloDePacientes[pacienteActual].eps, token.c_str(), 100);
                    break;
                case 10:
                    strncpy(arregloDePacientes[pacienteActual].ensurance, token.c_str(), 100);
                    break;
            }
            patientelement++;
        }
        pacienteActual++;
    }
    file.close();

    return arregloDePacientes;
}


        
    void generarreportebinarioerrorECG(Patient& paciente,Room& sala){
        ofstream reportFile("pacientes_ecg_anomalos.dat", ios::app|ios::binary);
    if (!reportFile.is_open()) {
        cerr << "Error: No se pudo abrir pacientes_ecg_anomalos.dat para escritura." <<endl;
        return; 
    }
    char idCompleto[22];
    strncpy(idCompleto, paciente.id_type, 22);

    reportFile.write(reinterpret_cast<const char*>(&paciente.id_number), sizeof(paciente.id_number));
    cout<<"ID del paciente en reporte binario: "<<paciente.id_number<<endl;
    int contadorEpaciente=0;
    for(int w=0;w<sala.machine_number;w++){
        Machine* maquina = sala.machines;
    for(int i=0;i<maquina->measurements_number;i++){
        for(int j=0;j<maquina->m[i].readingsamount;j++){
            if(maquina->m[i].patient_id==paciente.id_number){
                    if(maquina->m[i].reading[j].SensorType=='E'){
                        contadorEpaciente++;
                    }}}}}
    reportFile.write(reinterpret_cast<const char*>(&contadorEpaciente), sizeof(contadorEpaciente));

    for(int w=0;w<sala.machine_number;w++){
        Machine* maquina = sala.machines;
    for(int i=0;i<maquina->measurements_number;i++){
        for(int j=0;j<maquina->m[i].readingsamount;j++){
            if(maquina->m[i].patient_id==paciente.id_number){
                    if(maquina->m[i].reading[j].SensorType=='E'){

                        if(detectAnomaly(maquina->m[i].reading[j], sala)){
                            reportFile.write(reinterpret_cast<const char*>(&maquina->m[i].reading[j].reading), sizeof(maquina->m[i].reading[j].reading));
                            reportFile.write(reinterpret_cast<const char*>(&maquina->m[i].date), sizeof(maquina->m[i].date));
                        }
                    }
            }
        }
    }
    
    reportFile.close();
    }}

                

   
    void cargarDatosBSF1( Room& salaDestino) {
        char nombreArchivo[65] = "libs4project/Binarystuff/patient_readings_simulation_small 1.bsf";
        ifstream archivo(nombreArchivo, ios::in | ios::binary);
        if (!archivo.is_open()) {
            cerr << "ERROR: No se pudo abrir el archivo binario " << nombreArchivo << endl;
            return;
        }

    // : Leer SOLO los datos de la sala, no los arreglos internos 
    archivo.read(reinterpret_cast<char*>(&salaDestino.id), sizeof(salaDestino.id));
    cout<<"id sala leida: "<<salaDestino.id<<endl;
    archivo.read(reinterpret_cast<char*>(&salaDestino.machine_number), sizeof(salaDestino.machine_number));

    cout << "Lectura de cabecera de sala completada." << endl;
    cout << "ID de la Sala: " << static_cast<int>(salaDestino.id) << endl;
    cout << "Numero de Maquinas a leer: " << (int)salaDestino.machine_number << endl; 
    salaDestino.machines= new Machine[salaDestino.machine_number];
    int contadorMaquinas = 0;
    

    // Bucle para leer cada máquina 
    for (int i = 0; i < salaDestino.machine_number; ++i) {
        Machine* maquinaactual = salaDestino.machines + i;
        
        contadorMaquinas++;

        //  Lectura de la máquina actual 
        
        archivo.read(reinterpret_cast<char*>(&maquinaactual->id), sizeof(maquinaactual->id));
        archivo.read(reinterpret_cast<char*>(&maquinaactual->measurements_number), sizeof(maquinaactual->measurements_number));
        
        //archivo.read(reinterpret_cast<char*>(&maquinaActual.min), sizeof(maquinaActual.min));
        //archivo.read(reinterpret_cast<char*>(&maquinaActual.max), sizeof(maquinaActual.max));


        cout << "\n  Leyendo Maquina #" << i + 1 << "..." << endl;
        cout << "  ID de Maquina: " << static_cast<int>(maquinaactual->id) << endl;
        cout << "  Numero de Mediciones a leer: " << maquinaactual->measurements_number << endl;

        maquinaactual->m = new measurements[maquinaactual->measurements_number];

        // Bucle para leer las mediciones de esa máquina 
        for (int j = 0; j < maquinaactual->measurements_number; ++j) {
            
            measurements* medicionActual = maquinaactual->m + j;
            


            // Lectura de la medición actual 
            archivo.read(reinterpret_cast<char*>(&medicionActual->patient_id), sizeof(medicionActual->patient_id));
            archivo.read(reinterpret_cast<char*>(&medicionActual->date), sizeof(medicionActual->date));
            archivo.read(reinterpret_cast<char*>(&medicionActual->readingsamount), sizeof(medicionActual->readingsamount));

            cout << "    Leyendo Medicion #" << j + 1 << "..." << endl;
            cout << "    ID de Paciente: " << medicionActual->patient_id << endl;

            cout << "    Fecha: ";     
            for(int i=0;i<24;i++){
                cout<<medicionActual->date[i];
            }     
            cout << "    Cantidad de Lecturas a leer: " << medicionActual->readingsamount << endl;

            //  Bucle para leer las lecturas de esa medición 
            medicionActual->reading = new Machinereading[medicionActual->readingsamount];
            
            for (int k = 0; k < medicionActual->readingsamount; ++k) {
                
                Machinereading* lecturaActual = medicionActual->reading + k;
                
            
                archivo.read(reinterpret_cast<char*>(&lecturaActual->SensorType), sizeof(lecturaActual->SensorType));
                cout<<"El sensor es de tipo "<<lecturaActual->SensorType<<endl;
                if(lecturaActual->SensorType=='P'){
                    archivo.read(reinterpret_cast<char*>(&lecturaActual->auxreading4psis), sizeof(uint32_t));
                    cout<<"La lectura es de: "<<lecturaActual->auxreading4psis<<endl;
                    archivo.read(reinterpret_cast<char*>(&lecturaActual->auxreading4pdia), sizeof(uint32_t));
                    cout<<"La lectura es de: "<<lecturaActual->auxreading4pdia<<endl;
                    lecturaActual->machine_id= 'P';
                }
                else if(lecturaActual->SensorType=='E'){
                    //char trashbin[2];
                    //archivo.read(reinterpret_cast<char*>(trashbin), sizeof(trashbin));
                    //cout<<"Los bytes basura son: "<<trashbin[0]<<" y "<<trashbin[1]<<endl;
                    archivo.read(reinterpret_cast<char*>(&lecturaActual->reading), sizeof(double));
                    cout<<"La lectura es de: "<<lecturaActual->reading<<endl;
                    lecturaActual->machine_id= 'E';
                }
                else{
                    
                archivo.read(reinterpret_cast<char*>(&lecturaActual->reading), sizeof(lecturaActual->reading));
                cout<<"La lectura es de: "<<lecturaActual->reading<<endl;
                lecturaActual->machine_id= lecturaActual->SensorType;
                }
                
            if(archivo.eof()) {
                cout << "Se alcanzó el final del archivo antes de completar la lectura esperada." << endl;
                return;} 
                

                           }
                                 
                           
        }
        
        
    }
    

    archivo.close();
    cout << "\nCarga de datos desde " << nombreArchivo << " completada." << endl;
};
    

               
    


