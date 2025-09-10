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

# Funciones del Proyecto
## Elementos generales: 
todas las funciones aquí descritas usan apuntadores o referencias de parámetros a menos de que se usen las maquinas de configuracion, que son variables comunes por ser solo 5 si bien las medidas y lecturas internas si son variables(vease estructuras)
## 1. findPatientNameById Function

Devuelve el nombre de un paciente de una lista según su número de
identificación.

### Parámetros

-   **patientId**: ID del paciente que se buscará.
-   **patientList**: puntero a la lista de pacientes (Patient\[\]).
-   **totalPatients**: número total de pacientes en la lista.

### Funcionamiento

-   Itera todos los pacientes mediante un bucle `for`.
-   Compara el `id_number` de cada paciente con el `patientId` obtenido
    mediante `strcmp`.
-   Si se encuentra una coincidencia, devuelve el nombre del paciente.

### Uso en el proyecto

Se usa para asignar datos de mediciones o de anomalías a un paciente
real, para simplificar la creación de reportes legibles.

------------------------------------------------------------------------

## 2. findMachineConfig

### Propósito

Obtener los valores de configuración mínimo y máximo de una máquina
(sensor) en una sala.

### Parámetros

-   **sensorId**: id del sensor/máquina que se busca.
-   **sala**: referencia a la estructura `Room` que gestiona la
    configuración de máquinas.
-   **minVal** y **maxVal**: referencias donde se almacenan los valores
    encontrados.

### Funcionamiento

-   Recorre el arreglo `machines4configinfo` (hasta 5 máquinas).
-   Si encuentra la máquina con `id` igual a `sensorId`, asigna a
    `minVal` y `maxVal` los valores de límites configurados.
-   Si no encuentra coincidencia, les asigna valores `0.0` por defecto
    (indica que no hay esa máquina).

### Utilidad en el proyecto

Permite una visualización rápida del rango de trabajo de un sensor para
verificar si una lectura está dentro de la norma o es una anomalía.

------------------------------------------------------------------------

## 3. compareAnomalies

### Objetivo

Función de orden utilizada para clasificar los registros de anomalías
primero por paciente, y luego por fecha.

### Parámetros

-   **a** y **b**: punteros genéricos (`void*`) que se convertirán en
    punteros `AnomalyRecord*`.
-   Esto es necesario porque la función está pensada para usarse con
    `qsort` o algoritmos de ordenamiento que requieren comparadores
    genéricos.

### Funcionamiento

-   Convierte los punteros a registros de anomalías (`AnomalyRecord`).

## AnomalyReport  

### Objetivo

Producir un reporte en archivo de texto de todas las lecturas anómalas
que aparezcan en los sensores de una sala, atribuyéndolas a cada
paciente y ordenándolas de forma clara.

Es la función que recopila e informa la información relacionada: acepta
los datos brutos (lecturas), procesa los datos, almacena sólo los casos
fuera de rango y crea un documento final para el usuario.

------------------------------------------------------------------------

### Parámetros

-   **sala (const Room&)** → referencia a la sala donde están los
    sensores y sus valores.\
-   \*\*listaPacientes (const Patient\*)\*\* → lista con pacientes dados
    de alta, para unir IDs con nombres.\
-   **totalPacientes (int)** → número de pacientes en la lista.

------------------------------------------------------------------------

## Flujo interno de ejecución

### 1. Inicialización

-   Se reserva un puntero dinámico para guardar las entradas de
    anomalías.\
-   `anomaliasCount` cuenta cuántas anomalías se han detectado.

### 2. Búsqueda por máquinas, mediciones y lecturas

Se recorren tres bucles anidados:\
1. Máquinas en la sala.\
2. Mediciones realizadas por cada máquina.\
3. Lecturas concretas de cada medición.

Esto asegura que se revisan **todos los datos disponibles**.

### 3. Detección de anomalías

-   Ignora el sensor tipo `'E'` (posiblemente especial o excluido).\
-   Usa `detectAnomaly` para saber si la lectura está fuera de los
    valores normales.

### 4. Creación de un registro de anomalía

-   Crea un nuevo registro con el dato del paciente, fecha y tipo de
    sensor.\
-   Obtiene el nombre legible utilizando `findPatientNameById`.\
-   Si es de tipo presión arterial (`'P'`), se toma un valor auxiliar
    (`auxreading4pdia`).\
-   Para otros sensores, se usa la lectura principal.\
-   Verifica el rango normal admitido para ese sensor en la sala.

### 5. Inserción dinámica en el array

-   Se crea un nuevo array dinámico con espacio adicional.\
-   Se copian las anomalías previas.\
-   Se agrega la nueva.\
-   Se elimina el array antiguo.

