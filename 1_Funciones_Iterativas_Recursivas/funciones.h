// Jesus Osvaldo Ramos Perez A01713833
#ifndef FUNCIONES_H
#define FUNCIONES_H

class Funciones {
public:
//Metodo Iterativo calcula la suma usando un ciclo for
    int sumaIterativa(int n) const {
        if (n <= 0) return 0;             //si n es 0 o negativo
        int acum = 0;                    
        for (int i = 1; i <= n; i++) {   //ciclo de 1 a n
            acum += i;
        }
        return acum;
    }
//Metodo Recursivo utiliza llamadas recursivas para sumar de 1 a n 
    int sumaRecursiva(int n) const {    
        if (n <= 0) return 0;            //si n<=0 
        if (n == 1) return 1;            //si n=1
        return n + sumaRecursiva(n - 1); //paso recursivo 
    }
//Metodo Directo se utiliza la formula  n * ((n + 1) / 2) en 3 casos
    int sumaDirecta(int n) const {
        if (n <= 0) return 0;            //si n es 0 o negativo
        if (n % 2 == 0) {                //si n es par 
            return (n / 2) * (n + 1);
        } else {                         //si n es impar
            return n * ((n + 1) / 2);
        }
    }
};

#endif

