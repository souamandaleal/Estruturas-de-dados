#include <iostream>

using namespace std;

typedef int Dado;

class Noh{
friend class Pilha;
    public:
        Noh(Dado dado);
    private:
        Dado mDado;
        Noh* mPtProximo;
};

Noh::Noh(Dado dado){
    mDado = dado;
    mPtProximo = nullptr;
}

class Pilha{
    public:
        Pilha();
        ~Pilha();
        void Empilha(Dado dado);
        Dado Desempilha();
        Dado Espia();
    private:
        Noh* topo;
        int mTamanho;
};

Pilha::Pilha(){
    topo = nullptr;
    mTamanho = 0;
}

Pilha::~Pilha(){
    while(topo != nullptr){
        Desempilha();
    }
}

void Pilha::Empilha(Dado dado){
    Noh* novoNoh = new Noh(dado);

    if(topo == nullptr){
        topo = novoNoh;
    } else {
        topo->mPtProximo = topo;
        topo = novoNoh;
    }
    mTamanho++;
}

Dado Pilha::Desempilha(){
    if(topo == nullptr){
        cerr << "Pilha vazia!" << endl;
        return -1;
    } else {
        Dado retorno = topo->mDado;
        Noh* novo = topo->mPtProximo;
        delete topo;
        topo = novo;
        mTamanho--;
        return retorno;
    }
}

Dado Pilha::Espia(){
    if(topo == nullptr){
        cerr << "Pilha vazia!" << endl;
        return -1;
    } else {
        return topo->mDado;
    }
}

int main(){

    Pilha minhaPilha;

    minhaPilha.Empilha(10);
    minhaPilha.Empilha(9);
    minhaPilha.Empilha(8);
    minhaPilha.Empilha(7);

    //minhaPilha.Desempilha();
    minhaPilha.Desempilha();

   cout <<  minhaPilha.Espia() << endl;
}
