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
    string genero;
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
    cout << "Carrera: " << estudiante.carrera << "\n";
    cout << "\n";
    cout << "Nombre Completo: " << estudiante.nombreCompleto << "\n"; 
    cout << "\n";
    cout << "Genero: " << estudiante.genero << "\n";
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

    cout << "Seleccione el género:\n";
    cout << "1. Masculino\n";
    cout << "2. Femenino\n";
    cout << "-----------------------------------------------------------\n";
    
    int generoOpcion = seleccionarOpcion("Seleccione una opcion (1-2): ", 2);
    nuevoEstudiante.genero = (generoOpcion == 1) ? "Masculino" : "Femenino";

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
    }

    string primerApellido;
    cout << "Ingrese el primer apellido: ";
    cin.ignore(); 
    getline(cin, primerApellido); 
    cout << "-----------------------------------------------------------\n";
    nuevoEstudiante.nombreCompleto += " " + primerApellido;

    if (generoOpcion == 2) {
        cout << "¿Desea agregar:\n";
        cout << "1. Apellido de casada\n";
        cout << "2. Segundo apellido\n";
        cout << "3. Ninguno\n";
        cout << "-----------------------------------------------------------\n";
        
        int opcionApellidoCasada = seleccionarOpcion("Seleccione una opción (1-3): ", 3);

        if (opcionApellidoCasada == 1) {
            string apellidoCasada;
            cout << "Ingrese el apellido de casada: ";
            cin.ignore(); 
            getline(cin, apellidoCasada);
            cout << "-----------------------------------------------------------\n";
            nuevoEstudiante.nombreCompleto += " " + apellidoCasada;
        } else if (opcionApellidoCasada == 2) {
            string segundoApellido;
            cout << "Ingrese el segundo apellido: ";
            cin.ignore(); 
            getline(cin, segundoApellido);
            cout << "-----------------------------------------------------------\n";
            nuevoEstudiante.nombreCompleto += " " + segundoApellido;
        }
    } else {
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
    }

    int diaNacimiento, mesNacimiento, anioNacimiento;
    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
    char slash;
    cin >> diaNacimiento >> slash >> mesNacimiento >> slash >> anioNacimiento;
    nuevoEstudiante.edad = calcularEdad(diaNacimiento, mesNacimiento, anioNacimiento);
    cout << "-----------------------------------------------------------\n";

    const string departamentos[] = {
        "Guatemala", "Sacatepéquez", "Chimaltenango", "Escuintla", "Santa Rosa",
        "Solola", "Totonicapan", "Quetzaltenango", "Suchitepequez", "Retalhuleu",
        "San Marcos", "Huehuetenango", "Quiche", "Baja Verapaz", "Alta Verapaz",
        "Peten", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
    };

    cout << "Ingrese el numero del departamento en donde reside:\n";
    for (int i = 0; i < 10; ++i) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "-----------------------------------------------------------\n";
    
    int deptoOpcion = seleccionarOpcion("Seleccione una opcion (1-10): ", 10);
    nuevoEstudiante.departamento = departamentos[deptoOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    const std::string municipios[22][15] = {
        {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula", "San Jose del Golfo", "San Pedro Ayampuc", "Palencia", "Chinautla", "Fraijanes", "Amatitlan", "San Juan Sacatepequez", "Villa Canales"},
        {"Antigua Guatemala", "San Lucas Sacatepeqez", "San Bartolome Milpas Altas", "Sumpango", "Magdalena Milpas Altas", "San Miguel Duenas", "Santa Maria de Jesus", "Ciudad Vieja", "Pastores", "San Juan Alotenango", "Acatenango"},
        {"Chimaltenango", "San Jose Poaquil", "San Martin Jilotepeque", "Patzun", "Tecoanapa", "San Juan Comalapa", "Patzicia", "El Tejar", "San Andres Itzapa", "San Pedro Yepocapa", "Santa Apolonia"},
        {"Escuintla", "Santa Lucia Cotzumalguapa", "La Democracia", "San Jose", "Masagua", "San Vicente Pacaya", "Nueva Concepcion", "El Rosario", "Siquinala", "Guanagazapa", "San Pedro Mazapa"},
        {"Santa Rosa de Lima", "Cuilapa", "Barberena", "San Rafael Las Flores", "Chiquimulilla", "Guazacapan", "San Juan Tecuaco", "Santa Maria Ixhuatan", "El Sasle", "Oratorio", "San Pedro de Mitope"},
        {"Solola", "San Jose Chacaya", "San Juan La Laguna", "San Pablo La Laguna", "San Marcos La Laguna", "Santa Catarina Palopo", "Santa Cruz La Laguna", "Chichicastenango", "Nahuala", "San Antonio Palopo", "San Lucas Toliman"},
        {"Totonicapan", "San Cristobal Totonicapan", "San Francisco El Alto", "Santa Maria Chiquimula", "San Andres Xecul", "San Bartolo", "Momostenango", "Panchoy", "San Juan Ixcoy", "Santa Lucia La Reforma"},
        {"Quetzaltenango", "Olintepeque", "San Carlos Sija", "Sibilia", "La Esperanza", "Salcaja", "San Francisco La Union", "Cantel", "Colomba", "Zunil", "San Mateo", "San Juan Bautista"},
        {"Suchitepequez", "Mazatenango", "San Bernardino", "San Francisco Zapotitlan", "Zunilito", "Samayac", "San Miguel Panan", "Retalhuleu", "Santa Barbara", "San Jose El Idolo", "San Pedro La Laguna"},
        {"Retalhuleu", "San Sebastian", "San Martin Zapotitlan", "El Asintal", "Nuevo San Carlos", "San Felipe", "Champerico", "San Andres Villa Seca", "Santa Cruz Mulua"},
        {"San Marcos", "San Pedro Sacatepequez", "Tierra Blanca", "Nuevo Progreso", "Malacatan", "San Miguel Ixtahuacán", "La Reforma", "San Jose El Golfo", "Catarina", "Ixchiguan", "El Quetzal", "San Antonio Sacatepeqez"},
        {"Huehuetenango", "Chiantla", "Cuilco", "Jacaltenango", "Nenton", "San Mateo Ixtatan", "San Juan Ixcoy", "San Pedro Necta", "La Libertad", "Malacatancito", "Santa Barbara"},
        {"Quiche", "Santa Cruz del Quiche", "Chiche", "Zaragoza", "San Antonio Ilotenango", "San Juan Cotzal", "Chajul", "San Pedro Jocopilas", "Joyabaj", "Patzite", "El Quiche"},
        {"Baja Verapaz", "Salama", "San Miguel Chicaj", "Rabinal", "Granados", "Santa Cruz El Chol", "San Jeronimo", "Purulha", "San Pedro Carchá"},
        {"Alta Verapaz", "Coban", "Santa Cruz Verapaz", "San Cristobal Verapaz", "Tactic", "Raxruha", "San Juan Chamelco", "Chisec", "Fray Bartolome de las Casas", "Panzos", "Senahu", "La Tinta", "Lanquín", "San Pedro Carcha"},
        {"Izabal", "Puerto Barrios", "Livingston", "El Estor", "Moran", "Los Amates", "Santa Maria Xalapan"},
        {"Peten", "Flores", "Santa Elena", "San Benito", "La Libertad", "San Francisco", "Dolores", "Poptun", "Sayaxche", "Las Flores", "El Chal", "Tayasal", "San Andres", "San Luis", "San Jose"},
        {"Zacapa", "Zacapa", "La Union", "Estanzuela", "Teculutan", "Gualan", "San Jorge", "Cabanas", "Huité", "Chiquimula de la Sierra", "San Juan Ermitas"},
        {"Chiquimula", "Chiquimula", "San Jose La Arada", "Camotan", "Quezaltepeque", "San Juan Ermita", "Concepcion Las Minas", "Jocotan", "Olopa", "Cabanas"},
        {"Jalapa", "Jalapa", "San Pedro Pinula", "San Luis Jilotepeque", "San Manuel Chaparron", "Mataquescuintla", "Tierra Blanca", "Nuevo Orleans"},
        {"Jutiapa", "El Progreso", "Santa Catarina Mita", "San Jose Acatempa", "Agua Blanca", "Jerez", "Concepcion Jumaytepeque", "San Manuel", "Moyuta", "Tepec", "San Luis"},
        {"El Progreso", "Guastatoya", "San Antonio La Paz", "San Cristobal Acasaguastlan", "Morazan", "Sanarate", "San Jose del Golfo"}
    };

    cout << "Ingrese el numero del municipio en donde reside:\n";
    int maxMunicipios = 0;
    for (int i = 0; i < 15 && !municipios[deptoOpcion - 1][i].empty(); ++i) {
        cout << i + 1 << ". " << municipios[deptoOpcion - 1][i] << endl;
        maxMunicipios++;
    }
    cout << "-----------------------------------------------------------\n";

    int municipioOpcion;
    while (true) {
        municipioOpcion = seleccionarOpcion("Seleccione una opcion: ", maxMunicipios);
        if (municipioOpcion >= 1 && municipioOpcion <= maxMunicipios) {
            break;
        } else {
            cout << "Opción inválida. Por favor ingrese un número entre 1 y " << maxMunicipios << ": ";
        }
    }

    nuevoEstudiante.municipio = municipios[deptoOpcion - 1][municipioOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    // Teléfonos
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
            cout << "Teléfono invalido. Ingrese nuevamente (8 digitos): ";
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

    // Aquí añadirías el nuevo estudiante a la lista
    mostrarEstudiante(nuevoEstudiante);
    cout << "Estudiante registrado con éxito. Código Personal: " << nuevoEstudiante.codigoPersonal << "\n";
    cout << "-----------------------------------------------------------\n";
    
    char volverARegistrar;
    cout << "¿Quiere volver a registrar un estudiante? (s/n): ";
    cin >> volverARegistrar;
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


void asignarCursos() {
    string codigo;
    bool codigoValido = false;

    while (!codigoValido) {
        cout << "Ingrese el codigo del estudiante: ";
        cin >> codigo;
        cout << " \n";
        cout << " \n";
        cout << "-----------------------------------------------------------\n";

        if (validarCodigoEstudiante(codigo)) {
            codigoValido = true;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigo) {
                    cout << "              --- Asignacion de cursos ---\n";
                    cout << "-----------------------------------------------------------\n";
                    cout << "Cursos disponibles para " << estudiantes[i].nombreCompleto << ":\n";
                    cout << "-----------------------------------------------------------\n";

                    string cursos[5];
                    int cantidadCursos = 0;

                    if (estudiantes[i].carrera == "Ingenieria en sistemas") {
                        cursos[cantidadCursos++] = "Algebra lineal";
                        cursos[cantidadCursos++] = "Algoritmos";
                        cursos[cantidadCursos++] = "Contabilidad";
                        cursos[cantidadCursos++] = "MatemAtica discreta";
                        cursos[cantidadCursos++] = "Pre cAlculo";
                    } else if (estudiantes[i].carrera == "Derecho") {
                        cursos[cantidadCursos++] = "Derecho Civil";
                        cursos[cantidadCursos++] = "Derecho Penal";
                        cursos[cantidadCursos++] = "Derecho Constitucional";
                        cursos[cantidadCursos++] = "Derecho Internacional";
                        cursos[cantidadCursos++] = "Derecho Laboral";
                    } else if (estudiantes[i].carrera == "Auditoría") {
                        cursos[cantidadCursos++] = "Auditoria Financiera";
                        cursos[cantidadCursos++] = "Auditoria Interna";
                        cursos[cantidadCursos++] = "Auditoria de Sistemas";
                        cursos[cantidadCursos++] = "Auditoria de Cumplimiento";
                        cursos[cantidadCursos++] = "Auditoria Forense";
                    }

                    for (int j = 0; j < cantidadCursos; ++j) {
                        char seccion;
                        cout  << cursos[j] << "\n";
                        cout << "\n";
                        cout << "¿Que seccion desea asignarle? (A, B, C, D): ";
                        cin >> seccion;
                        cout << "-----------------------------------------------------------\n";

                        Curso nuevoCurso;
                        nuevoCurso.nombre = cursos[j];
                        nuevoCurso.codigo = generarCodigoPersonal(); 
                        nuevoCurso.seccion = seccion;

                        estudiantes[i].cursos.push_back(nuevoCurso);
                    }

                    mostrarCursosAsignados(estudiantes[i]);

                    
                    char asignarOtro;
                    cout << "-----------------------------------------------------------\n";
                    cout << GRIS_NORMAL << BLANCO;
                    cout << "¿Quiere asignarle cursos a otro alumno? (s/n): ";
                    cin >> asignarOtro;
                    cout << " \n";
                    cout << " \n";
                    if (asignarOtro == 's' || asignarOtro == 'S') {
                        asignarCursos(); 
                    }
                    break;
                }
            }
        }
    }
}


void mostrarDatosRegistrados() {
    int opcion;
    do {
        cout << GRIS_NORMAL << BLANCO_INTENSO;
        cout << "\n            --- Mostrar Datos Registrados ---\n";
        cout << "-----------------------------------------------------------\n";
        cout << "1. Mostrar Estudiantes Registrados\n";
        cout << "2. Mostrar Cursos Asignados\n";
        cout << "3. Mostrar Notas Ingresadas\n";
        cout << "4. Salir\n"; 
        cout << "-----------------------------------------------------------\n";
        opcion = seleccionarOpcion("Seleccione una opcion (1-4): ", 4);
        cout << " \n";
        cout << " \n";
        

        if (opcion == 1) {
            string codigoEstudiante;
            cout << "Ingrese el codigo del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarEstudiante(estudiantes[i]);
                    encontrado = true;
                    break; 
                }
            }
          
        } else if (opcion == 2) {
            string codigoEstudiante;
            cout << "Ingrese el codigo del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarCursosAsignados(estudiantes[i]);
                    encontrado = true;
                    break; 
                }
            }
            
        } else if (opcion == 3) {
            string codigoEstudiante;
            cout << "Ingrese el codigo del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarNotas(estudiantes[i]);
                    encontrado = true;
                    break; 
                }
            }
            
        }

    } while (opcion != 4); 
}


int main() {
	system("COLOR 8F");
    srand(static_cast<unsigned int>(time(0))); 
    
    mostrarIconoGiratorio();



    int opcion;
    do {
    	cout << GRIS_NORMAL << BLANCO_INTENSO;
    	cout << "===========================================================\n";
        cout << "\n                 --- Menu Principal ---               \n";
        cout << "===========================================================\n";
        cout << "1. Registrar Estudiante                          \n";
        cout << "2. Asignacion de Cursos                          \n";
        cout << "3. Control de Notas                          \n";
        cout << "4. Mostrar Datos Registrados            \n";
        cout << "5. Salir                             \n";
        cout << "-----------------------------------------------------------\n";
        opcion = seleccionarOpcion("Seleccione una opcion (1-5): ", 5); 
        cout << " \n";
        cout << " \n";
        cout << "-----------------------------------------------------------\n";

        switch (opcion) {
            case 1:
                registrarEstudiante();
                break;
            case 2:
                asignarCursos();
                break;
            case 3:
                controlNotas();
                break;
            case 4:
                mostrarDatosRegistrados();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
        }
    } while (opcion != 5);
    
    return 0;
}
