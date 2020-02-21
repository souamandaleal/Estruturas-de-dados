//Implementação de AVL com metódo no nó, by Amanda C. Leal
// Versão 1 - 2020/1 para avaliação suplementar

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

class NohAVL; //declaracao avancada

typedef std::string TChave; //chave da arvore
typedef float TValor; //valor da arvore

//Declaracoes das classes

class NohAVL{
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    private:
        NohAVL(TChave chave, const TValor& valor);
        ~NohAVL();
        NohAVL* ArrumarBalanceamento();
        void AtualizarAltura();
        void DesalocarFilhosRecursivo();
        int FatorBalanceamento();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; //folhas tem altura 1
};

class AVL{
    public:
        AVL();
        ~AVL();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
    private:
        NohAVL* mPtRaiz;
};

using namespace std;

//Classe NohAVL
NohAVL::NohAVL(TChave chave, const TValor& valor){
    mChave = chave;
    mValor = valor;
    mPtEsq = nullptr;
    mPtDir = nullptr;
    mPtPai = nullptr;
    mAltura = 1; //noh folha tem altura igual a 1
}

NohAVL::~NohAVL(){
    DesalocarFilhosRecursivo();
}

//Faz (as rotacoes e ajustes necessarios inclusive no noh pai.
//Atualiza a altura
//Retorna o noh que ficar na posicao dele apos os ajustes
NohAVL* NohAVL::ArrumarBalanceamento(){
    //Atualiza altura do noh que eu estou
    AtualizarAltura();
    //Calcular o fator de bal
    int fatorBal = FatorBalanceamento();

    if((fatorBal >= -1) and (fatorBal <= 1)){
        return this;
    } else{
        //1. Desbalanceado esq-esq
        if((fatorBal > 1) and (mPtEsq->FatorBalanceamento() >= 0)){
            return RotacionarDireita();
        }
        //2. Desbalanceado dir-dir
        if((fatorBal < -1) and (mPtDir->FatorBalanceamento() < 0)){
            return RotacionarEsquerda();
        }
        //3. Desbalanceado dir-esq
        if((fatorBal < -1) and (mPtDir->FatorBalanceamento() > 0)){
            mPtDir = mPtDir->RotacionarDireita();
            return RotacionarEsquerda();
        }
        //4. Desbalanceado esq-dir
        if((fatorBal > 1) and (mPtEsq->FatorBalanceamento() < 0)){
            mPtEsq = mPtEsq->RotacionarEsquerda();
            return RotacionarDireita();
        }
    }
    return this;
}

//Calcula e atualiza a altura de um noh
void NohAVL::AtualizarAltura(){
	int altArvEsq;
	int altArvDir;
	
	if(mPtEsq != nullptr){
		altArvEsq = mPtEsq->mAltura;
	} else{
		altArvEsq = 0;
	}
	
	if(mPtDir != nullptr){
		altArvDir = mPtDir->mAltura;
	} else{
		altArvDir = 0;
	}
	
	if(altArvEsq >= altArvDir){
		mAltura = altArvEsq + 1;
	} else{
		mAltura = altArvDir + 1;
	}
}


//Desalocar todos os descendentes
void NohAVL::DesalocarFilhosRecursivo(){
    if(mPtEsq != nullptr){
        mPtEsq->DesalocarFilhosRecursivo();
    }
    if(mPtDir != nullptr){
        mPtDir->DesalocarFilhosRecursivo();
    }
    delete mPtEsq;
    delete mPtDir;
}

//Calcula e retorna o fator de balanceamento do noh
int NohAVL::FatorBalanceamento(){
    int altArvoreEsq = 0;
    int altArvoreDir = 0;

    if(mPtEsq != nullptr){
        altArvoreEsq = mPtEsq->mAltura;
    } else{
		altArvoreEsq = 0;
	}
    if(mPtDir != nullptr){
        altArvoreDir = mPtDir->mAltura;
    } else{
		altArvoreDir = 0;
	}

    int fatorBal = altArvoreEsq - altArvoreDir;

    return fatorBal;
}

