#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <string>
#include <windows.h>
#include <vector>

#define MAX_NOMBRE 100
#define MAX_ARR_LENGTH 100

int Bienvenida();
std::string get_string(std::string prompt, size_t size);
void gotoxy(short x, short y);

void Opcion1();
void Opcion2();
void Opcion3();
void Opcion4();
void Opcion5();

int main() {
    int opt;
    char charOpt = 's';

    do{
        if(tolower(charOpt) == 's'){
            opt = Bienvenida();

                switch(opt){
                    case 1:
                        Opcion1();
                        break;
                    case 2:
                        Opcion2();
                        break;
                    case 3:
                        Opcion3();
                        break;
                    case 4:
                        Opcion4();
                        break;
                    case 5:
                        Opcion5();
                        break;
                    case 0:
                        charOpt = 'n';
                        break;
                }

                if(opt != 0){            
                    std::cout << std::endl << std::endl << "Desea continuar? (s/n)\n>>> ";
                    std::cin >> charOpt;
                }

            }

            else{
                std::cout << std::endl << "Buen dia...";
            }

        if(tolower(charOpt) != 's' && tolower(charOpt) != 'n') std::cout << "\nOpcion invalida!\n";
    } while(tolower(charOpt) == 's');

    return 0;
}

int Bienvenida() {
    system("cls");

    int opt = 0;
     std::cout<< "================= ";
	std::cout<< "Mini proyecto";
	std::cout<< " =================";
	std::cout<<"\n";
    std::cout << "Bienvenido, seleccione una opcion: \n\n";
    std::cout << "1 - Grabar los registros\n";
    std::cout << "2 - Mostrar los registros\n";
    std::cout << "3 - Buscar un registro por codigo\n";
    std::cout << "4 - Modificar un campo y recalcular los valores\n";
    std::cout << "5 - Eliminar un registro segun su codigo\n";
    std::cout << "0 - Salir\n";

    do{
        std::cout << "\n\n>>> ";
        std::cin >> opt;

        if(opt != 1 && opt != 2 && opt != 3 && opt != 4 && opt != 5 && opt != 0) std::cout << "\nElija una opcion valida\n";        
    } while(opt != 1 && opt != 2 && opt != 3 && opt != 4 && opt != 5 && opt != 0);

    return opt;
}

struct producto {
    int codigo;
    std::string nombre;
    char linea;
    double precioEtiq;
    double precioOfer;
    int cantidad;
    double importeEtiq;
    double importeOfer;
    double IGV;
    double ImporteTotal;
};

void Opcion1() {
    system("cls");
    srand(time(NULL));
    
    int N = 0;
    std::cout << "Ingrese el numero de productos\n>>> ";
    std::cin >> N;

    producto templateProd;

    std::ofstream regisclean("productos.txt", std::ios::trunc);
    regisclean.close();

    std::ofstream regis("productos.txt", std::ios::app);

    for (int i = 0; i < N; i++) {
        templateProd.codigo = rand()%500 + 1;
        templateProd.nombre = get_string("Ingrese el nombre del producto " + std::to_string(i + 1) + " (max 30 car.)\n>>> ", 30);
        
        do {
            std::cout << "Ingrese la linea del producto\n>>> ";
            std::cin >> templateProd.linea;

            if (templateProd.linea != 'A' && templateProd.linea != 'B' && templateProd.linea != 'C') std::cout << "\nLinea invalida\n";
        } while (templateProd.linea != 'A' && templateProd.linea != 'B' && templateProd.linea != 'C');
        
        std::cout << "Ingrese el precio de etiqueta del producto\n>>> ";
        std::cin >> templateProd.precioEtiq;

        switch (templateProd.linea) {
        case 'A':
            templateProd.precioOfer = templateProd.precioEtiq * 0.9;
            break;
        case 'B':
            templateProd.precioOfer = templateProd.precioEtiq * 0.85;
            break;
        case 'C':
            templateProd.precioOfer = templateProd.precioEtiq * 0.8;
            break;
        }

        templateProd.cantidad = rand()%21 + 10;

        templateProd.importeEtiq = templateProd.precioEtiq * templateProd.cantidad;
        templateProd.importeOfer = templateProd.precioOfer * templateProd.cantidad;

        templateProd.IGV = 0.18 * templateProd.precioOfer;
        templateProd.ImporteTotal = templateProd.importeOfer + templateProd.IGV;

        regis << templateProd.codigo << "\n";
        regis << templateProd.nombre << "\n";
        regis << templateProd.linea << "\n";
        regis << templateProd.precioEtiq << "\n";
        regis << templateProd.precioOfer << "\n";
        regis << templateProd.cantidad << "\n";
        regis << templateProd.IGV << "\n";
        regis << templateProd.importeEtiq << "\n";
        regis << templateProd.importeOfer << "\n";
        regis << templateProd.ImporteTotal << "\n";
    }

    regis.close();
}

