#include <iostream>

using namespace std;

//constantes para verificacao 
const int MAXITENS = 3;
const int MINITENS = 1;
const int MAXFILHOS = 4;

//posicao do elemento do meio (o que sobe para pag pai em caso de estouro)
const int MEIO = 1;
const int METADE = 1;

typedef float Dado;

class Noh{
friend class Arvore234;
    private:   
        bool folha; //para saber se um noh eh folha
        int num; //numero de chaves armazendas no noh
        Dado itens[MAXITENS];
        Noh* filhos[MAXFILHOS];
        Noh* pai;
    public:
        Noh();
        ~Noh();
};

Noh::Noh(){
    num = 0; //numero de chaves
    folha = false;
    for(int i = 0; i < MAXFILHOS;i++){
        filhos[i] = NULL; 
    }
}

Noh::~Noh(){
    for(int i = 0; i < num+1; i++){
        delete filhos[i];
    }
}

class Arvore234{
    private:
         Noh* raiz;
         void percorreEmOrdemAux(Noh* atual, int nivel);
         Dado buscaAux(Noh* umNoh, Dado umItem);
    public:
        Arvore234() {raiz = nullptr;}
        ~Arvore234() {delete raiz;}
        //códigos não implementado, sua tarefa é implementá-lo!
        void insere(Dado umItem);
        Noh* insereAux(Noh* umNoh, Dado umItem, Dado& promovido);
        void insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem);
        Noh* divideNoh(Noh* umNoh, Dado& promovido);
        void insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novo, Dado& promovido);
        Dado minimo();
        Dado minimoAux(Noh* aux);
        Dado maximo();
        void buscar(Dado umItem);
        //percorrimento
        void percorrerEmOrdem();
}; 

void Arvore234::insere(Dado umItem){
    if(raiz == nullptr){
        raiz = new Noh();
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->num = 1;
    } else {
        Dado promovido = 0;
        Noh* novo = insereAux(raiz,umItem,promovido);
        if (novo != nullptr){
            Noh* antiga = raiz;
            raiz = new Noh();
            raiz->itens[0] = promovido;
            raiz->num = 1;
            raiz->filhos[0] = antiga;
            raiz->filhos[1] = novo;
        }
    }
}

Noh* Arvore234::insereAux(Noh* umNoh, Dado umItem, Dado& promovido){
    if (umNoh->folha){
        if (umNoh->num < MAXITENS){
            insereEmNohFolhaNaoCheio(umNoh,umItem);
            promovido = 0;
            return NULL;
        } else { //noh esta cheio
            Noh* novo = divideNoh(umNoh, promovido);
            if (umItem <= umNoh->itens[MEIO]){
                insereEmNohFolhaNaoCheio(umNoh, umItem);
            } else {
                insereEmNohFolhaNaoCheio(novo,umItem);
            }
            return novo;
        }
    } else { //nao sou folha 
        int i = umNoh->num - 1;
        while ((i >= 0) and (umNoh->itens[i] > umItem)){
            i--;
        }
        Noh* nohAux = insereAux(umNoh->filhos[i+1], umItem, promovido);
        if(nohAux != nullptr){
            if(umNoh->num < MAXITENS){
                insereEmNohIntermediarioNaoCheio(umNoh, nohAux, promovido);
                return NULL;
            } else { //noh esta cheio
                Dado provFilho = promovido;
                Noh* novo = divideNoh(umNoh, promovido);
                if(umItem <= umNoh->itens[MEIO]){
                    insereEmNohIntermediarioNaoCheio(umNoh, nohAux, provFilho);
                } else {
                    insereEmNohIntermediarioNaoCheio(novo, nohAux, provFilho);
                }
                return novo;
            }

        }
        return NULL;
    }
}

void Arvore234::insereEmNohFolhaNaoCheio(Noh* umNoh, Dado umItem){
    int pos = umNoh->num - 1;
    while (pos>=0 and umNoh->itens[pos] > umItem){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    umNoh->itens[pos+1] = umItem;
    umNoh->num++;
}

Noh* Arvore234::divideNoh(Noh* umNoh, Dado& promovido){
    promovido = umNoh->itens[MEIO];
    Noh* novo = new Noh();
    novo->folha = umNoh->folha;
    novo->itens[0] = umNoh->itens[MEIO+1];
    novo->num = METADE;
    umNoh->num = METADE;
    if(not(umNoh->folha)){
        for (int i = 0; i <= MEIO+1; i++){
            novo->filhos[i] = umNoh->filhos[MEIO+1+i];
        }
    }
    return novo;
}

void Arvore234::insereEmNohIntermediarioNaoCheio(Noh* umNoh, Noh* novo, Dado& promovido){
    int pos = umNoh->num-1;
    while (pos >= 0 and umNoh->itens[pos] > promovido){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    umNoh->itens[pos+1] = promovido;
    umNoh->filhos[pos+2] = novo;
    umNoh->num++;
}

Dado Arvore234::minimo(){
    Noh* aux = raiz;
    Noh* anterior =  nullptr;
    while(aux != nullptr){
        anterior = aux;
        aux = aux->filhos[0];
    }
    Dado menor = anterior->itens[0];
    return menor;
}

Dado Arvore234::maximo(){
    Noh* atual = raiz;
    if (raiz->folha){
        return atual->itens[atual->num-1];
    }
    while (!(atual->folha)){
        atual = atual->filhos[atual->num];
    }
    return atual->itens[atual->num-1];
}

void Arvore234::percorrerEmOrdem(){
    percorreEmOrdemAux(raiz,0);
    cout << endl;
}

void Arvore234::percorreEmOrdemAux(Noh* umNoh, int nivel){
    int i;
    for (i = 0; i < umNoh->num; i++){
        //se noh nao eh folha, imprima os dados do filho i
        //antes de imprimir o item i
        if (not umNoh->folha){
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
        }
        cout << umNoh->itens[i] << '/' << nivel << ' ';
    }
    //imprima os dados do ultimo filho
    if(not umNoh->folha){
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
    }
}

void Arvore234::buscar(Dado umItem){
    if (raiz == nullptr){
        cout << "Arvore Vazia!";
    } else {
        Dado posItemBuscado = buscaAux(raiz, umItem);
        cout << "A posicao do item buscado eh: " << posItemBuscado << endl;
    }
}

Dado Arvore234::buscaAux(Noh* umNoh, Dado umItem){
    int i = 0;
    Noh* aux = umNoh;

    while((i < aux->num) and (aux->itens[i] <= umItem)){ //para andar dentro do vetor de chaves
        i++;
    } 
    i--;
    if (aux->itens[i] == umItem){
        return i;
    } else{
        if (aux->folha){
            return 0;
        } else{
            return buscaAux(aux->filhos[i+1], umItem);
        }
    }
}

int main() {
    Arvore234* B = new Arvore234;

    char opcao;
    float valor;

    do{
        cin >> opcao;
        if(opcao == 'i'){
            cin >> valor;
            B->insere(valor);
        }
        if(opcao == 'l'){
            cout << B->minimo() << endl;
        }
        if(opcao == 'h'){
            cout << B->maximo() << endl;
        }
        if(opcao == 'b'){
            cin >> valor;
            B->buscar(valor);
        }
        else if (opcao == 'e'){
            B->percorrerEmOrdem();
        }
    } while (opcao != 'q');

    delete B;

    return 0;
}

/*
 * i 40 
 * i 12
 * i 68
 * i 36
 * i 38
 * i 60
 * i 48
 * i 55
 * i 50
 * i 62
 * i 65
 * i 22
 * i 90
*/
