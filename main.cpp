#include <iostream>
#include <ctime>
#include <cstdlib>

/*Эффективно смоделировать RAID 5 (или RAID 2), для k буферов размера n кБайт
Технология использует контрольные суммы для восстановления данных в случае выхода из строя одного жёсткого диска. Нужно проделать тоже самое, только на буферах(массивах фиксированной длины). В моделировании нужно заполнить несколько буферов данных, по ним построить буфер контрольных сумм. Затем выбрать случайным образом один из буферов, как исчезнувший. После восстановить исчезнувшие данные и сравнить восстановленные данные с настоящими.
*/

using namespace std;

int main()
{
    srand(unsigned(time(0)));
    int n, buffsize, k, broken;
    unsigned int xorop;
    unsigned int** buffers;
    unsigned int* recovered;
    bool check = 1;

    cout << "Input a size of data buffers (kB):\t";
    cin >> n;
    buffsize = n*256;
    cout << "Input a quantity of buffers:\t";
    cin >> k;

    buffers = new unsigned int*[k];
    for (int f = 0; f < k; f++) buffers[f] = new unsigned int[buffsize];
    for (int i = 0; i < k-1; i++){
        for (int j = 0; j < buffsize; j++) buffers[i][j] = rand();
    }


    for (int m = 0; m < buffsize; m++){
        xorop = buffers[0][m];
        for (int n = 1; n < k-1; n++){
            xorop ^= buffers[n][m];
        }
        buffers[k-1][m] = xorop;
    }


    broken = rand() % k + 0;

    recovered = new unsigned int [buffsize];


    for (int m = 0; m < buffsize; m++){
        xorop = 0;
        for (int n = 0; n < k; n++){
            if (n != broken)    xorop ^= buffers[n][m];
        }
        recovered[m] = xorop;
    }

    for (int g = 0; g < buffsize; g++){
        if (buffers[broken][g] != recovered[g]) check = 0;
    }

    if (check) cout << "\nThe broken buffer was restored correctly.";
    if (!check) cout << "\nThere are some errors in the restored buffer.";
    return 0;
}
