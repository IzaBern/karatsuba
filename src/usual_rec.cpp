#include <iostream>
#include <vector>
using namespace std;

//laço for do 'j'
void produto_rec(string u, string v, int i, int j, vector<int> &resultado){
    if(j<0)
        return;
    int prod = (u[i] - '0') * (v[j] - '0');
    int soma = prod + resultado[i+j+1];
    resultado[i+j+1] = soma%10; //digito da unidade
    resultado[i+j] += soma/10; //digito da dezena
    
    produto_rec(u, v, i, j-1, resultado);
}
//laço for do 'i'
void produto(string u, string v, int i, int j, vector<int> &resultado){
    if(i<0)
        return;
    produto_rec(u, v, i, j, resultado);
    produto(u, v, i-1, j, resultado); 
}
void normaliza(vector<int> &res, int k) {
    if (k < 0) return;
    if (res[k] >= 10) {
        int carry = res[k] / 10;
        res[k] %= 10;
        if (k > 0) res[k - 1] += carry;
    }
    normaliza(res, k - 1);
}

int main(){
    int n, m;
    string u, v;
    cin >> u >> v;

    n = u.length();
    m = v.length();
    vector<int> resultado(n+m,0);
    produto(u, v, n-1, m-1, resultado);
    normaliza(resultado, n+m-1);
    
    //remove zeros à esquerda
    int indice = 0;
    while (indice < resultado[n+m-1] && resultado[indice] == 0)
        indice++;
    for (int i = indice; i < resultado.size(); i++)
        cout << (int)resultado[i];
    cout << endl;
}