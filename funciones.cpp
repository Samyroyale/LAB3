#include "funciones.h"

//Cadena a binario
string Cabin(string texto){


    string bin, textobinario;
    unsigned num;

    for(unsigned long i=0; i<texto.length(); ++i){//recorre el texto
        num=texto[i];
        for(int h=0; h<8; ++h){
            bin+=(num%2)+48;
            num/=2;
        }
        bin=reverse(bin);
        textobinario+=bin;
        bin="";//construccion equivalente en binario
    }

    return textobinario;
}
//Binario a caracter

string Binca(string textobinario){
    string bin, textocaracteres;
    int dec;

    for(unsigned long i=0; i<textobinario.length(); i+=8){
        dec=0;
        bin=textobinario.substr(i,8);//subcadena
        bin=reverse(bin);
        for(int h=0; h<8; ++h){
            dec+=(int(bin[h])-48)*pow(2,h);
        }
        textocaracteres+=char(dec);
    }

    return textocaracteres;
}

string Codificar1(string textobinario, int semilla){
    //Codificar con el primer metodo

    string bloque, codificado="";
    long unos=0, ceros=0;//conteo de unos y ceros

    for(unsigned long i=0; i<textobinario.length(); i+=semilla){
        bloque=textobinario.substr(i,semilla);

        if(unos==ceros){
            codificado+=Invertir(bloque,1);
        }
        else if(ceros>unos){
            codificado+=Invertir(bloque,2);
        }
        else{
            codificado+=Invertir(bloque,3);
        }

        unos=Contar1y0(bloque,'1');
        ceros=Contar1y0(bloque,'0');

    }

    return codificado;
}
//Decodificar metodo 1
string Decodificar1(string codificado, int semilla){

    string bloque, decodificado="";
    long unos=0, ceros=0;

    for(unsigned long i=0; i<codificado.length(); i+=semilla){
        bloque=codificado.substr(i,semilla);

        if(unos==ceros){
            decodificado+=Invertir(bloque,1);
        }
        else if(ceros>unos){
            decodificado+=Invertir(bloque,2);
        }
        else{
            decodificado+=Invertir(bloque,3);
        }

        unos=Contar1y0(decodificado.substr(i,semilla),'1');
        ceros=Contar1y0(decodificado.substr(i,semilla),'0');

    }

    return decodificado;
}

//codifica un bloque de bits
string Invertir(string binario, int num){

    for(unsigned long i=1; i<=binario.length(); ++i){
        if(i%num==0){
            if(binario[i-1]=='0')
                binario[i-1]='1';
            else
                binario[i-1]='0';
        }
    }

    return binario;
}
//Cuenta la cantidad de unos y ceros en un bloque de n bits
long Contar1y0(string binario, char numero){
    long contador=0;
    for(unsigned long i=0; i<binario.length(); ++i){
        if(binario[i]==numero)
            contador++;
    }

    return contador;
}
//Abre un archivo y lo lee
string Leer(string nombre, int tipo){

    ifstream archivo;
    string texto, aux;

    archivo.open(nombre); //abrir el archivo
    if (archivo.is_open()){
        while (!archivo.eof()) { //end of a line
            getline(archivo,aux);

            if(tipo==1)
                texto+=aux+'\n'; //Termina una linea
            else
                texto+=aux;
        }
        archivo.close();//cerrar archivo
    }
    else{
        cout << "NO ES POSIBLE ABRIR EL ARCHIVO." << endl;
        exit(1);
    }

    return texto;
}

//Escribir un archivo
void Escribir(string nombre, string texto, int tipo){


    ofstream archivo;

    if(tipo == 1){
        archivo.open(nombre, ios::trunc);//contenido de archivo actual será descartado
    }
    else{
        archivo.open(nombre, ios::app);//agregará al archivo.
    }
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    archivo << texto;

    archivo.close();//Cerrar archivo
}

string reverse(string cadena){
    //Invierte una cad String

    string auxcadena;

    for(long long i=cadena.length()-1; i>=0; --i){
        auxcadena+=cadena[i];
    }

    return  auxcadena;
}

void menuCajero()
//Mostrar el menu del cajero
{
    cout << "~~~~~~~~~~ CAJERO AUTOMATICO ~~~~~~~~~~" << endl
         << "1. Consultar saldo." << endl
         << "2. Retirar dinero." << endl
         << "3. Entrar como administrador." << endl
         << "4. SALIR." << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << "Opcion: ";
}