/*
    Utilizando estructura de registros, elaborar un programa en C++ que permita realizar lo siguiente:
        • Registrar N registros en un archivo externo TXT que contengan los siguientes campos de ventas de los
        productos:
        • Codigo (entero autogeneradoentre 1 y 500)
        • Nombre producto(string o char de 30)
        • Linea de Producto (A.electrodomesticos, B: línea blanca y C: audio y video)
        • Precio Etiqueta (soles)
        • Precio de Oferta ( Sobre precio etiqueta A= 10% , B=15%, C=20%
        • Cantidad (autogenerado entre 10 y 30)
        • Importe total Precio Etiqueta (soles)…(valor calculado)
        • Importe total Precio Oferta(soles) …(valor calculado)
        • IGV 18% sobre importe precio oferta…(valor calculado)
        • Importe Total = Importe total Precio Oferta + IGV…(valor calculado)

    Tener en cuenta lo siguiente:
        • Precio Oferta: Obtener el valor del descuento según la categoría
        • Importe Precio etiqueta = Cantidad x Precio Etiqueta
        • Importe Precio Oferta = Cantidad x Precio Oferta
        • IGV: considerar 18% sobre importe oferta
        • Importe Total= Importe total Precio Oferta + IGV

    Incluir las Operaciones Básicas de archivos:
        a) Grabar los registros en un archivo TXT
        b) Mostrar los registros grabados en modo Tabular
        c) Buscar un registro por código
        d) Modificar un campo y recalcular los valores calculados
        e) Eliminar un registro según su código
*/


void Opcion2() {
    system("cls");

    std::string buffer;

    std::ifstream productos("productos.txt");
    if (productos.fail()) {
        std::cout << "No se pudo abrir el archivo de productos";
        return;
    }

    std::string tipos[13] = {
        "Codigo",
        "Nombre",
        "Linea",
        "Precio de etiqueta",
        "Precio de Oferta",
        "Cantidad",
        "IGV",
        "Importe de Etiqueta",
        "Importe de Oferta",
        "Importe Total"
    };


    gotoxy(1, 1);
    std::cout << "Codigo";
    gotoxy(16, 1);
    std::cout << "Nombre";
    gotoxy(31, 1);
    std::cout << "Linea";
    gotoxy(46, 1);
    std::cout << "Precio etiq";
    gotoxy(61, 1);
    std::cout << "Precio Ofer";
    gotoxy(76, 1);
    std::cout << "Cantidad";
    gotoxy(91, 1);
    std::cout << "IGV";
    gotoxy(106, 1);
    std::cout << "Imp. Etiqueta";
    gotoxy(121, 1);
    std::cout << "Imp. de Oferta";
    gotoxy(136, 1);
    std::cout << "Imp. Total";

    size_t i = 0;
    size_t y = 0;
    while(std::getline(productos, buffer, '\n')) {
        gotoxy(1 + 15*i , y + 2);
        std::cout << buffer << "\n";        
        if (i == 9) {
            i = 0;
            y++;
        }
        else i++;

    }

    productos.close();
}

void Opcion3() {
    system("cls");

    std::string buffer;
    std::string checker;

    std::cout << "Ingrese el codigo del registro a modificar\n>>> ";
    std::cin >> checker;

    std::cout << std::endl;

    std::ifstream productos("productos.txt");
    if (productos.fail()) {
        std::cout << "No se pudo abrir el archivo de productos";
        return;
    }

    std::string tipos[10] = {
        "Codigo",
        "Nombre",
        "Linea",
        "Precio de etiqueta",
        "Precio de Oferta",
        "Cantidad",
        "IGV",
        "Importe de Etiqueta",
        "Importe de Oferta",
        "Importe Total",
    };

    std::string groupBuffer[10];

    size_t count = 0;
    while(!productos.eof()) {
        for (int j = 0; j < 10; j++) {
            std::getline(productos, groupBuffer[j], '\n');
        }

        if (groupBuffer[0] == checker) {
            std::cout << "==========\n";
            for (int i = 0; i < 10; i++) {
                std::cout << tipos[i] << ": " << groupBuffer[i] << "\n";
            }
            std::cout << "==========\n\n";
            count++;
        }
    }
    std::cout << "Se han encontrado " << count << "coincidencias";
    productos.close();
}

