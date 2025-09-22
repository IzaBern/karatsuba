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

int main(){
    int n, m;
    string u, v;
    cin >> u >> v;

    n = u.length();
    m = v.length();
    vector<int> resultado(n+m,0);
    produto(u, v, n-1, m-1, resultado);
    
    for(int a : resultado){
        cout << a;
    }
    cout << endl;
}