void menuOperador()
//Mostrar el menu del administrador
{
    cout << "|~~~~~~~ BIENVENIDO ADEMINISTRADOR ~~~~~~~~ |" << endl
         << "|1. Nuevo usuario modificar usuario         |" << endl
         << "|2. SALIR                                   |" << endl
         << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl
         << "|Opcion:                                 ";
}

//VERIFICA EN EL ARCHIVO ASIGANADO SI LA CLAVE CODIFICADA COINCIDE CON LA DEL ADMIN
bool verificarContrasena()

{
    string contrasena;
    int errores = 0;

    do{
        cout << "Por favor ingrese la contrasena: ";
        cin >> contrasena;
        system("CLS");

        if(contrasena == Binca(Decodificar1(Leer("C:/Users/santi/Google Drive/Tareas/Santiago/UdeA/2021_2/InformaticaII/Lab/Practica3/sudo.txt", 2), 4))){
            return true;
        }
        cout << "Contrasena incorrecta. Intente de nuevo." << endl;
        errores++;
    }while (errores < 3);

    system("CLS");

    return false;
}
//Añade un usuario
void nuevoUsuario()
{
    string usuario[3];
    string datos[3]={"Cedula","Clave","Saldo"};

    for(int i=0; i<3; ++i){
        system("CLS");
        cout << datos[i] << ": ";
        cin >> usuario[i];
        while(!isNum(usuario[i])){
            system("CLS");
            cout << "Solo se admiten numeros." << endl
                 << datos[i] << ": ";
            cin >> usuario[i];
        }
    }
    Escribir("C:/Users/santi/Google Drive/Tareas/Santiago/UdeA/2021_2/InformaticaII/Lab/Practica3/data.txt", Codificar1(Cabin(usuario[0]+","+usuario[1]+","+usuario[2]+"\n"), 4), 2);
}
//Verifica si una cadena es numerica
bool isNum(string cadena)
{
    for(int i=0; i<int(cadena.size()); ++i){
        if(!(cadena[i]>= 48 && cadena[i] <=57)){
            return false;
        }
    }
    return true;
}

//Buscar el usuario
string buscarDatos(string __cedula__)

{
    int contador = 0;
    string datos[100][3] = {}, aux, aux1 = Binca(Decodificar1(Leer("C:/Users/santi/Google Drive/Tareas/Santiago/UdeA/2021_2/InformaticaII/Lab/Practica3/data.txt",2),4));
    for(int j=0; aux1.size()>0; ++j){
        aux = aux1.substr(0,aux1.find("\n"));//subcadens entre lineas
        for(int i=0; i<3;++i){
            //cedula, calve separados por (,)
            datos[j][i] = aux.substr(0,aux.find(","));
            aux = aux.substr(aux.find(",")+1, aux.size());
        }
        aux1 = aux1.substr(aux1.find("\n")+1, aux1.size());
        contador++;
    }

    for(int i=0; i<contador; ++i){
        if(datos[i][0] == __cedula__){
            return datos[i][1]+ "," + datos[i][2];
        }
    }
    return  "-1";
}

//muestra al usaurio su saldo
void mostrarSaldo()

{
    string cedula, contrasena, aux;

    cout << "Cedula:";
    cin >> cedula;

    aux = buscarDatos(cedula);

    system("CLS");
    if(!(aux == "-1")){//Si existe
        cout << "Contrasena: ";
        cin >> contrasena;
        system("CLS");
        //BUSCAR AL USAURIO
        if(contrasena == aux.substr(0, aux.find(","))){
            if(atoi(aux.substr(aux.find(",")+1,aux.size()).c_str()) <0 ){
                cout << "Saldo insuficiente para realizar esta accion. " << endl;
            }
            else{
                cout << "Saldo: " << aux.substr(aux.find(",")+1,aux.size()) << endl;
                restarSaldo(cedula, 1000);
            }
        }

    }else{
        cout << "la cedula ingresada no se encuentra registrada" << endl;
    }
}

