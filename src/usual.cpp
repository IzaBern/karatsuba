#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, m;
    string u, v;
    cin >> u >> v;

    n = u.length();
    m = v.length();
    vector<int> resultado(n+m,0);

    for(int i = n-1; i >= 0; i--){
        for(int j = m-1 ; j >= 0; j--){
            //seleciona os digitos, converte p/ int e multiplica
            int produto = (u[i] - '0') * (v[j] - '0');
            int soma = produto + resultado[i+j+1];

            resultado[i+j+1] = soma%10; //digito da unidade
            resultado[i+j] += soma/10; //digito da dezena
        }
    }
    
    cout << "Produto:" << endl;
    for(int a : resultado){
        cout << a;
    }
    cout << endl;
}