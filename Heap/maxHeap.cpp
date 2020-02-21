#include <iostream>
using namespace std;

class MaxHeap{
    private:
        int getPai(int filho);
        int getEsq(int pai);
        int getDir(int pai);
        void corrigeDescendo(int pos);
        void corrigeSubindo(int pos);
        int mCapacidade;
        int mTamanho;
        int* vetor;
    public:
        MaxHeap(int cap);
        MaxHeap(int outroVet[], int tam); //heapfy
        ~MaxHeap();
        int retiraRaiz();
        void inserir(int valor);
        void imprimir();
};

MaxHeap::MaxHeap(int cap){
    mCapacidade = cap;
    mTamanho = 0;
    vetor = new int[mCapacidade];
}

MaxHeap::MaxHeap(int outroVet[], int tam){ //heapfy
    mCapacidade = tam + 5; //nova capacidade
    mTamanho = tam; //novo tamanho

    //aloca nova capacidade para o vetor
    vetor = new int[mCapacidade]; 

    //passo tudo que tem no outro vetor para o vetor atual
    for(int i = 0; i < mTamanho; i++){
        vetor[i] = outroVet[i];
    }

    for(int i = mCapacidade/2; i >= 0; i--){
        corrigeDescendo(i);
    }
}

MaxHeap::~MaxHeap(){
    delete[] vetor;
}

int MaxHeap::getPai(int filho){
    return (filho-1)/2;
}

int MaxHeap::getEsq(int pai){
    return (2*pai) + 1;
}

int MaxHeap::getDir(int pai){
    return (2*pai) + 2;
}

void MaxHeap::corrigeDescendo(int pos){
    int filhoEsq = getEsq(pos);
    int filhoDir = getDir(pos);
    int maior = pos;

    if((filhoEsq <= mTamanho) and (vetor[filhoEsq] > vetor[maior])){
        maior = filhoEsq;
    }
    if((filhoDir <= mTamanho) and (vetor[filhoDir] > vetor[maior])){
        maior = filhoDir;
    }
    if(maior != pos){
        swap(vetor[maior], vetor[pos]);
        corrigeDescendo(maior);
    }
}

int MaxHeap::retiraRaiz(){
    if(mTamanho < 1){
        return -1;
    }

    int aux = vetor[0];
    swap(vetor[0], vetor[mTamanho-1]);
    mTamanho--;

    corrigeDescendo(0);

    return aux;
}

void MaxHeap::corrigeSubindo(int pos){
    int pai = getPai(pos);

    if(pos != 0){ //se eu nao for a raiz
        if(vetor[pos] > vetor[pai]){
            swap(vetor[pos], vetor[pai]);
            corrigeSubindo(pai);
        }
    }
}

void MaxHeap::inserir(int valor){
    if(mTamanho == mCapacidade){
        cerr << "Heap cheio" << endl;
    }
    else if(mTamanho == 0){
        vetor[0] = valor;
    } else{
        vetor[mTamanho] = valor;
        corrigeSubindo(mTamanho);
    }

    mTamanho++;
}

void MaxHeap::imprimir(){
    if(mTamanho == 0){
        cerr << "Heap vazio!" << endl;
    }

    for(int i = 0; i < mTamanho; i++){
        cout << vetor[i] << " ";
    }

    cout << endl;
}

int main(){
    int valor;
    int vetor[15];

    for(int i = 0; i < 15; i++){
        cin >> valor;
        vetor[i] = valor;
    }

    Max heap(vetor,15);
    heap.imprimir();

    for(int i = 0; i < 5; i++){
        cin >> valor;
        heap.inserir(valor);
    }

    heap.imprimir();

    return 0;
}