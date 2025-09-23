#include <bits/stdc++.h>
using namespace std;


vector<int> leia_vetor() {
    string s;
    cin >> s;
    vector<int> a;
    for (int i=0; i<s.length(); i++) {
        a.push_back(s[i] - '0');
    }
    return a;
}


vector<int> soma(vector<int> &a, vector<int> &b){
    vector<int> resultado;
    int i, j, aux = 0;
    i = a.size()-1;
    j = b.size()-1;
    while(i >= 0 || j >= 0 || aux){
        int soma = aux;
        if(i >= 0) soma += a[i--];
        if(j >= 0) soma += b[j--];
        resultado.push_back(soma%10);
        aux = soma/10;
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}


vector<int> subtracao(vector<int> &a, vector<int> &b){
    vector<int> resultado;
    int i, j, aux = 0;
    i = a.size()-1;
    j = b.size()-1;


    while(i >= 0){
        int sub = a[i] - aux;
        if(j >=0) sub -= b[j];
        if(sub < 0){
            sub += 10;
            aux = 1;
        }else{
            aux = 0;
        }
        resultado.push_back(sub);
        i--;
        j--;
    }
    // Remove zeros à esquerda
    int x = resultado.size() - 1;          
    while (x > 0 && resultado[x] == 0) x--;
    resultado.resize(x + 1);
    reverse(resultado.begin(), resultado.end());              
    return resultado;
}


vector<int> produto_simples(vector<int> &u, vector<int> &v) {
    int n = u.size(), m = v.size();
    vector<int> resultado(n+m, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = m-1 ; j >= 0; j--){
            long long int produto = u[i] * v[j];
            long long int soma = produto + resultado[i+j+1];


            resultado[i+j+1] = soma%10; //digito da unidade
            resultado[i+j] += soma/10; //digito da dezena
        }
    }
    return resultado;
}


vector <int> karatsuba(vector <int> &u, vector <int> &v){
    int n = max(u.size(), v.size());
    if(n<=32){ //se for pequeno, evita a recursão
        return produto_simples(u,v);
    }else{
        int k = n / 2;
        //digitos + significativos de u (/10^k)
        vector<int> a(u.begin(), u.begin() + n - k);
        //digitos - significativos de u (mod 10^k)
        vector<int> b(u.begin() + n - k, u.end());
        //digitos + significativos de v
        vector<int> c(v.begin(), v.begin() + n - k);
        //digitos - significativos de v
        vector<int> d(v.begin() + n - k, v.end());


        vector<int> ac = karatsuba(a,c);
        vector<int> bd = karatsuba(b,d);
        a = soma(a,b);
        c = soma(c,d);
        vector<int> y = karatsuba(a, c);
       
        // (y−ac−bd)
        y = subtracao(y,ac);
        y = subtracao(y,bd);
        // ac*10^(2k)
        ac.insert(ac.end(), (2*k), 0);
        // (y−ac−bd)*10^k
        y.insert(y.end(), (k), 0);
        //x = ac*10^(2k) + (y−ac−bd)*10k + bd
        ac = soma(ac,y);
        return soma(ac,bd);
    }
}


int main(){
    vector <int> u = leia_vetor();
    vector <int> v = leia_vetor();


    vector <int> resultado = karatsuba(u,v);
    for(int x : resultado){
        cout << x;
    }
    cout << endl;
}