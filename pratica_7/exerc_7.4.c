float produtoEscalar(int n, float A[], float B[]){
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += (A[i] * B[i]);
    }
    return soma;
}