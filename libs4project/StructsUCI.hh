#ifndef Machine_H
#define Machine_H

#include <string>
#include <sstream>
#include <cstring>
#include <cstdint>

using namespace std;

struct Machinereading {
    double reading;
    uint32_t auxreading4psis;
    uint32_t auxreading4pdia;
    uint8_t machine_id;
    char SensorType;
    char patient_name[20];



        Machinereading():reading(0.0),auxreading4psis(0),auxreading4pdia(0),machine_id(' '),SensorType(' '),patient_name("") {
        
    }};
    struct AnomalyRecord {
    char patientId[20];
    char patientName[50]; // Guardaremos el nombre para un reporte más amigable
    char date[24];
    char sensorType;
    double value;
    double minRange;
    double maxRange;
};
        struct measurements {
    char patient_id[11];
    char date[24];
    uint32_t readingsamount;
    Machinereading* reading;
    measurements():patient_id(""),date(""),readingsamount(0),reading(nullptr) {
        }
    
    /*measurements() {
        strncpy(patient_id,"",11);
                strncpy(date, "", 24);
        readingsamount = 0;
        for (int i = 0; i < 10; i++) {
            reading[i] = Machinereading();
        
    }/*/
};






struct Machine{
    uint8_t id;
    
    int measurements_number;
    measurements* m;
    float min;
    float max;

    Machine():id(' '),measurements_number(0),m(nullptr),min(0.0f),max(0.0f) {
    }
};









struct Room {
    uint8_t id;
    uint8_t machine_number;
    Machine* machines;
    Machine machines4configinfo[5];
    

    Room() {
        id = ' ';
        machine_number = 0;
        for(int i = 0; i < 5; i++) {
            machines4configinfo[i] = Machine();
        }
        machines = new Machine[machine_number];
    }
};

struct Patient {
    char patient_number[4];
    char name[20];
    char last_name[20];
    char id_type[2];
    char id_number[20];
    char  date[12];
    char phone_number[15];
    char email[50];
    char bloodtype[3];
    char eps[100];
    char ensurance[100];
    char room_id[20];

    Patient() {
        strncpy(patient_number, "", 4);
        strncpy(name, "", 20);
        strncpy(last_name, "", 20);
        strncpy(id_type, "", 2);
        strncpy(id_number, "", 20);
        strncpy(date, "", 12);
        for(int i = 0; i < 15; i++) {
            phone_number[i] = '\0';
        }
        strncpy(email, "", 50);
        strncpy(bloodtype, "", 3);
        strncpy(eps, "", 100);
        strncpy(ensurance, "", 100);
        strncpy(room_id, "", 20);

    }
};








#endif /* Machine_H */