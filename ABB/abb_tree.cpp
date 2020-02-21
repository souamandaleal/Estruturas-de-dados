#include <iostream>

using namespace std;

typedef int Dado;

class Noh{
friend class ABB;
    public:
        Noh(Dado dado);
        ~Noh();
        void Inserir(Noh* novo);
        int ContarNivel();
    private:
        Dado mDado;
        Noh* mPai;
        Noh* mEsq;
        Noh* mDir;
};
Noh::Noh(Dado dado){
    mDado = dado;
    mPai = nullptr;
    mEsq = nullptr;
    mDir = nullptr;
}

Noh::~Noh(){
    if(mEsq != nullptr){
        delete mEsq;
    }
    if(mDir != nullptr){
        delete mDir;
    }
}

void Noh::Inserir(Noh* novo){
    if (novo->mDado < mDado){
        if(mEsq == nullptr){
            mEsq = novo;
            novo->mPai = this;
        } else {
            mEsq->Inserir(novo);
        }
    } else{
        if(mDir == nullptr){
            mDir = novo;
            novo->mPai = this;
        } else{
            mDir->Inserir(novo);
        }
    }
}

int Noh::ContarNivel(){
    if(mPai == nullptr){ //estou na raiz
        return 0;
    } else{
        return 1 + mPai->ContarNivel();
    }
}

class ABB{
    public:
        ABB();
        ~ABB();
        void Inserir(Dado dado);
        void InserirRecursivo(Dado dado);
        void DestruirNohRecursivamente(Noh* noh);
        Noh* BuscarNoh(Dado dado);
        void GetAltura();
        int ContarFolhas();
        void ImprimeEmOrdem();
        void ImprimeEmPreOrdem();
        void ImprimeEmPosOrdem();
        int ContarNohs();
        int Minimo();
        int Maximo();
    private:
        int ContarFolhasAux(Noh* noh);
        int ContarNohsAux(Noh* noh);
        int GetAlturaAux(Noh* atual);
        void ImprimeEmOrdemAux(Noh* noh);
        void ImprimeEmPreOrdemAux(Noh* noh);
        void ImprimeEmPosOrdemAux(Noh* noh);
        Noh* MinimoAux(Noh* umNoh);
        Noh* MaximoAux(Noh* umNoh);
        Noh* mRaiz;
        int mAltura;
};

ABB::ABB(){
    mRaiz = nullptr;
    mAltura = 0;
}

ABB::~ABB(){
    DestruirNohRecursivamente(mRaiz);
    delete mRaiz;
}

void ABB::Inserir(Dado dado){
    Noh* novoNoh = new Noh(dado);

    if(mRaiz == nullptr){
        mRaiz = novoNoh;
    } else{
        Noh* percorredor = mRaiz;
        bool inserido =  false;

        while(inserido == false){
            if (percorredor->mDado > dado){
                if (percorredor->mEsq == nullptr){
                    percorredor->mEsq = novoNoh;
                    inserido = true;
                } else{
                    percorredor = percorredor->mEsq;
                }
            } else{
                if(percorredor->mDir == nullptr){
                    percorredor->mDir = novoNoh;
                    inserido = true;
                } else{
                    percorredor = percorredor->mDir;
                }
            }
        }
        novoNoh->mPai = percorredor;
    }
}

void ABB::InserirRecursivo(Dado dado){
    Noh* novoNoh = new Noh(dado);

    if(mRaiz == nullptr){
        mRaiz = novoNoh;
    } else{
        mRaiz->Inserir(novoNoh);
    }
}
void ABB:: DestruirNohRecursivamente(Noh* noh){
    if(noh != nullptr){
        DestruirNohRecursivamente(noh->mEsq);
        DestruirNohRecursivamente(noh->mDir);
        delete noh;
    }
}


Noh* ABB::BuscarNoh(Dado dado){
    if(mRaiz == nullptr){
        return nullptr;
    } else{
        Noh* percorredor = mRaiz;

        while(percorredor != nullptr){
            if(percorredor->mDado == dado){
                return percorredor;
            }
            else if(percorredor->mDado > dado){
                percorredor = percorredor->mEsq;
            } else{
                percorredor = percorredor->mDir;
            }
        }
        
        return nullptr;
    }
}

void ABB::GetAltura(){ //QUESTAO 52
    mAltura = GetAlturaAux(mRaiz);
}

int ABB::GetAlturaAux(Noh* atual){
    if(atual == nullptr){
        return 0;
    }

    int altEsq = GetAlturaAux(atual->mEsq);
    int altDir = GetAlturaAux(atual->mDir);

    if(altEsq > altDir){
        return 1 + altEsq;
    } else{
        return 1 + altDir;
    }
}

int ABB::ContarFolhas(){ //QUESTAO 54
    return ContarFolhasAux(mRaiz);
}

int ABB::ContarFolhasAux(Noh* noh){
    if(noh == nullptr){
        return 0;
    }

    if((noh->mEsq == nullptr) and (noh->mDir == nullptr)){
        return 1;
    } else{
        return ContarFolhasAux(noh->mEsq) + ContarFolhasAux(noh->mDir);
    }
}

void ABB::ImprimeEmOrdem(){
    ImprimeEmOrdemAux(mRaiz);
}

void ABB::ImprimeEmOrdemAux(Noh* noh){
    if(noh != nullptr){
        ImprimeEmOrdemAux(noh->mEsq);
        cout << noh->mDado << " ";
        ImprimeEmOrdemAux(noh->mDir);
    }
}

void ABB::ImprimeEmPreOrdem(){
    ImprimeEmPreOrdemAux(mRaiz);
}

void ABB::ImprimeEmPreOrdemAux(Noh* noh){
    if(noh != nullptr){
        cout << noh->mDado << " ";
        ImprimeEmPreOrdemAux(noh->mEsq);
        ImprimeEmPreOrdemAux(noh->mDir);
    }
}

void ABB::ImprimeEmPosOrdem(){
    ImprimeEmPosOrdemAux(mRaiz);
}

void ABB::ImprimeEmPosOrdemAux(Noh* noh){
    if(noh != nullptr){
        ImprimeEmPosOrdemAux(noh->mEsq);
        ImprimeEmPosOrdemAux(noh->mDir);
        cout << noh->mDado << " ";
    }
}

int ABB::ContarNohs(){ //QUESTAO 53
    return ContarNohsAux(mRaiz);
}

int ABB::ContarNohsAux(Noh* noh){
    if(noh == nullptr){
        return 0;
    }
    return ContarNohsAux(noh->mEsq) + ContarNohsAux(noh->mDir);
}

int ABB::Minimo(){
    if(mRaiz == nullptr){
        cerr << "Arvore vazia!" << endl;
        return 0;
    } else{
        Noh* minimo = MinimoAux(mRaiz);
        return minimo->mDado;
    }
}

Noh* ABB::MinimoAux(Noh* umNoh){
    Noh* aux = umNoh;
    while(aux->mEsq != nullptr){
        aux = aux->mEsq;
    }
    return aux;
}

int ABB::Maximo(){
    if(mRaiz == nullptr){
        cerr << "Arvore vazia!" << endl;
        return 0;
    } else{
        Noh* maximo = MaximoAux(mRaiz);
        return maximo->mDado;
    } 
}

Noh* ABB::MaximoAux(Noh* umNoh){
    Noh* percorredor = umNoh;
    
    while(percorredor->mDir != nullptr){
        percorredor = percorredor->mDir;
    }
    return percorredor;
}

int main(){

    ABB abb;

    abb.Inserir(50);

    return 0;
}
