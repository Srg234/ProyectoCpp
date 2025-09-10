# FUNCIONAMIENTO

AQUI SE ENUNCIAN LAS DIFIERENTES PARTES DEL CODIGO CON UNA BREVE EXPLICACION DE CADA UNA
=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=
## STRUCTS
Muchas de las structs tienen debajo una sentencia del tipo: nombrestruct():elemento1(valorelemento),elemento2(valorelemento),...

En esta sentencia se inician valores determinados cal crear un elemento de este tipo para que no hayan bits basura en los arreglos y variables y entonces se pueda trabajar mejor con ellos.
### Machinereading
lectura de la maquina. En la misma se guardan:
double reading-->la lectura en sí que da la máquina

uint32_t auxreading4psis/4pdia-->la lectura si es que la maquina es de tipo P. Puesto que se guardan 2 lecturas y además de tamaño distinto al reading, nos pareció mejor crear una variable dedicada y adaptar las funciones a este elemento

uint8_t machine_id-->id de la máquina en la que se encuenntra la lectura

char Sensortype-->Tipo de sensor con el que se mide la lectura.

char patient_name[20]-->Cstring con el nombre (SOLO EL NOMBRE) del paciente.


### AnomalyRecord
estructura en la que se guardan los elementos que definen a la lectura anómala

char patientId[20]-->cstring que guarda el id de paciente

char patientName[50]-->cstring que guarda el nombre del paciente

char date[24]-->ccstring con la fecha

char SensorType-->caracter que guarda el tipo de sensor de cada máquina

double Value--> valor de la medida

double minRange-->minimo de la medida para ese sensor

double maxRange-->maximo de la medida para ese sensor


### measurements
struct para las medidas de la màquina
char patient_id[11]-->cstring con el id de paciente

char date[24]-->cstring con la informacion de la fecha de la medida 

uint32_t readingsamount-->cantidad de lecturas en la medicion

Machinereading* reading--> apuntador hacia el primer elemento del array dinàmico de lecturas


### Machine
struct para la màquina

uint8_t id-->id de la màquina

int measurements_number-->cantidad de medidas

measurements*m;-->apuntador al primer elemento del array dinamico para medidas de la maquina

float min;-->minimo de este tipo de maquina(por tipo de sensor)

float max;--maximo de este tipo de maquina(por tipo de sensor)


### Room

struct para la sala

uint8_t id--> id de la sala

uint8_t machine_number-->numero de maquinas en la sala

Machine* machines--> apuntador hacia el primer elemento del array dinamico de Maquinas

Machine machine4configinfo[5]-->maquinas para guardar la informacion de minimos y maximos de cada tipo de sensor


### Patient

struct con la informacion del paciente

char patient_number[4]-->cstring con el numero del paciente

char name[20]--> cstring con el nombre del paciente

char last_name[20]--> cstring con el apellido del paciente

char id_type[2]--> cstring con el tipo de id del paciente

char id_number[20]--> cstring con el numero de id del paciente

char  date[12]--> cstring con la fecha de entrada/cumpleanos del paciente

char phone_number[15]-->cstring con el numero de telefono del paciente

char email[50]--> cstring con el email del paciente

char bloodtype[3]-->cstring con el tipo de sangre del paciente

char eps[100]-->cstring con la eps del paciente

char ensurance[100]-->cstring con la aseguradora del paciente

char room_id[20]--> id de la sala en la que reside el paciente( en este caso para todos el kismo por lo que es una unica sala)