void Opcion4() {
    system("cls");

    std::string buffer;
    std::string checker;
    std::string newData;

    std::cout << "Ingrese el codigo a buscar\n>>> ";
    std::cin >> checker;


    std::cout << std::endl;

    std::ifstream productos("productos.txt");
    if (productos.fail()) {
        std::cout << "No se pudo abrir el archivo de productos";
        return;
    }

    std::ofstream output("out.txt");
    if (output.fail()) {
        std::cout << "No se pudo crear el archivo de salida modificado";
        return;
    }

    std::string tipos[10] = {
        "Codigo",
        "Nombre",
        "Linea",
        "Precio de etiqueta",
        "Precio de Oferta",
        "Cantidad",
        "IGV",
        "Importe de Etiqueta",
        "Importe de Oferta",
        "Importe Total",
    };

    std::string groupBuffer[10];

    size_t count = 0;
    bool printable = true;

    while(!productos.eof()) {
        for (int j = 0; j < 10; j++) {
            if (!std::getline(productos, groupBuffer[j], '\n')) {
                printable = false;
                break;
            }
            else printable = true;
        }

        if (groupBuffer[0] == checker) {
            std::cout << "==========\n";
            for (int i = 0; i < 10; i++) {
                std::cout << tipos[i] << ": " << groupBuffer[i] << "\n";
            }
            std::cout << "==========\n\n";

            std::cout << "Ingrese el nuevo nombre para este registro\n>>> ";
            std::cin >> newData;

            groupBuffer[1] = newData;

            count++;
        }

        for (int k = 0; k < 10 && printable; k++) {
            output << groupBuffer[k] << "\n";
        }
    }

    productos.close();
    std::remove("productos.txt");

    output.close();
    std::rename("out.txt", "productos.txt");
}

void Opcion5() {
    system("cls");

    std::string buffer;
    std::string checker;
    std::string newData;

    std::cout << "Ingrese el codigo a buscar\n>>> ";
    std::cin >> checker;


    std::cout << std::endl;

    std::ifstream productos("productos.txt");
    if (productos.fail()) {
        std::cout << "No se pudo abrir el archivo de productos";
        return;
    }

    std::ofstream output("new.txt");
    if (output.fail()) {
        std::cout << "No se pudo crear el archivo de salida modificado";
        return;
    }

    std::string tipos[10] = {
        "Codigo",
        "Nombre",
        "Linea",
        "Precio de etiqueta",
        "Precio de Oferta",
        "Cantidad",
        "IGV",
        "Importe de Etiqueta",
        "Importe de Oferta",
        "Importe Total",
    };

    std::string groupBuffer[10];

    size_t count = 0;
    bool printable = true;

    while(!productos.eof()) {
        for (int j = 0; j < 10; j++) {
            if (!std::getline(productos, groupBuffer[j], '\n')) {
                printable = false;
                break;
            }
            else printable = true;
        }

        if (groupBuffer[0] == checker) {
            printable = false;
            std::cout << "==========\n";
            for (int i = 0; i < 10; i++) {
                std::cout << tipos[i] << ": " << groupBuffer[i] << "\n";
            }
            std::cout << "==========\n\n";
            count++;
        }

        for (int k = 0; k < 10 && printable; k++) {
            output << groupBuffer[k] << "\n";
        }
    }

    productos.close();
    std::remove("productos.txt");

    output.close();
    std::rename("new.txt", "productos.txt");
}


std::string get_string(std::string prompt, size_t size) {
    char buffer[size];
    do {
        std::cout << prompt;
        fflush(stdin);
        std::cin.getline(buffer, MAX_NOMBRE, '\n');
        if (strlen(buffer) > size) std::cout << "\nNombre Invalido (demasiado largo)\n";
    } while (strlen(buffer) > size);

    std::string str = buffer;
    return str;
}

void gotoxy(short x, short y) {
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
}
