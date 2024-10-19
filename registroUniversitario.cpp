#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <windows.h> 

using namespace std;

const string MORADO = "\033[35m";    
const string VERDE = "\033[32m";     
const string AZUL = "\033[34m";      
const string BLANCO = "\033[37m";    
const string ROJO = "\033[31m";
const string GRIS_NORMAL = "\033[90m";
const string RESET = "\033[0m"; 
const string BLANCO_INTENSO = "\033[1;37m";

struct Curso {
    string nombre;
    string codigo;
    char seccion;
    float notaFinal; 
};

struct Estudiante {
    string codigoPersonal;
    string nombreCompleto;
    string carrera;
    string departamento;
    string municipio;
    string telefonoPersonal;
    string telefonoCasa;
    string correoElectronico;
    int edad;
    int anioIngreso;
    int semestre;
    vector<Curso> cursos; 
};

vector<Estudiante> estudiantes;

string generarCodigoPersonal() {
    int codigo = rand() % 9000 + 1000;
    ostringstream ss;
    ss << codigo;
    return ss.str();
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

bool validarTelefono(const string& telefono) {
    if (telefono.length() != 8) return false;
    for (size_t i = 0; i < telefono.length(); ++i) {
        if (!isdigit(telefono[i])) return false;
    }
    return true;
}

bool validarCodigoEstudiante(const string& codigo) {
    if (codigo.length() != 4) return false;
    for (size_t i = 0; i < codigo.length(); ++i) {
        if (!isdigit(codigo[i])) return false;
    }
    return true;
}

int seleccionarOpcion(const string& mensaje, int maxOpcion) {
    int opcion;
    while (true) {
        cout << mensaje;
        cin >> opcion;
        if (opcion >= 1 && opcion <= maxOpcion) {
            return opcion;
        } else {
            cout << "Valor invalido, intente de nuevo.\n";
        }
    }
}

void mostrarIconoGiratorio() {
    const char* iconos = "|/-\\";
    for (int i = 0; i < 20; ++i) {
        cout << "\r" << iconos[i % 4] << " Cargando... ";
        cout.flush();
        Sleep(100); 
    }
    cout << "\r"; 
    cout << "                \r"; 
}

void mostrarEstudiante(const Estudiante& estudiante) {           
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << MORADO;
    cout << "-----------------------------------------------------------\n";
    cout << "\n             --- Estudiante Registrado ---\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Codigo Personal: " << estudiante.codigoPersonal << "\n";
    cout << "\n";
    cout << "Nombre Completo: " << estudiante.nombreCompleto << "\n"; 
    cout << "\n";
    cout << "Carrera: " << estudiante.carrera << "\n";
    cout << "\n";
    cout << "Edad: " << estudiante.edad << "\n";
    cout << "\n";
    cout << "Departamento: " << estudiante.departamento << "\n";
    cout << "\n";
    cout << "Municipio: " << estudiante.municipio << "\n";
    cout << "\n";
    cout << "Telefono Personal: " << estudiante.telefonoPersonal << "\n";
    cout << "\n";
    cout << "Telefono de Casa: " << estudiante.telefonoCasa << "\n";
    cout << "\n";
    cout << "Correo Electronico: " << estudiante.correoElectronico << "\n";
    cout << "\n";
    cout << "Año de Ingreso: " << estudiante.anioIngreso << "\n";
    cout << "\n";
    cout << "Semestre: " << estudiante.semestre << "\n";
    cout << "-----------------------------------------------------------\n";
    
}

void mostrarCursosAsignados(const Estudiante& estudiante) {          
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << AZUL;
    cout << " \n                --- Cursos Asignados ---\n";
    cout << "-----------------------------------------------------------\n";
    for (size_t k = 0; k < estudiante.cursos.size(); ++k) {
        cout << "Curso: " << estudiante.cursos[k].nombre << "\n";
        cout << "Codigo del Curso: " << estudiante.cursos[k].codigo << "\n";
        cout << "Seccion Asignada: " << estudiante.cursos[k].seccion << "\n\n";
    }
    if (estudiante.cursos.empty()) {
        cout << "No se han asignado cursos a este estudiante.\n";
    }
}

void mostrarNotas(const Estudiante& estudiante) {               
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << ROJO;
    cout << "\n                 --- Notas Asignadas ---\n";
    cout << "-----------------------------------------------------------\n";
    for (size_t k = 0; k < estudiante.cursos.size(); ++k) {
        cout << "Curso: " << estudiante.cursos[k].nombre << "\n";
        cout << "Nota Final: " << estudiante.cursos[k].notaFinal << "\n";
        cout << "Estado Actual del Curso: " << (estudiante.cursos[k].notaFinal >= 60 ? "Aprobado" : "Desaprobado") << "\n";
        cout << "-----------------------------------------------------------\n";
    }
    if (estudiante.cursos.empty()) {
        cout << "No se han registrado notas para este estudiante.\n";
    }
}

bool registrarEstudiante() {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.codigoPersonal = generarCodigoPersonal();
    cout << GRIS_NORMAL << BLANCO_INTENSO;
    cout << "            --- Registro de estudiantes ---                       \n";
    cout << "-----------------------------------------------------------\n";
    cout << "Elija la carrera que desea cursar:\n";
    cout << "1. Ingenieria en sistemas\n";
    cout << "2. Derecho\n";
    cout << "3. Auditoria\n";
    cout << "-----------------------------------------------------------\n";
    int carreraOpcion = seleccionarOpcion("Seleccione una opcion (1-3): ", 3);
    cout << "-----------------------------------------------------------\n";
    switch (carreraOpcion) {
        case 1: nuevoEstudiante.carrera = "Ingenieria en sistemas"; break;
        case 2: nuevoEstudiante.carrera = "Derecho"; break;
        case 3: nuevoEstudiante.carrera = "Auditoria"; break;
    }

    
    string primerNombre;
    cout << "Ingrese el primer nombre: ";
    cin.ignore(); 
    getline(cin, primerNombre); 
    cout << "-----------------------------------------------------------\n";
    nuevoEstudiante.nombreCompleto = primerNombre;

    
    char agregarSegundoNombre;
    cout << "¿Desea agregar un segundo nombre? (s/n): ";
    cin >> agregarSegundoNombre;
    cout << "-----------------------------------------------------------\n";
    if (agregarSegundoNombre == 's' || agregarSegundoNombre == 'S') {
        string segundoNombre;
        cout << "Ingrese el segundo nombre: ";
        cin.ignore(); 
        getline(cin, segundoNombre);
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + segundoNombre;
    }

    
    char agregarTercerNombre;
    cout << "¿Desea agregar un tercer nombre? (s/n): ";
    cin >> agregarTercerNombre;
    cout << "-----------------------------------------------------------\n";
    if (agregarTercerNombre == 's' || agregarTercerNombre == 'S') {
        string tercerNombre;
        cout << "Ingrese el tercer nombre: ";
        cin.ignore(); 
        getline(cin, tercerNombre);
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + tercerNombre;
    }

    
    string primerApellido;
    cout << "Ingrese el primer apellido: ";
    cin.ignore(); 
    getline(cin, primerApellido); 
    cout << "-----------------------------------------------------------\n";
    nuevoEstudiante.nombreCompleto += " " + primerApellido;


    char agregarSegundoApellido;
    cout << "¿Desea agregar un segundo apellido? (s/n): ";
    cin >> agregarSegundoApellido;
    cout << "-----------------------------------------------------------\n";
    if (agregarSegundoApellido == 's' || agregarSegundoApellido == 'S') {
        string segundoApellido;
        cout << "Ingrese el segundo apellido: ";
        cin.ignore(); 
        getline(cin, segundoApellido); 
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + segundoApellido;
    }

    int diaNacimiento, mesNacimiento, anioNacimiento;
    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
    char slash;
    cin >> diaNacimiento >> slash >> mesNacimiento >> slash >> anioNacimiento;
    nuevoEstudiante.edad = calcularEdad(diaNacimiento, mesNacimiento, anioNacimiento);
    cout << "-----------------------------------------------------------\n";

    const string departamentos[] = {
        "Guatemala", "Sacatepequez", "Chimaltenango", "Escuintla", "Santa Rosa",
        "Solala", "Totonicapan", "Quetzaltenango", "Suchitepequez", "Retalhuleu"
    };
    cout << "Ingrese el numero del departamento en donde reside:\n";
    for (int i = 0; i < 10; ++i) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "-----------------------------------------------------------\n";
    int deptoOpcion = seleccionarOpcion("Seleccione una opcion (1-10): ", 10);
    nuevoEstudiante.departamento = departamentos[deptoOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    const string municipios[10][5] = {
        {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"},
        {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"},
        {"Chimaltenango", "San Martin de los Canes", "El Tejar", "San Jose Poaquil", "San Juan Comalapa"},
        {"Escuintla", "Santa Lucia Cotzumalguapa", "La Democracia", "San Jose", "Siquinala"},
        {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"},
        {"Solala", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palopo"},
        {"Totonicapan", "San Cristobal Totonicapan", "San Francisco el Alto", "San Andres Xecul", "Momostenango"},
        {"Quetzaltenango", "Salcaja", "San Martín Sacatepequez", "Sibilia", "Zunil"},
        {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitepequez", "Santo Domingo Suchitepequez"},
        {"Retalhuleu", "San Sebastian", "Champerico", "San Martin Zapotitlan", "Santa Cruz Mulua"}
    };
    cout << "Ingrese el numero del municipio en donde reside:\n";
    for (int i = 0; i < 5; ++i) {
        cout << i + 1 << ". " << municipios[deptoOpcion - 1][i] << endl;
    }
    cout << "-----------------------------------------------------------\n";
    int municipioOpcion = seleccionarOpcion("Seleccione una opcion (1-5): ", 5);
    nuevoEstudiante.municipio = municipios[deptoOpcion - 1][municipioOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el telefono personal (8 digitos): ";
    while (true) {
        string telefono;
        cin >> telefono;
        cout << "-----------------------------------------------------------\n";
        if (validarTelefono(telefono)) {
            nuevoEstudiante.telefonoPersonal = telefono;
            break;
        } else {
            cout << "Teléfono invalido. Ingrese nuevamente (8 digitos): ";
        }
    }

    cout << "Ingrese el telefono de casa (8 digitos): ";
    while (true) {
        string telefono;
        cin >> telefono;
        cout << "-----------------------------------------------------------\n";
        if (validarTelefono(telefono)) {
            nuevoEstudiante.telefonoCasa = telefono;
            break;
        } else {
            cout << "Telefono invalido. Ingrese nuevamente (8 digitos): ";
        }
    }

    cout << "Ingrese el correo electronico: ";
    cin >> nuevoEstudiante.correoElectronico;
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el año de ingreso: ";
    cin >> nuevoEstudiante.anioIngreso;
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el semestre: ";
    cin >> nuevoEstudiante.semestre;
    cout << " \n";
    cout << " \n";

    estudiantes.push_back(nuevoEstudiante);
    
    mostrarEstudiante(nuevoEstudiante);
    cout << GRIS_NORMAL << BLANCO;
    cout << "Estudiante registrado con exito. Codigo Personal: " << nuevoEstudiante.codigoPersonal << "\n";
    cout << "-----------------------------------------------------------\n";
    
    char volverARegistrar;
    cout << "¿Quiere volver a registrar un estudiante? (s/n): ";
    cin >> volverARegistrar;
    cout << " \n";
    cout << " \n";
    if (volverARegistrar == 's' || volverARegistrar == 'S') {
        registrarEstudiante(); 
    }

    return true;
}


void controlNotas() {
    string codigoEstudiante;
    
    cout << "Ingrese el codigo del estudiante: ";
    cin >> codigoEstudiante;
    cout << " \n";
    cout << " \n";
    cout << "-----------------------------------------------------------\n";
    cout << "\n                --- Control de notas ---\n";
    cout << "-----------------------------------------------------------\n";

    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].codigoPersonal == codigoEstudiante) {
            vector<string> resultados;

            if (estudiantes[i].cursos.empty()) {
                cout << "Ningun alumno con asignacion de cursos.\n";
                return;
            }

            for (size_t j = 0; j < estudiantes[i].cursos.size(); ++j) {
                float notaParcial1, notaParcial2, zonaTotal, notaExamenFinal;

               
                cout << "\nCurso: " << estudiantes[i].cursos[j].nombre << "\n";

                
                do {
                    cout << "Ingrese la nota del primer parcial (0-15): ";
                    cin >> notaParcial1;
                } while (notaParcial1 < 0 || notaParcial1 > 15);

                do {
                    cout << "Ingrese la nota del segundo parcial (0-15): ";
                    cin >> notaParcial2;
                } while (notaParcial2 < 0 || notaParcial2 > 15);

                do {
                    cout << "Ingrese la zona total (0-35): ";
                    cin >> zonaTotal;
                } while (zonaTotal < 0 || zonaTotal > 35);

                do {
                    cout << "Ingrese la nota del examen final (0-35): ";
                    cin >> notaExamenFinal;
                    cout << "-----------------------------------------------------------\n";
                } while (notaExamenFinal < 0 || notaExamenFinal > 35);

                estudiantes[i].cursos[j].notaFinal = notaParcial1 + notaParcial2 + zonaTotal + notaExamenFinal;

                string estado = (estudiantes[i].cursos[j].notaFinal >= 60) ? "Aprobado" : "Reprobado";
                stringstream ss;
                ss << estudiantes[i].cursos[j].notaFinal;

                resultados.push_back("Curso: " + estudiantes[i].cursos[j].nombre);
                resultados.push_back("Nota Final: " + ss.str());
                resultados.push_back("Estado Actual del Curso: " + estado);
                resultados.push_back("-----------------------------------------------------------");
            }

            mostrarIconoGiratorio();  
            cout << GRIS_NORMAL << ROJO;
            cout << "\n               --- Resultados Finales ---\n";
            cout << "-----------------------------------------------------------\n";           
            for (size_t k = 0; k < resultados.size(); ++k) {
                cout << resultados[k] << "\n";
            }

            char volverRegistrar;
            cout << GRIS_NORMAL << BLANCO;
            cout << "¿Quieres volver a registrar notas? (s/n): ";
            cin >> volverRegistrar;
            cout << " \n";
            cout << " \n";
            if (volverRegistrar == 's' || volverRegistrar == 'S') {
                controlNotas(); 
            }
            return; 
        }
    }

    cout << "Estudiante no encontrado.\n";
}
