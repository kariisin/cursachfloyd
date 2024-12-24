#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define INF 999999999

// Вывод матрицы
void printMatrix(int** matrix, int n, FILE* fout) {
    printf("Исходная матрица: \n");
    fprintf(fout, "Исходная матрица: \n");
    fprintf(fout, "Количество вершин: %d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] >= INF) {
                printf("INF ");
                fprintf(fout, "INF ");
            }
            else {
                printf("%d ", matrix[i][j]);
                fprintf(fout, "%d ", matrix[i][j]);
            }
        }
        printf("\n");
        fprintf(fout, "\n");
    }
    printf("\n");
    fprintf(fout, "\n");
}

// Алгоритм Флойда
void originalFloyd(int** matrix, int n) {
    //пробегаемся по всем вершинам и ищем более короткий путь чрез вершину k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = (matrix[i][j] < matrix[i][k] + matrix[k][j]) ? matrix[i][j] : (matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

// Функция для безопасного ввода целого числа
int safeInputInt() {
    int value;
    while (1) {
        if (scanf("%d", &value) != 1 || value < 0) {
            printf("Ошибка ввода. Пожалуйста, введите неотрицательное целое число: ");
            while (getchar() != '\n'); // Очистка буфера ввода
        }
        else {
            break;
        }
    }
    return value;
}

int main() {
    setlocale(LC_ALL, "Rus");

    FILE* fout = fopen("newMatrix.txt", "w");
    if (fout == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    int n, numberEnter, numberVec;
    int ver;

    printf("Выберите как вы хотите задать матрицу смежности: \n1. Случайно сгенерировать\n2. Ввести вручную\n3. Ввести из файла\n");
    numberEnter = safeInputInt();
    printf("\n");

    // Проверка выбора способа генерации матрицы
    while (numberEnter < 1 || numberEnter > 3) {
        printf("Неверный выбор. Пожалуйста, выберите 1, 2 или 3: ");
        numberEnter = safeInputInt();
    }

    if (numberEnter == 1) {
        printf("Введите количество вершин в матрице: ");
        n = safeInputInt();
        printf("\nВыберите вид графа: \n1. Ориентированный\n2. Неориентированный\n");
        
        srand(time(NULL));

        int** matrix = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            matrix[i] = (int*)malloc(n * sizeof(int));
        }

        numberVec = safeInputInt();
        // Проверка выбора типа графа
        while (numberVec < 1 || numberVec > 2) {
            printf("Неверный выбор. Пожалуйста, введите 1 для ориентированного или 2 для неориентированного графа: ");
            numberVec = safeInputInt();
        }

        // Случайная генерация матрицы
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    matrix[i][j] = 0;
                }
                else {
                    ver = rand() % 2;
                    matrix[i][j] = (ver == 1) ? rand() % 100 : INF; // Исправлено
                }
            }
        }


        if (numberVec == 2) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[j][i] = matrix[i][j];
                }
            }
        }

        printMatrix(matrix, n, fout);
        originalFloyd(matrix, n);
        printMatrix(matrix, n, fout);
        printf("\nРезультат сохранён в файл newMatrix.txt\n");

        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    // Ручной ввод
    else if (numberEnter == 2) {
        printf("Введите количество вершин в матрице: ");
        n = safeInputInt();
        int** matrix = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            matrix[i] = (int*)malloc(n * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            printf("Ввод %d-й строки\n\n", i + 1);
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    printf("%d-й элемент массива по умолчанию 0\n", j + 1);
                    matrix[i][j] = 0;
                }
                else {
                    int numb;
                    int proverka = 0;
                    while (!proverka) {
                        printf("Введите %d-й элемент массива: ", j + 1);
                        numb = safeInputInt();
                        if (numb >= 0) {
                            matrix[i][j] = numb;
                            proverka = 1;
                        }
                        else {
                            printf("Невозможно ввести отрицательный элемент. Повторите попытку\n");
                        }
                    }
                }
            }
        }

        printMatrix(matrix, n, fout);
        originalFloyd(matrix, n);
        printMatrix(matrix, n, fout);
        printf("\nРезультат сохранён в файл newMatrix.txt\n");

        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    // Ввод с файла
    else if (numberEnter == 3) {
        FILE* file = fopen("matrix.txt.txt", "r");
        if (!file) {
            printf("Файл не может быть открыт!\n");
            fclose(fout);
            return 1;
        }
        fscanf(file, "%d", &n);
        printf("Количество вершин в матрице равно: %d\n", n);

        int** matrix = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            matrix[i] = (int*)malloc(n * sizeof(int));
        }

        // Считываем матрицу
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(file, "%d", &matrix[i][j]);
                if (matrix[i][j] < 0) {
                    printf("В матрице обнаружен отрицательный элемент. Исправьте матрицу.\n");
                    fclose(file);
                    fclose(fout);
                    return 1;
                }
                if (i == j && matrix[i][j] != 0) {
                    printf("В матрице не все элементы главной диагонали нули. Исправьте матрицу.\n");
                    fclose(file);
                    fclose(fout);
                    return 1;
                }
            }
        }

        fclose(file); // закрываем файл

        printMatrix(matrix, n, fout);
        originalFloyd(matrix, n);
        printMatrix(matrix, n, fout);
        printf("\nРезультат сохранён в файл newMatrix.txt\n");

        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    fclose(fout); // закрываем файл вывода
    return 0;
}
