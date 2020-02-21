#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <queue>

typedef std::string TValor;
typedef unsigned TChave;
enum Cor {PRETO, VERMELHO};

class Noh{
    friend class ArvoreRN;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    public:
		Noh(unsigned chave, TValor valor);
	private:
        Noh* Tio();
        void DesalocarRecursivo();
        TValor mValor;
        TChave mChave;
        Cor mCor;
        Noh* mEsq;
        Noh* mDir;
        Noh* mPai;
};

class ArvoreRN{
    public:
        ArvoreRN();
        ~ArvoreRN();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(unsigned chave, TValor valor);
    private:
        void ArrumarInsercao(Noh* umNoh);
        void RotacionarDireita(Noh* umNoh);
        void RotacionarEsquerda(Noh* umNoh);
        Noh* mRaiz;
};

using namespace std;

//===== Classe Noh=====
Noh::Noh(TChave chave, TValor valor)
    : mValor(valor), mChave(chave), mCor(VERMELHO), mEsq(nullptr), mDir(nullptr), mPai(nullptr){

}

//Desalocar as subarvores e depois a si proprio
void Noh::DesalocarRecursivo(){
    if(mEsq != nullptr) {
        mEsq->DesalocarRecursivo();
    }
    if(mDir != nullptr) {
        mDir->DesalocarRecursivo();
    }
    delete mEsq;
    delete mDir;
}

Noh* Noh::Tio(){
    if (mPai->mPai != nullptr){
        if(mPai->mPai->mEsq == mPai){
            if (mPai->mPai->mPai->mDir != nullptr){
                return mPai->mPai->mDir;
            } else{
                return nullptr;
            }
        } else{
            if (mPai->mPai->mEsq != nullptr){
                return mPai->mPai->mEsq;
            } else{
                return nullptr;
            }

        }
    }
    return nullptr;
}

//===== Classe ArvoreRN =====
ArvoreRN::ArvoreRN() : mRaiz(nullptr){
}

ArvoreRN::~ArvoreRN(){
    if(mRaiz != nullptr){
        mRaiz->DesalocarRecursivo();
        delete mRaiz;
    }
}

//insere uma chave/valor na Arvore
//chama ArrumarInsercao para corrigir eventuais problemas
void ArvoreRN::Inserir(unsigned chave, TValor valor){
    Noh* novoNoh = new Noh(chave, valor);

    if(mRaiz == nullptr){
        mRaiz = novoNoh;
        novoNoh->mCor = PRETO;
    } else{
        Noh* percorredor = mRaiz;
        bool inserido = false;

        while (inserido == false){
            if(percorredor->mChave > chave) {
                if(percorredor->mEsq == nullptr){
                    percorredor->mEsq = novoNoh;
                    inserido = true;
                } else {
                    percorredor = percorredor->mEsq;
                }
            } else {
                if(percorredor->mDir == nullptr){
                    percorredor->mDir = novoNoh;
                    inserido = true;
                } else {
                    percorredor = percorredor->mDir;
                }
            }
        }
        novoNoh->mPai = percorredor;
    }
    ArrumarInsercao(novoNoh);
}

//procedimento para manter balanceaamento apos a insercao
void ArvoreRN::ArrumarInsercao(Noh* umNoh){
    while ((umNoh != mRaiz) and (umNoh->mPai->mCor == VERMELHO)){
        Noh* tio = umNoh->Tio();

       //Caso 1 - Tio eh vermelho
       if(tio->mCor == VERMELHO){
		  tio->mCor = PRETO; //troca a cor do tio
          umNoh->mPai->mCor = PRETO; //troca a cor do pai
		  umNoh = umNoh->mPai->mPai; //atualiza umNoh com o avo para continuar o teste
		} else{
            //Caso 2 - Tio eh preto, eu sou filho esq do meu pai e meu pai eh filho esq do meu avo
            if((umNoh->mPai->mEsq == umNoh) and (umNoh->mPai->mPai->mEsq == umNoh->mPai)){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai->mPai);
            }
            //Caso 3 - Tio eh preto, eu sou filho dir do meu pai e meu pai eh filho dir do meu avo
            else if((umNoh->mPai->mDir == umNoh) and (umNoh->mPai->mPai->mDir == umNoh->mPai)){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai->mPai);
            }
            //Caso 4- Tio eh preto, eu sou filho dir do meu pai e meu pai eh filho esq do meu avo
            else if((umNoh->mPai->mDir == umNoh) and (umNoh->mPai->mPai->mEsq == umNoh->mPai)){
                umNoh->mCor = PRETO;
                Noh* avo = umNoh->mPai->mPai;
                avo->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai);
                RotacionarDireita(avo);
                umNoh = umNoh->mPai; //atualiza o noh para a verficacao no enquanto
            }
            //Caso 5 - Tio eh preto, eu sou filho esq do meu pai e meu pai eh filho dir do meu avo
            else {
                umNoh->mCor = PRETO;
                Noh* avo = umNoh->mPai->mPai;
                avo->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai);
                RotacionarEsquerda(avo);
                umNoh = umNoh->mPai;
            }
        }
    }
    mRaiz->mCor = PRETO;
}

