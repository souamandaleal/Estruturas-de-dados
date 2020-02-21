#include <iostream>

using namespace std;

typedef int Dado;

class Noh{
friend class Fila;
    public:
        Noh(Dado);
    private:
        Dado mDado;
        Noh* mPtProximo;
};

class Fila{
    public:
        Fila();
        ~Fila();
        void Enfileirar(Dado dado);
        Dado Espiar();
        Dado Desenfileirar();
    private:
        Noh* mPtInicio;
        Noh* mPtFim;
};

Noh::Noh(Dado dado){
    mDado = dado;
    mPtProximo = nullptr;  
}

Fila::Fila(){
    mPtInicio = nullptr;
    mPtFim = nullptr;
}

Fila::~Fila(){
    while(mPtInicio != nullptr){
        Desenfileirar();
    }
}

void Fila::Enfileirar(Dado dado){
    Noh* novoNoh = new Noh(dado);

    if(mPtInicio == nullptr){
        mPtInicio = novoNoh;
        mPtFim = novoNoh;
    } else{
        mPtFim->mPtProximo = novoNoh;
        mPtFim = novoNoh;
    }
}

Dado Fila::Espiar(){
    if(mPtInicio == nullptr){
        cerr << "Fila vazia!" << endl;
        return -1;
    }else {
        return mPtInicio->mDado;
    }
}

Dado Fila::Desenfileirar(){
    if(mPtInicio == nullptr){
        cerr << "Fila vazia!" << endl;
        return -1;
    } else{
        Dado retorno = mPtInicio->mDado;
        Noh* novoInicio = mPtInicio->mPtProximo;
        delete [] mPtInicio;
        mPtInicio = novoInicio;
        return retorno;
    }
}

int main(){

    Fila minhaFila;

    minhaFila.Enfileirar(10);
    minhaFila.Enfileirar(9);
    minhaFila.Enfileirar(8);
    minhaFila.Enfileirar(7);
    minhaFila.Enfileirar(6);
    minhaFila.Enfileirar(5);
    minhaFila.Enfileirar(4);
    minhaFila.Enfileirar(3);
    minhaFila.Enfileirar(2);
    minhaFila.Enfileirar(1);
    minhaFila.Desenfileirar();
    minhaFila.Desenfileirar();
    cout << minhaFila.Espiar() << endl;


    return 0;
}