//Insere um noh numa subarvore
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh){
    if(ptNoh->mChave < mChave){
        if(mPtEsq == nullptr){
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        } else{
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    } else{
        if(mPtDir == nullptr){
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        } else{
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

//Rotaciona a subarvore a direita.
//Retorna a nova raiz da subarvore
NohAVL* NohAVL::RotacionarDireita(){
    //guarda a nova raiz da subarvore
    NohAVL* novaRaizSub = mPtEsq;
    mPtEsq = novaRaizSub->mPtDir;

    if(novaRaizSub->mPtDir != nullptr){
        novaRaizSub->mPtDir->mPtPai = this;
    }

    novaRaizSub->mPtPai = this->mPtPai;

    if(mPtPai != nullptr){
        if(mPtPai->mPtDir == this){
            mPtPai->mPtDir = novaRaizSub;
        } else {
            mPtPai->mPtEsq = novaRaizSub;
        }
    }
    //faz o noh que eu estou como filho direito da nova raiz
    this->mPtPai = novaRaizSub;
    novaRaizSub->mPtDir = this;

    //atualiza as alturas
    AtualizarAltura(); //primeiro do noh que eu estou
    novaRaizSub->AtualizarAltura(); //depois da nova raiz

    return novaRaizSub; //retorna a nova raiz da subarvore
}

//Rotaciona a subarvore a esqueda.
//Retorna a nova raiz da subarvore
NohAVL* NohAVL::RotacionarEsquerda(){
    //guarda a nova raiz da subarvore
    NohAVL* novaRaizSub = mPtDir;
    mPtDir = novaRaizSub->mPtEsq;

    if(novaRaizSub->mPtEsq != nullptr){
        novaRaizSub->mPtEsq->mPtPai = this;
    }
    novaRaizSub->mPtPai = mPtPai;

    if(mPtPai != nullptr){
        if(mPtPai->mPtDir == this){
            mPtPai->mPtDir = novaRaizSub;
        } else{
            mPtPai->mPtEsq = novaRaizSub;
        }
    }
    novaRaizSub->mPtEsq = this;
    this->mPtPai = novaRaizSub;

    //Atualiza as alturas
    AtualizarAltura();
    novaRaizSub->AtualizarAltura();

    return novaRaizSub;
}

//Substitui um dos filhos por um novo noh
void NohAVL::TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo){
    if(mPtPai == ptAntigo){
        mPtPai = ptNovo;
    }
    else if(ptAntigo->mPtPai->mPtEsq == ptAntigo){
        ptAntigo->mPtPai->mPtEsq = ptNovo;
    } else{
        ptAntigo->mPtPai->mPtDir = ptNovo;
    }

    if(ptNovo != nullptr){
        ptNovo->mPtPai = ptAntigo->mPtPai;
    }
}

// Escreve o conteúdo de um nó no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

//Clase AVL
AVL::AVL(){
    mPtRaiz = nullptr;
}

AVL::~AVL(){
    mPtRaiz->DesalocarFilhosRecursivo();
    delete mPtRaiz;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

//Insere um par chave/valor na arvore
void AVL::Inserir(TChave chave, const TValor& valor){
    NohAVL* novo = new NohAVL(chave, valor);

    if(mPtRaiz == nullptr){
        mPtRaiz = novo;
    } else{
        mPtRaiz = mPtRaiz->InserirRecursivo(novo);
    }
}

int main(){
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;

    do{
        cin >> opcao;
        switch (opcao){
            case 'i': //inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave,valor);
                break;
            case 'e': //escrever nos nivel a nivel
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': //finalizar o programa
                break;
            default:
                cerr << "Opcao invalida" << endl;
        }
    } while(opcao != 'f');

    return 0;
}