//resta saldo por accion del usuario
void restarSaldo(string __cedula__, int __cantidad__)
{
    int contador = 0;
    string datos[100][3] = {}, aux, aux1 = Binca(Decodificar1(Leer("C:/Users/santi/Google Drive/Tareas/Santiago/UdeA/2021_2/InformaticaII/Lab/Practica3/data.txt",2),4));
    for(int j=0; aux1.size()>0; ++j){
        aux = aux1.substr(0,aux1.find("\n"));
        //calve, cedla separados por (,)
        for(int i=0; i<3;++i){
            datos[j][i] = aux.substr(0,aux.find(","));
            aux = aux.substr(aux.find(",")+1, aux.size());
        }
        aux1 = aux1.substr(aux1.find("\n")+1, aux1.size());
        contador++;
    }

    for(int i=0; i<contador; ++i){
        if(datos[i][0] == __cedula__){
            datos[i][2] = to_string(atoi((datos[i][2]).c_str())-__cantidad__);
        }
    }

    string datosAux = "";
    for(int i=0; i<contador; ++i){
        datosAux += datos[i][0] + "," + datos[i][1] + "," + datos[i][2] + "\n";
    }
    Escribir("C:/Users/santi/Google Drive/Tareas/Santiago/UdeA/2021_2/InformaticaII/Lab/Practica3/data.txt", Codificar1(Cabin(datosAux),4), 1);
}

//Restar la cantidad que el usaurio retire
void retirarSaldo()
{
    string cedula, contrasena, aux;
    int cantidad;

    cout << "Cedula:";
    cin >> cedula;

    aux = buscarDatos(cedula);
    system("CLS");
    if(!(aux == "-1")){
        cout << "Contrasena: ";
        cin >> contrasena;
        system("CLS");
        cout << "Ingrese la cantidad a retirar: ";
        cin >> cantidad;
        system("CLS");
        //Buscar el usaurio
        if(contrasena == aux.substr(0, aux.find(","))){
            if(atoi(aux.substr(aux.find(",")+1,aux.size()).c_str()) < cantidad ){
                cout << "Saldo insuficiente para realizar esta accion. " << endl;
            }
            else{
                cout << "Saldo restante: " << atoi(aux.substr(aux.find(",")+1,aux.size()).c_str())-cantidad << endl;
                restarSaldo(cedula, cantidad);//Restar cantidad ingresada
                restarSaldo(cedula, 1000);//cobro de uso
            }
        }

    }else{
        cout << "la cedula ingresada no se encuentra registrada" << endl;
    }
}
//-------------------------------------------------------------------------------------------------------------------------
void codificar2( unsigned long long tam, int n, string binarios){

    char n1, n2 ;

    int x, cont1 = 1 ;
    //recorrer el arreglo binarios
    for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){

        if( cont1 == 1 ){

            x = i ;     //Coordenada inicial de cada grupo

            cont1++ ;
        }
        else if( cont1 > 1 ){

            if( cont1 == n ){

                n1 = binarios[i] ;

                binarios[i] = binarios[x] ;  //Cambia ha al ultima posicion el elemento inicial

                binarios[x] = n1 ;      //La Ultima la volvemos inicail

            }
            else{
                //Almacena el inicial

                n1 = binarios[x] ;
                //Almacena el Actual

                n2 = binarios[i] ;
                //LLevamos a la pos actual lo que hay en la inicial
                binarios[i] = n1 ;
                //Llevamos a la pos inicial lo que habia en la actual

                binarios[x] = n2 ;

            }

            cont1++ ;
        }


        if( cont1 > n ){        //Se reinia el contador

           cont1 = 1 ;
        }

    }


    cout<<binarios;//se retorna el binarios

}

void decodificar2( unsigned long long tam, int n, string codif ){

    int cont = 1, x ;

    char n1, n2 ;

    for( unsigned long long i = 0 ; i < (tam*8) ; i++ ){


        if( cont == 1 ){
    //Inicializacion de la posicion
            x = i ;
            cont++ ;

        }
        else if( cont > 1 ){

           n1 = codif[x] ;

           n2 = codif[i] ;

           codif[i] = n1 ;

           codif[x] = n2 ;

           x = i ;

           cont++ ;

        }


        if( cont > n ){     //Se reinicia el contador

            cont = 1 ;

        }

    }

    cout<<codif;//se retorna el codificado

}
//-------------------------------------------------------------------------------------------------------------------------




