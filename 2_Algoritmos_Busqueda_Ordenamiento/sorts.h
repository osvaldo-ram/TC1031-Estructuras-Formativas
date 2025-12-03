#ifndef SORTS_H
#define SORTS_H

#include <vector>

template <class T>
class Sorts {
public:
    // Ordena en forma ascendente usando seleccion
    void ordenaSeleccion(std::vector<T>& v) {
        int n = static_cast<int>(v.size());
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (v[j] < v[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                T tmp = v[i];
                v[i] = v[minIdx];
                v[minIdx] = tmp;
            }
        }
    }

    // Ordena en forma ascendente usando burbuja
    void ordenaBurbuja(std::vector<T>& v) {
        int n = static_cast<int>(v.size());
        bool swapped = true;
        for (int i = 0; i < n - 1 && swapped; ++i) {
            swapped = false;
            for (int j = 0; j < n - 1 - i; ++j) {
                if (v[j + 1] < v[j]) {
                    T tmp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = tmp;
                    swapped = true;
                }
            }
        }
    }

    // Ordena en forma ascendente usando merge sort
    void ordenaMerge(std::vector<T>& v) {
        if (v.size() < 2) return;
        std::vector<T> aux(v.size());
        mergeSplit(v, aux, 0, static_cast<int>(v.size()) - 1);
    }

    // Busqueda secuencial regresa indice o -1 si no esta
    int busqSecuencial(const std::vector<T>& v, const T& dato) {
        for (int i = 0; i < static_cast<int>(v.size()); ++i) {
            if (v[i] == dato) return i;
        }
        return -1;
    }

    // Busqueda binaria el vector debe estar ordenado ascendentemente
    int busqBinaria(const std::vector<T>& v, const T& dato) {
        int low = 0;
        int high = static_cast<int>(v.size()) - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (v[mid] == dato) return mid;
            if (dato < v[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }

private:
    void mergeSplit(std::vector<T>& v, std::vector<T>& aux, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSplit(v, aux, left, mid);
        mergeSplit(v, aux, mid + 1, right);
        merge(v, aux, left, mid, right);
    }

    void merge(std::vector<T>& v, std::vector<T>& aux, int left, int mid, int right) {
        int i = left;      // puntero para la mitad izquierda
        int j = mid + 1;   // puntero para la mitad derecha
        int k = left;      // puntero para aux

        // Copiar el rango a aux
        for (int idx = left; idx <= right; ++idx) aux[idx] = v[idx];

        while (i <= mid && j <= right) {
            if (aux[i] <= aux[j]) {
                v[k++] = aux[i++];
            } else {
                v[k++] = aux[j++];
            }
        }
        while (i <= mid) v[k++] = aux[i++];
        while (j <= right) v[k++] = aux[j++];
    }
};

#endif 
