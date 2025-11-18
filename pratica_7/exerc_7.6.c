void mediaMovel(int n, float v[], int k, float m[]) {
    float media = 0;
    int tamanho = n - k + 1;
    for(int i = 0; i < tamanho; i++, k++) {
        for(int j = i; j < k; j++) {
            media += v[j]; 
        }
        m[i] = media / k;
        media = 0;     
    }
}

void mediaMovel(int n, float v[], int k, float m[]) {
    float media = 0;
    int janela = k;
    for(int i = 0; i < (n - k + 1); i++) {
        int j = i;
        printf("%.1f %d\n", v[i], 1);
        while(j < janela) {
            media += v[j];
            printf("%.1f %d\n", v[j], 2);
            printf("%.1f %d\n", media, 3);
            j++;
        }
        m[i] = media / k;
        media = 0;
        printf("%.1f %d\n", m[i], 4);
        janela++;
    }
}