//Tabela Hash com tratamento de colisão encadeada.
//by Amanda C Leal para avaliação suplementar de ED 2020

#include <iostream>
using namespace std;

typedef int Dado;

int FuncaoHash(int chave, int capacidade){
    return chave * 13 % capacidade;
}

class Noh{
friend class TabelaHash;
    public:
        Noh(int chave, Dado dado);
    private:
        int mChave;
        Dado mDado;
        Noh* mPtProximo;
};

Noh::Noh(int chave, Dado dado){
    mChave = chave;
    mDado = dado;
    mPtProximo = nullptr;
}

class TabelaHash{
    public:
        TabelaHash(int capacidade); //construtor
        ~TabelaHash(); //destrutor
        Dado Recuperar(int chave);
        void Inserir(int chave, Dado dado);
        void Alterar(int chave, Dado dado);
        Dado Remover(int chave);
        void Imprimir();
    private:
        Noh** tabela;
        int mCapacidade;
};

TabelaHash::TabelaHash(int capacidade){
    tabela = new Noh*[capacidade]; //crio vetor
    mCapacidade = capacidade;

    for(int i = 0; i < mCapacidade; i++){ //inicio o vetor com os valores null
        tabela[i] = NULL;
    }
}

TabelaHash::~TabelaHash(){
    Noh* anterior = tabela[0];
    Noh* atual = tabela[0];

    for(int i = 0; i < mCapacidade; i++){
        anterior = tabela[i]; //ando nas posicoes do vetor na vertical
        atual = tabela[i];

        while(atual != nullptr){ //ando nos nohs de cada posicao do vetor (horizontal)
            anterior = atual;
            atual = atual->mPtProximo;
            delete anterior;
        }
    }
    delete [] tabela; //deleto o vetor
}

Dado TabelaHash::Recuperar(int chave){
    int numeroHash = FuncaoHash(chave, mCapacidade);

    if(tabela[numeroHash] == NULL){ 
        return -1;
    } else{
        if(tabela[numeroHash]->mChave == chave){
            return tabela[numeroHash]->mDado;
        } else{
            Noh* percorredor = tabela[numeroHash]->mPtProximo;

            while(percorredor != nullptr){
                if(percorredor->mChave == chave){
                    return percorredor->mDado;
                } else{
                    percorredor = percorredor->mPtProximo;
                }
            }
            return -1;
        }
    }
}

void TabelaHash::Inserir(int chave, Dado dado){
    int numeroHash = FuncaoHash(chave,mCapacidade);
    Noh* novoNoh = new Noh(chave, dado);

    if(tabela[numeroHash] == NULL){
        tabela[numeroHash] = novoNoh;
    }
    else if(Recuperar(chave) != -1){
        cerr << "Chave ja existente" << endl;
    } else{
        Noh* percorredor = tabela[numeroHash];

        while(percorredor->mPtProximo != nullptr){
            percorredor = percorredor->mPtProximo;
        }
        percorredor->mPtProximo = novoNoh;
    }
}

void TabelaHash::Alterar(int chave, Dado dado){
    if(Recuperar(chave) == -1){
        cerr << "Chave nao existente" << endl;
    } else{
        int numeroHash = FuncaoHash(chave, mCapacidade);

        Noh* percorredor = tabela[numeroHash];

        while(percorredor->mChave != chave and percorredor != nullptr){
            percorredor = percorredor->mPtProximo;
        }
        percorredor->mDado = dado;
    }
}

Dado TabelaHash::Remover(int chave){
    if(Recuperar(chave) == -1){
        cerr << "Chave nao existente" << endl;
        return -1;
    } else{
        int numeroHash = FuncaoHash(chave, mCapacidade);

        if(tabela[numeroHash]->mChave == chave){
            Noh* proximo = tabela[numeroHash]->mPtProximo;
            int aux = tabela[numeroHash]->mDado;
            delete tabela[numeroHash];
            tabela[numeroHash] = proximo;
            return aux;
        } else{
            Noh* atual = tabela[numeroHash];
            Noh* anterior = tabela[numeroHash];

            while(atual->mChave != chave and atual != nullptr){
                anterior = atual;
                atual = atual->mPtProximo;
            }
            int aux = atual->mDado;
            anterior->mPtProximo = atual->mPtProximo;
            delete atual;
            return aux;
        }
    }
}

void TabelaHash::Imprimir(){
    for(int i = 0; i < mCapacidade; i++){
        Noh* percorredor = tabela[i];

        while(percorredor != nullptr){
            cout << percorredor->mDado << " ";
            percorredor = percorredor->mPtProximo;
        }
    }
    cout << endl;
    cout << "Capacidade: " << mCapacidade << endl;
}

int main(){

    TabelaHash minhaHash(10);

    minhaHash.Inserir(1, 22);
    minhaHash.Inserir(2, 33);
    minhaHash.Inserir(3, 44);
    
    minhaHash.Imprimir();
    
    minhaHash.Alterar(2, 55);
    minhaHash.Inserir(4, 66);
    minhaHash.Remover(3);
    
    minhaHash.Imprimir();
    
    return 0;
}
