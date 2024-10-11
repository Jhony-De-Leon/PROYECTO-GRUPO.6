#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <cstdlib>

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

const string departamentos[] = {
    "Guatemala", "Sacatep�quez", "Chimaltenango", "Escuintla", "Santa Rosa",
    "Solol�", "Totonicap�n", "Quetzaltenango", "Suchitep�quez", "Retalhuleu",
    "San Marcos", "Huehuetenango", "Quich�", "Baja Verapaz", "Alta Verapaz",
    "Pet�n", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
    
};

const string municipios[22][5] = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"},
    {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"},
    {"Chimaltenango", "San Mart�n de los Canes", "El Tejar", "San Jos� Poaquil", "San Juan Comalapa"},
    {"Escuintla", "Santa Luc�a Cotzumalguapa", "La Democracia", "San Jos�", "Siquinal�"},
    {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"},
    {"Solal�", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palop�"},
    {"Totonicap�n", "San Crist�bal Totonicap�n", "San Francisco el Alto", "San Andr�s Xecul", "Momostenango"},
    {"Quetzaltenango", "Salcaj�", "San Mart�n Sacatep�quez", "Sibilia", "Zunil"},
    {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitep�quez", "Santo Domingo Suchitep�quez"},
    {"Retalhuleu", "San Sebasti�n", "San Mart�n Zapotitl�n", "Tecoanapa", "Champerico"},
    {"San Marcos", "San Pedro Sacatep�quez", "Malacat�n", "San Antonio Sacatep�quez", "Sibinal"},
    {"Huehuetenango", "Aguacat�n", "Chiantla", "Colotenango", "Concepci�n Huista"},
    {"Santa Cruz del Quich�", "San Antonio Ilotenango", "San Bartolom� Jocotenango", "San Pedro Jocopilas", "Patzit�"},
    {"Salam�", "Granados", "Rabinal", "San Jer�nimo", "El Chol"},
    {"Cob�n", "San Pedro Carch�", "San Crist�bal Verapaz", "Tactic", "Tucur�"},
    {"Flores", "Melchor de Mencos", "Popt�n", "San Benito", "San Francisco"},
    {"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"},
    {"Gual�n", "R�o Hondo", "La Uni�n", "San Jorge", "Estanzuela"},
    {"Chiquimula", "Jocot�n", "Esquipulas", "Camot�n", "Ipala"},
    {"Monjas", "San Pedro Pinula", "San Carlos Alzatate", "San Luis Jilotepeque", "Jalapa"},
    {"Jutiapa", "Jalpatagua", "El Progreso", "Asunci�n Mita", "Santa Catarina Mita"},
    {"Guastatoya", "Moraz�n", "Sanarate", "Sansare", "San Agust�n Acasaguastl�n"}
   
};

int generarCodigo() {
    static int codigo = 1000; 
    return codigo++;
}

int calcularEdad(int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    time_t t = time(0);
    tm* ahora = localtime(&t);

    int anioActual = 1900 + ahora->tm_year;
    int mesActual = 1 + ahora->tm_mon;
    int diaActual = ahora->tm_mday;

    int edad = anioActual - anioNacimiento;

    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--;
    }
    
    return edad;
}

string escogerCarrera() {
    int opcion;
    cout << "\nSeleccione una carrera:\n";
    cout << "1. Ingenier�a en sistemas\n";
    cout << "2. Administraci�n de empresas\n";
    cout << "3. Derecho\n";
    while (true) {
    	cout << "\n------------------------------------------\n";
        cout << "Ingrese el n�mero de la carrera: ";
        if (cin >> opcion && opcion >= 1 && opcion <= 3) {
            switch(opcion) {
                case 1: return "Ingenier�a en sistemas";
                case 2: return "Administraci�n de empresas";
                case 3: return "Derecho";
            }
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void escogerDireccion(string& departamento, string& municipio) {
    int opcionDepto;
    cout << "\n------------------------------------------\n";
    cout << "\nSeleccione un departamento:\n";
    for (int i = 0; i < 22; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    while (true) {
    	cout << "\n------------------------------------------\n";
        cout << "Ingrese el n�mero del departamento: ";
        if (cin >> opcionDepto && opcionDepto >= 1 && opcionDepto <= 22) {
            departamento = departamentos[opcionDepto - 1];
            break;
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int opcionMuni;
    cout << "\n------------------------------------------\n";
    cout << "\nSeleccione un municipio en " << departamento << ":\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << municipios[opcionDepto - 1][i] << endl;
    }
    while (true) {
    	cout << "\n------------------------------------------\n";
        cout << "Ingrese el n�mero del municipio: ";
        if (cin >> opcionMuni && opcionMuni >= 1 && opcionMuni <= 5) {
            municipio = municipios[opcionDepto - 1][opcionMuni - 1];
            break;
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void mostrarEstudiantes(const vector<Estudiante>& estudiantes) {
    cout << "\n--- Lista de Estudiantes Registrados ---\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        const Estudiante& estudiante = estudiantes[i];
        cout << "ID: " << estudiante.id << endl;
        cout << "Nombre: " << estudiante.nombre << " " << estudiante.apellido << endl;
        cout << "Carrera: " << estudiante.carrera << endl;
        cout << "Departamento: " << estudiante.departamento << endl;
        cout << "Municipio: " << estudiante.municipio << endl;
        cout << "Tel�fono Personal: " << estudiante.telefonoPersonal << endl;
        cout << "Tel�fono de Casa: " << estudiante.telefonoCasa << endl;
        cout << "Tel�fono de Emergencia: " << estudiante.telefonoEmergencia << endl;
        cout << "Correo Electr�nico: " << estudiante.correoElectronico << endl;
        cout << "Fecha de Nacimiento: " << estudiante.diaNacimiento << "/" 
             << estudiante.mesNacimiento << "/" << estudiante.anioNacimiento << endl;
        cout << "Edad: " << estudiante.edad << endl;
        cout << "A�o de Ingreso: " << estudiante.anioIngreso << endl;
        cout << "------------------------------------------\n";
    }
}

void registrarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevoEstudiante; 
    nuevoEstudiante.id = generarCodigo(); 

    cin.ignore();  
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nuevoEstudiante.nombre);
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el apellido del estudiante: ";
    getline(cin, nuevoEstudiante.apellido);
    cout << "\n------------------------------------------\n";
    
    nuevoEstudiante.carrera = escogerCarrera();
    
    escogerDireccion(nuevoEstudiante.departamento, nuevoEstudiante.municipio);
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el n�mero de tel�fono personal: ";
    cin >> nuevoEstudiante.telefonoPersonal;
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el n�mero de tel�fono de casa: ";
    cin >> nuevoEstudiante.telefonoCasa;
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el n�mero de tel�fono de emergencia: ";
    cin >> nuevoEstudiante.telefonoEmergencia;
    cout << "\n------------------------------------------\n";
    cout << "Ingrese el correo electr�nico: ";
    cin >> nuevoEstudiante.correoElectronico;

    while (true) {
    	cout << "\n------------------------------------------\n";
        cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
        char separator; 
        if (cin >> nuevoEstudiante.diaNacimiento >> separator 
                  >> nuevoEstudiante.mesNacimiento >> separator 
                  >> nuevoEstudiante.anioNacimiento) {
            if (nuevoEstudiante.diaNacimiento >= 1 && nuevoEstudiante.diaNacimiento <= 31 &&
                nuevoEstudiante.mesNacimiento >= 1 && nuevoEstudiante.mesNacimiento <= 12) {
                break;
            }
        }
        cout << "Valor inv�lido. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.diaNacimiento, nuevoEstudiante.mesNacimiento, nuevoEstudiante.anioNacimiento);
    
    while (true) {
    	cout << "\n------------------------------------------\n";
        cout << "Ingrese el a�o de ingreso a la universidad: ";
        if (cin >> nuevoEstudiante.anioIngreso) break;
        else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    estudiantes.push_back(nuevoEstudiante);
    cout << "Estudiante registrado exitosamente!\n";
    mostrarEstudiantes(estudiantes);
}

string generarCodigoAleatorio() {
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string codigo;
    for (int i = 0; i < 6; ++i) { 
        codigo += caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    return codigo;
}

void asignarCursos() {
    srand(time(0)); 
    int opcion;
    const int NUM_CURSOS = 5;
    string cursosSistemas[NUM_CURSOS] = {"Algoritmos", "�lgebra Lineal", "Matem�tica Discreta", "Pre C�lculo", "Contabilidad"};
    string cursosAdministracion[NUM_CURSOS] = {"Contabilidad", "Marketing", "Recursos Humanos", "Finanzas", "Estrategia"};
    string cursosDerecho[NUM_CURSOS] = {"Derecho Civil", "Derecho Penal", "Derecho Mercantil", "Derecho Constitucional", "Derecho Internacional"};
    string seccionElegida[NUM_CURSOS];
    string codigos[NUM_CURSOS];

    string codigoEstudiante;
    cout << "Ingrese el c�digo del estudiante: ";
    cin >> codigoEstudiante;

    cout << "\n------------------------------------------\n";
    cout << "           Asignaci�n de Cursos      \n";
    cout << "\n------------------------------------------\n";

    cout << "Seleccione una carrera:\n";
    cout << "1. Ingenier�a en Sistemas\n";
    cout << "2. Administraci�n de Empresas\n";
    cout << "3. Derecho\n";
    cout << "\n------------------------------------------\n";


    while (true) {
        cout << "Opci�n: ";
        cin >> opcion;

        if (cin.fail() || opcion < 1 || opcion > 3) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Opci�n inv�lida. Int�ntelo de nuevo.\n";
        } else {
            cin.ignore(10000, '\n'); 
            break;  
        }
    }

    switch (opcion) {
        case 1:
            cout << "\nCursos de Ingenier�a en Sistemas:\n";
            for (int i = 0; i < NUM_CURSOS; i++) {
                codigos[i] = generarCodigoAleatorio(); 
                char seccion;
                while (true) {
                    cout << i + 1 << ". " << cursosSistemas[i] << endl;
                    cout << "Ingrese la secci�n a la que desea asignarse (A/B/C/D): ";
                    cin >> seccion;
                    if (seccion == 'A' || seccion == 'B' || seccion == 'C' || seccion == 'D') {
                        break;  
                    } else {
                        cout << "Car�cter inv�lido. Int�ntelo de nuevo.\n";
                    }
                }
                seccionElegida[i] = seccion;
            }
            break;

        case 2:
            cout << "\nCursos de Administraci�n de Empresas:\n";
            for (int i = 0; i < NUM_CURSOS; i++) {
                codigos[i] = generarCodigoAleatorio(); 
                char seccion;
                while (true) {
                    cout << i + 1 << ". " << cursosAdministracion[i] << endl;
                    cout << "Ingrese la secci�n a la que desea asignarse (A/B/C/D): ";
                    cin >> seccion;
                    if (seccion == 'A' || seccion == 'B' || seccion == 'C' || seccion == 'D') {
                        break;  
                    } else {
                        cout << "Car�cter inv�lido. Int�ntelo de nuevo.\n";
                    }
                }
                seccionElegida[i] = seccion;
            }
            break;

        case 3:
            cout << "\nCursos de Derecho:\n";
            for (int i = 0; i < NUM_CURSOS; i++) {
                codigos[i] = generarCodigoAleatorio(); 
                char seccion;
                while (true) {
                    cout << i + 1 << ". " << cursosDerecho[i] << endl;
                    cout << "Ingrese la secci�n a la que desea asignarse (A/B/C/D): ";
                    cin >> seccion;
                    if (seccion == 'A' || seccion == 'B' || seccion == 'C' || seccion == 'D') {
                        break;  
                    } else {
                        cout << "Car�cter inv�lido. Int�ntelo de nuevo.\n";
                    }
                }
                seccionElegida[i] = seccion;
            }
            break;
    }

    cout << "\n------------------------------------------\n";
    cout << "C�digo del estudiante: " << codigoEstudiante << endl; 
    cout << "\n------------------------------------------\n";
    cout << "                  Cursos            \n";
    cout << "\n------------------------------------------\n";
    
    if (opcion == 1) {
        for (int i = 0; i < NUM_CURSOS; i++) {
            cout << cursosSistemas[i] << " - Secci�n: " << seccionElegida[i] << endl;
            cout << "C�digo: " << codigos[i] << endl;
        }
        cout << "\n------------------------------------------\n";
        cout << "\nMonto a cancelar: Q670.00" << endl;
    } else if (opcion == 2) {
        for (int i = 0; i < NUM_CURSOS; i++) {
            cout << cursosAdministracion[i] << " - Secci�n: " << seccionElegida[i] << endl;
            cout << "C�digo: " << codigos[i] << endl; 
        }
        cout << "\n------------------------------------------\n";
        cout << "\nMonto a cancelar: Q650.00" << endl;
    } else if (opcion == 3) {
        for (int i = 0; i < NUM_CURSOS; i++) {
            cout << cursosDerecho[i] << " - Secci�n: " << seccionElegida[i] << endl;
            cout << "C�digo: " << codigos[i] << endl; 
        }
        cout << "\n------------------------------------------\n";
        cout << "\nMonto a cancelar: Q670.00" << endl;
    }
}

void menu() {
    vector<Estudiante> estudiantes;
    int opcion;

    while (true) {
    	cout << "------------------------------------------\n";
        cout << "\n--- Sistema de Registro de Estudiantes ---\n";
        cout << "1. Registrar un estudiante\n";
        cout << "2. Asignar cursos\n";
        cout << "3. Salir\n";
        cout << "------------------------------------------\n";

        if (!(cin >> opcion)) {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Repetir el ciclo
        }

        switch (opcion) {
            case 1:
                registrarEstudiante(estudiantes);
                break;
            case 2:
                asignarCursos();
                break;
            case 3:
                cout << "Saliendo del programa...\n";
                return;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo.\n";
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}
