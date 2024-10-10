#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    string carrera;
    string departamento;
    string municipio;
    string telefonoPersonal;
    string telefonoCasa;
    string telefonoEmergencia;
    string correoElectronico;  
    int diaNacimiento, mesNacimiento, anioNacimiento;
    int edad;
    int anioIngreso; 
};

// Lista de departamentos
const string departamentos[] = {
    "Guatemala", "Sacatep�quez", "Chimaltenango", "Escuintla", "Santa Rosa",
    "Solol�", "Totonicap�n", "Quetzaltenango", "Suchitep�quez", "Retalhuleu",
    "San Marcos", "Huehuetenango", "Quich�", "Baja Verapaz", "Alta Verapaz",
    "Pet�n", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
};

// Lista de municipios por departamento
const string municipios[22][5] = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"}, //GUTEMALA
    {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"}, //SACATEPEQUEZ
    {"Chimaltenango", "San Mart�n de los Canes", "El Tejar", "San Jos� Poaquil", "San Juan Comalapa"}, //CHIMALTENANGO
    {"Escuintla", "Santa Luc�a Cotzumalguapa", "La democracia", "San Jos�", "Siquinal�"}, //ESCUINTLA
    {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"}, //SANTA ROSA
    {"Solal�", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palop�"}, //SOLOLA
    {"Totonicap�n", "San Crist�bal Totonicap�n", "San Francisco el Alto", "San Andr�s Xecul", "Momostenango"}, //TOTONICAPAN
    {"Quetzaltenango", "Salcaj�", "San Mart�n Sacatep�quez", "Sibilia", "Zunil"}, //QUETZALTENANGO
    {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitep�quez", "Santo Domingo Suchitep�quez"}, //SUCHITEPEQUEZ
    {"Retalhuleu", "San Sebasti�n", "San Mart�n Zapotitl�n", "Tecoanapa", "Champerico"}, //RETALHULEU
    {"San Marcos ","San Pedro Sacatep�quez", "Malacat�n", "San Antonio Sacatep�quez", "Sibinal"}, //SAN MARCOS
	{"Huehuetenango", "Aguacat�n", "Chiantla", "Colotenango", "Concepci�n Huista"}, //HUEHUTENENGO
	{"Santa Cruz del Quiche", "San Antonio Ilotenango", "San Bartolom� Jocotenango", "San Pedro Jocopilas", "Patzit�"}, //QUICHE
	{"Salam�", "Granados", "Rabinal", "San Jer�nimo", "El Chol"},  //BAJA VERAPAZ
	{"Cob�n", "San Pedro Carch�", "San Crist�bal Verapaz", "Tactic", "Tucur�"}, // ALTA VERAPAZ
	{"Flores", "Melchor de Mencos", "Popt�n", "San Benito", "San Francisco"}, //PETEN
	{"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"}, //IZABAL
	{"Gual�n", "R�o Hondo", "La Uni�n", "San Jorge", "Estanzuela"}, //ZACAPA
	{"Chiquimula", "Jocot�n", "Esquipulas", "Camot�n", "Ipala"}, //CHIQUIMULA
	{"Monjas", "San Pedro Pinula", "San Carlos Alzatate", "San Luis Jilotepeque", "Jalapa"}, //JALAPA
    {"Jutiapa", "Jalpatagua", "El Progreso", "Asunci�n Mita", "Santa Catarina Mita"}, //JUTIAPA
    {"Guastatoya", "Moraz�n", "Sanarate", "Sansare", "San Agust�n Acasaguastl�n"} //EL PROGRESO
};

// Funci�n para generar el c�digo autom�ticamente
int generarCodigo() {
    static int codigo = 1000; 
    return codigo++;
}

// Funci�n para calcular la edad actual
int calcularEdad(int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    time_t t = time(0);
    tm* ahora = localtime(&t);

    int anioActual = 1900 + ahora->tm_year;
    int mesActual = 1 + ahora->tm_mon;
    int diaActual = ahora->tm_mday;

    // Calcular la edad
    int edad = anioActual - anioNacimiento;

    // Ajustar si el cumplea�os a�n no ha ocurrido este a�o
    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--;
    }
    
    return edad;
}

// Funci�n para mostrar el men� de carreras y permitir al usuario escoger una
string escogerCarrera() {
    int opcion;
    cout << "\nSeleccione una carrera:\n";
    cout << "1. Ingenier�a en sistemas\n";
    cout << "2. Administraci�n de empresas\n";
    cout << "3. Derecho\n";
    cout << "Ingrese el n�mero de la carrera: ";
    cin >> opcion;
    
    switch(opcion) {
        case 1:
            return "Ingenier�a en sistemas";
        case 2:
            return "Administraci�n de empresas";
        case 3:
            return "Derecho";
        default:
            cout << "Opci�n no v�lida. Se asignar� Ingenier�a en sistemas por defecto.\n";
            return "Ingenier�a";
    }
}

// Funci�n para que el usuario elija su departamento y municipio
void escogerDireccion(string& departamento, string& municipio) {
    int opcionDepto;
    cout << "\nSeleccione un departamento:\n";
    for (int i = 0; i < 22; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "Ingrese el n�mero del departamento: ";
    cin >> opcionDepto;

    if (opcionDepto < 1 || opcionDepto > 22) {
        cout << "Opci�n no v�lida. Se asignar� Guatemala por defecto.\n";
        departamento = "Guatemala";
    } else {
        departamento = departamentos[opcionDepto - 1];
    }

    // Mostrar municipios del departamento seleccionado
    int opcionMuni;
    cout << "\nSeleccione un municipio en " << departamento << ":\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << municipios[opcionDepto - 1][i] << endl;
    }
    cout << "Ingrese el n�mero del municipio: ";
    cin >> opcionMuni;

    if (opcionMuni < 1 || opcionMuni > 5) {
        cout << "Opci�n no v�lida. Se asignar� " << municipios[opcionDepto - 1][0] << " por defecto.\n";
        municipio = municipios[opcionDepto - 1][0];
    } else {
        municipio = municipios[opcionDepto - 1][opcionMuni - 1];
    }
}

// Funci�n para registrar un estudiante
void registrarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevoEstudiante; 
    
    nuevoEstudiante.id = generarCodigo(); 
    
    // Limpiar el b�fer de entrada antes de usar getline
    cin.ignore();
    
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nuevoEstudiante.nombre);
    
    // Limpiar el b�fer de entrada antes de usar getline
    cout << "Ingrese el apellido del estudiante: ";
    getline(cin, nuevoEstudiante.apellido);
    
    // El usuario escoge la carrera
    nuevoEstudiante.carrera = escogerCarrera();
    
    // El usuario escoge la direcci�n (departamento y municipio)
    escogerDireccion(nuevoEstudiante.departamento, nuevoEstudiante.municipio);
    
    // Ingresar tel�fonos
    cout << "Ingrese el n�mero de tel�fono personal: ";
    cin >> nuevoEstudiante.telefonoPersonal;
    cout << "Ingrese el n�mero de tel�fono de casa: ";
    cin >> nuevoEstudiante.telefonoCasa;
    cout << "Ingrese el n�mero de tel�fono de emergencia: ";
    cin >> nuevoEstudiante.telefonoEmergencia;

    // Ingresar correo electr�nico
    cout << "Ingrese el correo electr�nico del estudiante: ";
    cin >> nuevoEstudiante.correoElectronico;  
    
    // Ingresar fecha de nacimiento
    cout << "Ingrese el d�a de nacimiento (DD): ";
    cin >> nuevoEstudiante.diaNacimiento;
    cout << "Ingrese el mes de nacimiento (MM): ";
    cin >> nuevoEstudiante.mesNacimiento;
    cout << "Ingrese el a�o de nacimiento (YYYY): ";
    cin >> nuevoEstudiante.anioNacimiento;
    
    // Calcular la edad
    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.diaNacimiento, nuevoEstudiante.mesNacimiento, nuevoEstudiante.anioNacimiento);
    
    // Ingresar el a�o de ingreso a la universidad
    cout << "Ingrese el a�o de ingreso a la universidad: ";
    cin >> nuevoEstudiante.anioIngreso;

    // Agregar el estudiante al vector
    estudiantes.push_back(nuevoEstudiante);
    
    cout << "Estudiante registrado con ID: " << nuevoEstudiante.id << ", Edad: " << nuevoEstudiante.edad 
         << " a�os, Carrera: " << nuevoEstudiante.carrera 
         << ", Departamento: " << nuevoEstudiante.departamento 
         << ", Municipio: " << nuevoEstudiante.municipio
         << ", Tel�fono Personal: " << nuevoEstudiante.telefonoPersonal
         << ", Tel�fono de Casa: " << nuevoEstudiante.telefonoCasa
         << ", Tel�fono de Emergencia: " << nuevoEstudiante.telefonoEmergencia
         << ", Correo Electr�nico: " << nuevoEstudiante.correoElectronico
         << ", A�o de Ingreso: " << nuevoEstudiante.anioIngreso << endl;
}

// Funci�n principal
int main() {
    vector<Estudiante> estudiantes;
    int opcion;

    do {
        cout << "\n1. Registrar estudiante\n";
        cout << "2. Salir\n";
        cout << "Ingrese una opci�n: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                registrarEstudiante(estudiantes);
                break;
            case 2:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opci�n no v�lida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 2);

    return 0;
}
