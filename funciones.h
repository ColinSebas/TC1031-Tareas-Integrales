/*
  * funciones.h
  * Date: 17/08/23
  * Auhtor: Sebastián Colín
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones {

    public:

        Funciones(){};

        int sumaIterativa (int n) {

            int acum = 0;
            for (int i = 0; i <= n; i++) {
                acum = acum + i;
            }

            return acum;

        }

        int sumaRecursiva (int n) {

            if (n == 0) {
                return 0;
            } else {
                return n + sumaRecursiva(n - 1);
            }

        }

        int sumaDirecta (int n) {

            return ((n * (n + 1)) / 2);

        }

};

#endif
