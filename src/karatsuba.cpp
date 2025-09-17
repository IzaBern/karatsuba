#include <bits/stdc++.h>
using namespace std;

string soma(string a, string b){
    string result;
    int i, j, aux = 0;
    i = a.length()-1;
    j = b.length()-1;

    while(i >= 0 || j >= 0 || aux){
        int soma = aux;
        if(i >= 0) soma += a[i--] - '0';
        if(j >= 0) soma += b[j--] - '0';
        result.push_back(soma%10 + '0');
        aux = soma/10;
    }
    reverse(result.begin(), result.end());
    return result;
}
string subtracao(string a, string b){
    string result;
    int i, j, aux = 0;
    i = a.length()-1;
    j = b.length()-1;

    while(i >= 0){
        int sub = (a[i] - '0') - aux;
        if(j >=0) sub -= b[j] - '0'; 
        if(sub < 0){
            sub += 10;
            aux = 1;
        }else{
            aux = 0;
        }
        result.push_back(sub + '0');
        i--;
        j--;
    }
    while (result.length() > 1 && result.back() == '0')
        result.pop_back(); //retira os zeros à esquerda
    reverse(result.begin(), result.end());
    return result;
}

string karatsuba(string u, string v, int n){
    if(n<=3){ //se for pequeno, evita a recursão
        int produto = stoi(u) * stoi(v);
        return to_string(produto);
    }else{
        int k = ceil(n/2);
        //digitos + significativos de u (/10^k)
        string a = u.substr(0, u.length() - k);
        //digitos - significativos de u (mod 10^k)
        string b = u.substr(u.length() - k);
        //digitos + significativos de v
        string c = v.substr(0, v.length() - k);
        //digitos + significativos de v
        string d = v.substr(v.length() - k);
        
        string ac = karatsuba(a,c,k);
        string bd = karatsuba(b,d,k);
        string y = karatsuba(soma(a,b), soma(c,d), k+1);
        // (y − ac − bd)
        string mid = subtracao(subtracao(y,ac),bd);
        // ac*10^(2k)
        ac = ac + string(2*k, '0');
        // mid*10^k
        mid = mid + string(k, '0');
        //x = ac*10^(2k) + mid*10k + bd
        return soma(soma(ac,mid),bd);
    }
}

int main(){
    string u, v;
    cin >> u >> v;
    int n = max(u.length(), v.length());
    string resultado = karatsuba(u,v,n);
    cout << resultado;
}