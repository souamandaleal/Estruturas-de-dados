#include <iostream>
using namespace std; 

class MinHeap{
    private:
        int GetPai(int filho);
        int GetEsq(int pai);
        int GetDir(int pai);
        void CorrigeDescendo(int pos);
        void CorrigeSubindo(int pos);
        int mCapacidade;
        int mTamanho;
        int* vetor;
    public:
        MinHeap(int cap);
        MinHeap(int outroVet[], int tam); //heapfy
        ~MinHeap();
        int RetiraRaiz();
        void Inserir(int valor);
        void Imprimir();
};

MinHeap::MinHeap(int cap){
    mCapacidade = cap;
    mTamanho = 0;
    vetor = new int[mCapacidade];
}

MinHeap::MinHeap(int outroVet[], int tam){ //heapfy
    mCapacidade = tam + 5; //nova capacidade
    mTamanho = tam; //novo tamanho

    //aloca nova capacidade para o vetor
    vetor = new int[mCapacidade];

    //passo tudo que tem no outro vetor para o vetor atual
    for(int i = 0; i < mTamanho; i++){
        vetor[i] = outroVet[i];
    }

    for(int i = mCapacidade/2; i >= 0; i--){
        CorrigeDescendo(i);
    }
}

MinHeap::~MinHeap(){
    delete [] vetor;
}

int MinHeap::GetPai(int filho){
    return (filho-1)/2;
}

int MinHeap::GetEsq(int pai){
    return (2*pai) + 1;
}

int MinHeap::GetDir(int pai){
    return (2*pai) + 2;
}

void MinHeap::CorrigeDescendo(int pos){
    int filhoEsq = GetEsq(pos);
    int filhoDir = GetDir(pos);
    int menor = pos;

    if((filhoEsq <= mTamanho) and (vetor[filhoEsq] <  vetor[menor])){
        menor = filhoEsq;
    }
    if((filhoEsq <= mTamanho) and (vetor[filhoDir] < vetor[menor])){
        menor = filhoDir;
    }

    if(menor != pos){
        swap(vetor[menor],vetor[pos]);
        CorrigeDescendo(menor);
    }
}

int MinHeap::RetiraRaiz(){
    if(mTamanho < 1){
        return -1;
    }

    int antigaRaiz = vetor[0];
    swap(vetor[0], vetor[mTamanho-1]);
    mTamanho--;

    CorrigeDescendo(0);

    return antigaRaiz;
}

void MinHeap::CorrigeSubindo(int pos){
    int pai = GetPai(pos);

    if(pos != 0){ //se eu nao for a raiz
        if(vetor[pos] < vetor[pai]){
            swap(vetor[pos],vetor[pai]);
            CorrigeSubindo(pai);
        }
    }
}

void MinHeap::Inserir(int valor){
    if(mTamanho == mCapacidade){
        cerr << "Heap cheio" << endl;
    } else if(mTamanho == 0){
        vetor[0] = valor;
    } else{
        vetor[mTamanho] = valor;
        CorrigeSubindo(mTamanho);
    }
    mTamanho++;
}

void MinHeap::Imprimir(){
    if(mTamanho == 0){
        cerr << "Heap vazio" << endl;
    }

    for(int i = 0; i < mTamanho; i++){
        cout << vetor[i] << " ";
    }
    cout << endl;
}

int main(){
    int valor;
    int vetor[5];

    for(int i = 0; i <15; i++){
        cin >> valor;
        vetor[i] = valor;
    }

    MinHeap heap(vetor,15);
    heap.Imprimir();
    
    for (int i = 0; i < 5; i++){
        cin >> valor;
        heap.Inserir(valor);
    }
    
    heap.Imprimir();

    return 0;
}