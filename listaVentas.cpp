#include "listaVentas.hpp"

int auxX = 0;//Variable publica.

List::List()
{
    hojas = 0;
    H = new NodoL();
    H->setNext(H);
    H->setPrev(H);
    H->setLeft(nullptr);
    H->setRight(nullptr);
}

List::~List()
{
    clear();
}

bool List::isValid(NodoL*p)
{
    NodoL* aux = H->getNext();

    while(aux != H){
        if(p == aux){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

bool List::isEmpty()
{
    return H->getNext() == H;
}

NodoL* List::insertData(NodoL* n, int f, char c)
{
    NodoL* aux;

    aux = new NodoL();

    if(n == nullptr){
        n = H;
    }

    aux->setCaracter(c);
    aux->setFrecuencia(f);

    aux->setPrev(n);
    aux->setNext(n->getNext());
    n->getNext()->setPrev(aux);
    n->setNext(aux);

    return aux;
}

void List::deleteData(NodoL* n)
{
    n->getPrev()->setNext(n->getNext());
    n->getNext()->setPrev(n->getPrev());

    delete n;
}

NodoL* List::getFirst()
{
    if(isEmpty()){
        return nullptr;
    }

    return H->getNext();
}

NodoL* List::getLast()
{
    if (isEmpty()){
        return nullptr;
    }
    return H->getPrev();
}

NodoL* List::getNext(NodoL*p)
{
    if(!isValid(p) or p == H->getPrev()){
        return nullptr;
    }
    return p->getNext();
}

NodoL* List::getPrev(NodoL*p)
{
    if(!isValid(p) or p == H->getNext()){
        return nullptr;
    }

    return p->getPrev();
}

NodoL* List::findDataChar(char c)
{
    NodoL* aux = H->getNext();

    while (aux != H){
        if (aux->getCaracter() == c){
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

NodoL* List::findDataF(int i)
{
    NodoL* aux = H->getNext();

    while (aux != H){
        if (aux->getFrecuencia() == i){
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

void List::imprimirLista()
{
    NodoL* aux = H->getNext();

    while(aux != H){
        cout<<" ["<< aux->getCaracter()<<"-"<<aux->getFrecuencia()<<"] ";
        aux = aux->getNext();
    }
}

void List::clear()
{
    NodoL* aux;

    while(H->getNext() != H){
        aux = H->getNext();
        H->setNext(H->getNext()->getNext());
        delete aux;
    }
    H->setPrev(H);
}

void List::ordenarLista()
{
    NodoL* aux = H->getNext();
    NodoL* aux2 = H->getNext();
    while(aux != H){
        while(aux2->getNext() != H){

            if(aux2->getFrecuencia()> aux2->getNext()->getFrecuencia()){
                intercambio(aux2, aux2->getNext());
                aux = H;
                break;
            }

            else if(aux2->getFrecuencia() == aux2->getNext()->getFrecuencia()){

                if(aux2->getCaracter()> aux2->getNext()->getCaracter()){
                    intercambio(aux2, aux2->getNext());
                    aux = H;
                    break;
                }
            }
            aux2 = aux2->getNext();
        }
        aux = aux->getNext();
        aux2 = aux;
    }
}

void List::intercambio(NodoL* a, NodoL* b)
{
    int frec;
    char caracter;

    frec = b->getFrecuencia();
    caracter = b->getCaracter();

    b->setFrecuencia(a->getFrecuencia());
    b->setCaracter(a->getCaracter());

    a->setFrecuencia(frec);
    a->setCaracter(caracter);
}

void List::convertirToArbol()
{
    NodoL* aux = H->getNext();
    NodoL* aux2 = H->getNext()->getNext();

    while(aux2 != H){
        NodoL* pElem = deleteArbol(aux);
        NodoL* segElem = deleteArbol(aux2);

        int frecAcum = pElem->getFrecuencia() + segElem->getFrecuencia();
        tamanio = frecAcum;

        NodoL* n = findDataF(frecAcum);
        NodoL* nP;

        if(n == nullptr){
            nP = insertData(getLast(), frecAcum, '*');
        }

        else{
            while(n->getCaracter() == '*'){
                n = n->getNext();
            }
            n = n->getPrev();
            nP = insertData(n, frecAcum, '*');
        }

        insertArbol(nP, pElem);
        insertArbol(nP, segElem);

         aux = H->getNext();
         aux2 = H->getNext()->getNext();
    }
}

void List::insertArbol(NodoL*n, NodoL*e)
{
    if(n->getLeft() == nullptr){
        n->setLeft(e);
    }
    else{
        n->setRight(e);
    }
}

NodoL* List::deleteArbol(NodoL*p)
{
    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());
    return p;
}

void List::mostrarArbol(NodoL* root, int cont)
{
    if(root == nullptr){
        return;
    }

    else{
        mostrarArbol(root->getRight(), cont+1);

        for(int i = 0; i < cont; i++){
            cout<<"\t";
        }
        cout<<"("<<root->getCaracter()<<" "<<root->getFrecuencia()<< ")"<<endl;
        mostrarArbol(root->getLeft(), cont+1);
    }
}

void List::gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

//int auxX = 0;//Variable publica.
//auxX = 0;//se debe reestablecer a 0 cada vez que se desea llamar la función
//mostrarArbol(miArbol,0);



void List::mostrarArbol2(NodoL *a, int x, int y)
{
    if(a == nullptr){
        return;
    }

    gotoxy(x,y);
    cout<<"("<<a->getCaracter()<<" "<<a->getFrecuencia()<< ")"<<endl;
    x=x-4; //-3
    y=y+4; //+3
    mostrarArbol2(a->getLeft(),x,y);
    x=x+8; //+6
    mostrarArbol2(a->getRight(),x,y);
    y=y-4; //-3
}

void List::mostrarArbol3(NodoL *r, int x)
{
    if(r == nullptr){//Arbol vacio nada que mostrar
        return;
    }
    auxX += 5;//variable que permite posicionarse en el eje X

    mostrarArbol3(r -> getLeft(),x+2);//Se para hasta el nodo mas a la izquierda del árbol construye primero el subarbol izq porque sus valores en X son menores

    gotoxy(10+auxX-x , 15+x);//posiciona el nodo segun sus variables en X y en Y

    cout<<"("<<r->getCaracter()<<" "<<r->getFrecuencia()<< ")"<<endl<<endl;

    mostrarArbol3(r -> getRight(),x+2);
}


void List::diccionario(NodoL* root, int i)
{
    if(root == nullptr)
    {
        if(codigo.length() != 0)
        codigo.pop_back();
        return;
    }

    else
    {
        if(root->getCaracter() != '*')
        {
            cout << "Caract: " << root->getCaracter() << "| Cod: "  << codigo << endl;

            v.push_back(root->getCaracter());
            v2.push_back(codigo);
            i++;
        }

        codigo = codigo + '0';
        diccionario(root->getLeft(),i);
        codigo = codigo + '1';
        diccionario(root->getRight(),i);

    }
    if(codigo.length() != 0){
        codigo.pop_back();
    }
}


//void List::imprimirDiccionario()
//{
//    int j = 0;
//    int i = getHojas(getFirst(),j);
//    int k = 0;

//    while(k < i)
//    {
//        cout << "Caracter: " << myChar[k] << " Valor:" << myString[k] << endl;
//        k++;
//    }
//}

int List::getHojas(NodoL* root,int &i)
{
    if(root == nullptr){
        return i;
    }
    else{
        if(root->getCaracter() != '*'){
            i++;
        }
        getHojas(root->getLeft(), i);
        getHojas(root->getRight(), i);
    }
}

void List::transformarConDiccionario(string s)
{
    int h = 0;
    hojas = getHojas(getFirst(), h);

    for (size_t j = 0; j < s.length(); ++j) {
        for (size_t i = 0; i < v.size(); ++i) {

            if (s[j] == v[i]) {

//                cout<<s[j]<<"-"<<v[i]<<"-"<<v2[i]<<endl;
                binario+=v2[i];
                break;
            }
        }
    }
    cout<<"\nTexto a Binario: "<<endl
        <<binario<<endl;
}

void List::empaquetar()
{
    string aux = getBinario();

    int size = aux.length();
    string aux2 = "0";

    int mod = size % 8;
    int cont =  8 - mod;

    for (int i = 0; i < cont; ++i) {
        aux+=aux2;
    }
//    cout<<"\nConcatenado: "<<endl
//       <<aux<<endl;
    conversionBinCar(aux);
}


void List::conversionBinCar(string bin)
{
    string byte;
//    string cifrado;
    char c;

    for (size_t i = 0; i < bin.length(); i = i+8) {

        byte = bin.substr(i,8);
        c  = bin_to_Decimal(byte);
        cifrado+= c;
    }
//    cout<<"\nTexto Cifrado: "<<cifrado<<endl;

    ofstream archivo("huffman.txt");

    if(!archivo.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        archivo<<cifrado<<endl;
        cout<<"\n\tTexto Guardado en Archivo"<<endl;
    }
}

int List::bin_to_Decimal(string byte)
{
    int conversion;
    long binario, p,c;

    binario = stoi(byte);
    c = 1;
    conversion = 0;
    while(binario>0){
        p = 0;
        p = c * (binario%10);
        conversion += p;
        c *= 2;
        binario /= 10;
    }
    return conversion;
}

void List::guardarDiccionario()
{
    fstream archivo("Diccionario.txt", ios::out);
    if (!archivo.is_open()) {
        cout<<"ERROR"<<endl;
    }
    else{
        char aux;
        string aux2;
        archivo<<tamanio<<endl;
        for (size_t i = 0; i < v.size(); ++i) {

            aux = v[i];
            aux2 = v2[i];

            archivo<<aux<<"|";
            archivo<<aux2<<"\n";
        }
    }
    cout<<"\n\tDiccionario Guardado"<<endl;
}

string List::getBinario() const
{
    return binario;
}

void List::setBinario(const string &value)
{
    binario = value;
}

void List::leerArchivo()
{
    ifstream archivo("huffman.txt");

    if(!archivo.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        string aux;
        string texto;

        while(!archivo.eof()){

            getline(archivo,aux);
            texto += aux;

            if (archivo.eof()) {
                break;
            }
        }
        cout<<"\n\tTexto Cifrado: "<<endl
            <<texto<<endl;

        string texto2 = "";
        int a;

        for (size_t i = 0; i < texto.length(); ++i) {

            a = texto[i];
            texto2 += decimal_to_Bin(a);
        }
        cout<<"A binario: "<<endl
            <<texto2<<endl;
        cargarDiccionario();
        compararDiccionario(texto2);
    }
}

string List::decimal_to_Bin(int dec)
{
    string bin;
    int i = 0;

    if (dec == 1) {
        return "00000001";
    }
    else if (dec == 0) {
        return "00000000";
    }

    if (dec < 0) {
        dec = dec + 256;
    }

    while (dec > 1) {
        if (dec % 2 == 0) {
            bin = "0" + bin;
        }
        else if (dec % 2 == 1) {
            bin = "1" + bin;
        }
        dec = dec / 2;
        if (dec == 1) {
            bin = "1" + bin;
        }
        i++;
    }
    for (i; i < 7; i++) {
        bin = "0" + bin;
    }
    return bin;
}

void List::cargarDiccionario()
{
    ifstream archivo("Diccionario.txt");
    if (!archivo.is_open()) {
        cout<<"ERROR"<<endl;
    }
    else{
        string aux;
        string aux2;

        getline(archivo,aux,'\n');

        newtam = atoi(aux.c_str());
        cout<<newtam<<endl;

        while (!archivo.eof()) {

            getline(archivo,aux,'|');

            for (size_t i = 0; i < aux.length(); ++i) {
                v.push_back(aux[i]);
            }

            getline(archivo,aux2,'\n');
            if (archivo.eof()) {
                break;
            }
            v2.push_back(aux2);
        }
    }
}

void List::compararDiccionario(string dato)
{
    string temp;
    string texto = "";
    int pos;

    for (size_t j = 0; j < dato.length(); ++j) {

        if (texto.length() == newtam) {
            break;
        }
        temp+=dato[j];

        pos = busqueda(temp);

        if (pos != -1) {
            texto+=v[pos];
            temp="";
        }
    }


    cout<<"\nTexto Descifrado: "<<endl
        <<texto<<endl;

    ofstream archivo("huffman.txt");

    if(!archivo.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        archivo<<texto<<endl;
        cout<<"\n   Texto Cifrado Guardado en Archivo"<<endl;
    }
}

int List::busqueda(string caract)
{
    for (size_t i = 0; i < v2.size(); ++i) {

        if (caract == v2[i]) {
            return i;
        }
    }
    return -1;
}

char List::getCaract() const
{
    return caract;
}

void List::setCaract(char value)
{
    caract = value;
}

