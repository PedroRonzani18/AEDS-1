#include <iostream>
#include <deque>
#include <string.h>

using namespace std;

#define print_v(a)     for(auto x : a) cout << x << " "; cout << endl
#define print2(a,x,y)  for(int i = x; i < y; i++) cout<< a[i]<< " "; cout << endl

#define rf(i,e,s) 	   for(int i=e-1;i>=s;i--)


#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args> void __f (const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr (names + 1, ',');
	cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

deque<int> multiplicador_em_valores(int n) { // Retorna o multiplicador dentro de um deque
    deque<int> retorno;

    while(n > 0) {
        retorno.push_front(n % 10);
        n /= 10;
    }

    return retorno;
}

void adiciona_zeros(deque<int>& d, const size_t& num) {
    for(size_t o=0; o<num; o++, d.push_front(0));
}

void remove_zeros_a_esquerda(deque<int>& d){    
    if(d.size() > 1)
    {
        int cont = 0;

        for(const int& x : d) {
            if(x == 0) cont ++;
            else break;
        }

        for(int i=0; i<cont; i++, d.pop_front());
    }
}

string factorial(const int& n) {
    
    deque<int> fact; fact.push_back(1);

    for(int c=2; c<=n; c++)
    {
        remove_zeros_a_esquerda(fact);

        deque<int> multiplicador = multiplicador_em_valores(c); // TODO:
        deque<int> soma_das_microsomas; soma_das_microsomas.push_back(0);


        for(size_t m=0; m<multiplicador.size(); m++) // percorre por cada digito do multiplicador
        {
            deque<int> microsoma; microsoma.resize(fact.size() + 1);

            int vai1 = 0;

            for(int f=fact.size()-1;f>=0 || vai1 >0;f--) // percorre por cada digito do fact para multiplicar por cada um dele
            {
                int index_microsoma = microsoma.size() - fact.size() + f;
                int produto_algarismos =  vai1 + (f >= 0 ? (fact[f] * multiplicador[m]) : 0);
                vai1 = produto_algarismos / 10;

                index_microsoma = index_microsoma + ((f == fact.size()-1)?0:1);

                microsoma[index_microsoma] = produto_algarismos % 10;

                if(vai1 == 0) break;

                microsoma.push_front(0);
                fact.push_front(0);
            }

            //remove_zeros_a_esquerda(fact);
            remove_zeros_a_esquerda(microsoma);

            // ajusta o tamanho da deque de soma_das_microsomas, para que a soma possa ocorrer sem segmentacao
            if(soma_das_microsomas.size() < microsoma.size() + fact.size()) {
                adiciona_zeros(soma_das_microsomas, microsoma.size() + fact.size() - soma_das_microsomas.size());
            }

            vai1 = 0;

            // somo a microsoma com a soma das microsomas
            // primeiro percorre a parte que a microsoma é util: soma sem o vai 1 ( depois somar apenas vai1)
            rf(s,microsoma.size(),0)// no pior dos casos vai percorrer a soma_das_microsomas toda
            {
                size_t index_soma = soma_das_microsomas.size() - microsoma.size() + s;
                soma_das_microsomas[index_soma] += microsoma[s] + vai1;
                vai1 = microsoma[s-1]/10;

                if(vai1 == 0 and microsoma[s-1] == 0) break;
            
            }
            if(vai1 >= 0) 
                soma_das_microsomas[soma_das_microsomas.size() - microsoma.size() - 1] += vai1; 

            remove_zeros_a_esquerda(soma_das_microsomas);
        }

        if(fact.size() < soma_das_microsomas.size() + 1)
            adiciona_zeros(fact, soma_das_microsomas.size() + 1 - fact.size());
        
        fact = soma_das_microsomas;

        remove_zeros_a_esquerda(fact);       
        
    }

    string retorno;
    for(int& x : fact) {
        retorno += to_string(x);
    }
    return retorno;
}

int main() {
    cout << "Digite um numero inteiro: "; int n; cin >> n;

    cout << "Respota: \n" << factorial(n) << endl;

    return 0;
}