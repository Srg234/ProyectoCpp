# ProyectoCpp
Aquí se encuentran todos los elementos del proyecto a entregar. El codigo soporta el archivo small pero hay que rectificar con respecto al real.

============================================================================================
### Funcionamiento General

En su base, el codigo usa el mismo tipo de menu que se propone originalmente. La opción 1 carga los datos de pacientes y configuración, la opcion 2 carga los datos de las distintas lecturas, la opcion 3 le permite al usuario ingresar el numero de un paciente para generar un reporte con sus medidas, la opción 4 hace un reporte general de todaslas anomalías y la 5 genera un archivo binario en el  que se guardan las mediciones de tipo ECG que sean anómalas. La salida borra los distintos elementos de tipo new creados, pero salir inmediatamente generará un error debido a que no se entiende que borrar. 
### Notas de funcionamiento
El id de paciente del reporte va de 1 al máximo de pacientes, y ciertas funciones de tipo add no están implementadas debido a que su utilidad final no fue la que se esperaba, pero se dejan para varias preguntas de lógica. Por default, el código usa los siguientes archivos: 
patient_reading_simulation_small.bsf
configuración.txt
pacientes.cvs
Para cambiar esto ir a la primera linea de cada una de las funciones que leen dicho archivo y cambiar la cadena de caracteres filename por la dirección del archivo que se desee usar.