//Rotacao Esquerda, muda a raiz se necessario
void ArvoreRN::RotacionarEsquerda(Noh* umNoh){
    //acha um filho a direita da subarvore
    Noh* novaRaizSubArv = umNoh->mDir;
    umNoh->mDir = novaRaizSubArv->mEsq;

    if(novaRaizSubArv->mEsq != nullptr){
        novaRaizSubArv->mEsq->mPai = umNoh;
    }

    novaRaizSubArv->mPai = umNoh->mPai;

    if(umNoh == mRaiz){
        mRaiz = novaRaizSubArv;
    }
    else if(umNoh == umNoh->mPai->mEsq){
        umNoh->mPai->mEsq = novaRaizSubArv;
    } else {
        umNoh->mPai->mDir = novaRaizSubArv;
    }
    novaRaizSubArv->mEsq = umNoh;
    umNoh->mPai = novaRaizSubArv;
}

//Rotacao Direita, muda a raiz se necessario
void ArvoreRN::RotacionarDireita(Noh* umNoh){
    //achar um filho a esquerda da subarvore
    Noh* novaRaizSub = umNoh->mEsq;
    umNoh->mEsq = novaRaizSub->mDir;

    if(novaRaizSub->mDir != nullptr){
        novaRaizSub->mDir->mPai = umNoh;
    }
    novaRaizSub->mPai = umNoh->mPai;

    if(umNoh == mRaiz){
        mRaiz = novaRaizSub;
    } 
    else if(umNoh->mPai->mEsq == umNoh){
        umNoh->mPai->mEsq = novaRaizSub;
    } else{
        umNoh->mPai->mDir = novaRaizSub;
    }
    novaRaizSub->mDir = umNoh;
    umNoh->mPai = novaRaizSub;
}

// Escreve o conteúdo da árvore nível a nível
void ArvoreRN::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    filhos.push(mRaiz);
    while (not filhos.empty()) {
        unsigned nroNohsNesteNivel = unsigned(filhos.size());
        for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
            Noh* ptNoh = filhos.front();
            filhos.pop();
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mEsq);
                filhos.push(ptNoh->mDir);
            }
        }
        cout << "\n";
    }
}

// Escreve um nó (ou NIL).
ostream& operator<<(ostream& saida, Noh* ptNoh) {
    static char vetLetrasCores[] = "PV";
    if (ptNoh == NULL)
        saida << "NIL";
    else
        saida << '[' << vetLetrasCores[ptNoh->mCor] << ':' << ptNoh->mChave << '/'
              << ptNoh->mValor << ']';
    return saida;
}

int main(){
    ArvoreRN arvore;
    char opcao;
    TChave chave;
    TValor valor;

    do{
        cin >> opcao;
        switch (opcao){
            case 'i': //inserir
                cin >> chave >> valor;
                arvore.Inserir(chave,valor);
                break;
            case 'e': //escrever nivel a nivel
                arvore.EscreverNivelANivel(cout);
                break;
            case 'f': //finalizar o programa
                //vai verificar depois
                break;
            default:
                cerr << "Opcao invalida" << endl;
        }
    } while(opcao != 'f');

    return 0;
}