⚠️ **Problema**: este algoritmo es costoso porque reasigna memoria en
cada anomalía. En C++ moderno sería mejor usar `std::vector`.

### 6. Ordenamiento de anomalías

-   Utiliza `qsort` para ordenar anomalías:
    -   Primero por paciente.\
    -   Luego por fecha.

### 7. Creación del archivo de reporte

-   Abre (o crea) el archivo `anomalias.txt`.\
-   Si falla, imprime error y libera memoria.\
-   Escribe la cabecera del archivo.

### 8. Escritura de anomalías

-   Agrupa las anomalías por paciente.\
-   Cuando aparece cambio de ID, imprime una nueva sección.\
-   Muestra la anomalía con **fecha, sensor, valor y rango normal**.

### 9. Finalización

-   Cierra el archivo.\
-   Libera memoria.\
-   Imprime en consola que todo ha ido correctamente.
-   
## AddStruct
-Funciones no usadas planteadas para añadir elementos a arrays ya existentes de cada tipo de struct y devolver el nuevo arreglo con el elemento extra. 
### Parámetros:
Apuntador a la maquina original
referencia a la cantidad de elementos de cada arreglo

## printMachine
-Funcion de tipo void cuyo proposito es imprimir en la consola el id, el minimo y el maximo de las máquinas, para rectificar que la lectura de cada uno está bien

### Parámetros: 
Referencia a la máquina de la que se quieran imprimir dichos datos

## CompareTwoDates
-Función que recibe dos medidas y compara sus fechas, de manera que devuelva un entero positivo si la primera es mayor, un 0 si son iguales y un entero negativo si la primera es menor(compara ambos cstrings por memcmp)

### Parámetros:
referencia a cada una de las medidas

## arrangeMeasurementsByDate

-Bucle que va organizando las medidas dadas de mas reciente a mas antiguas para imprimirlas ordenadas en el reporte
### Funcionamiento:
se plantea, con la misma logica de un algoritmo de ordenamiento por selección, un elemento auxiliar para copiar en un lado lo que está en el otro, y poco a poco va identificando la fecha mayor entre los elementos restantes y poniendola adelante

### Parámetros:
referencia al arreglo dinámico de medidas que se va a ordenar
tamaño de este arreglo


## DetectAnomaly
-Función de tipo bool que compara una lectura dada con los valores maximo y minimo de la configuracion en base al sensor de la misma

### Parametros:
Referencia a la lectura a comparar
referencia de la Sala en la que se encuentran los datos de configuración
## Generatereport:
-Funcion de tipo void que crea el reporte del paciente para ir ingresando sus datos. 
### Funcionamiento:
inicia por generar el archivo de texto clásico, y usando el numero de paciente, imprime de primeras el nombre y su id.Ordena las medidas por orden cronológico con arrangemeasurementsbydate y
sucesivamente, recorre todas las lecturas de todas las medidas de todas las máquinas para identificar aquellas en las que el numero del paciente cuyo numero se dio en un principio coincida con el numero de paciente(patient id) presente en la medida, y si es así, imprime los datos de la medida.
### Parámetros:
referencia del paciente del que se genera el reporte
apuntador a las maquinas de configuracion, sala de uci 

## readConfigFile
funcion de tipo void que lee el archivo de configuración y guarda sus elementos en maquinas diseñadas para esto
### Funcionamiento:
Abre el archivo, crea un bucle en el que por cada maquina de configuracion se usan referencias para caracterizar el espacio de memoria donde se guardan los valores minimos, maximos y de id de cada maquina/tipo de sensor(para la maquin no son intercambiables pero para la medida si) y guarda la informacion leida del archivo en estos espacios
### Parámetros:
Referencia a la sala donde guardar las maquinas

## cargarPacientesdesdeCSV:
funcion de tipo apuntador a patient que lee el archivo tipo csv dividiendo cada elemento que se pueda obtener en un caso identificable y guardando la medida en el espacio correspondiente en base a dicho caso.(sin parámetros)

## generarreportebinarioerrorECG
Función que genera un archivo binario con los datos de las mediciones anomalas de tipo ecg para un paciente dado.
### Funcionamiento:
Crea una serie de bucles en los que recorre todas las lecturas de todas las medidas de todas las máquinas dos veces. La primera vez, un contador registra cada vez que se encuentre una lectura de tipo ecg asignada al paciente dado, la segunda vez, identifica cuáles de estas lecturas son anómalas para reportar su valor y su fecha.
### Parámetros:
Referencia al paciente del que se generará la medición, referencia a la sala en la que se tienen los datos.














