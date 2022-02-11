#include "funciones.h"


using namespace std;

int main()
{
    int opcion;

    menuCajero(); //Muestra el menu del cajero y recibe la opcion
    cin >> opcion;

    system("CLS");//clear screen
    switch (opcion) {
    case 1:
        mostrarSaldo();
        break;

    case 2:
        retirarSaldo();
        break;

    case 3:
        if(verificarContrasena()){
            menuOperador();
            cin >> opcion;
            switch(opcion){
            case 1:
                nuevoUsuario();
                break;
            case 2:
                return 0;
            default:
                cout << "Opcion invalida" << endl;
            }
        }
        else{
            cout << "Ha superado el numero de intentos permitidos" << endl;
        }

        break;
    case 4:
        return  0;

    default:
        cout << "Opcion invalida." << endl;
    }

    return 0;
}
