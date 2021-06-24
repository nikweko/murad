#include "matrix.h"
using namespace std;

Matrix::Matrix()
{
}

Matrix::Matrix(int rowSize, int colSize, double initial)
{
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);
    for (int i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize, initial);
    }
}

//Конструктор считывания матрицы из файла
Matrix::Matrix(const char* fileName)
{
    ifstream file_A(fileName);

    int colSize = 0; //строка
    int rowSize = 0; //столбец

    string line_A;
    int idx = 0;
    double element_A;
    double* vector_A = nullptr;

    if (file_A.is_open() && file_A.good())
    {
        while (getline(file_A, line_A))
        {
            rowSize += 1;
            stringstream stream_A(line_A);
            colSize = 0;
            while (1)
            {
                stream_A >> element_A;
                if (!stream_A)
                    break;
                colSize += 1;
                double* tempArr = new double[idx + 1];
                copy(vector_A, vector_A + idx, tempArr);
                tempArr[idx] = element_A;
                vector_A = tempArr;
                idx += 1;
            }
        }
    }
    else
    {
        cout << "Failed to open file " << fileName << ". \n";
    }

    int j;
    idx = 0;
    m_matrix.resize(rowSize);
    for (int i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize);
    }
    for (int i = 0; i < rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            this->m_matrix[i][j] = vector_A[idx];
            idx++;
        }
    }

    m_colSize = colSize;
    m_rowSize = rowSize;
    delete[] vector_A; //очистка памяти
}

/*!
\param [in] Matrix - Матрица
\param [in] Matrix - Матрица
\return Matrix - Сумма двух матриц
*/
//!Функция сложение двух матриц
Matrix Matrix::operator+(Matrix & B)
{
    Matrix sum(m_colSize, m_rowSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            sum(i, j) = this->m_matrix[i][j] + B(i, j);
        }
    }
    return sum;
}

/*!
\param [in] Matrix - Матрица
\param [in] Matrix - Матрица
\return Matrix - Вычитание двух матриц
*/
//!Функция вычитание двух матриц
Matrix Matrix::operator-(Matrix& B)
{
    Matrix diff(m_colSize, m_rowSize, 0.0);
    int i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            diff(i, j) = this->m_matrix[i][j] - B(i, j);
        }
    }

    return diff;
}

/*!
\param [in] Matrix - Матрица
\param [in] Matrix - Матрица
\return Matrix - Умножение двух матриц
*/
//!Функция умножения двух матриц
Matrix Matrix::operator*(Matrix& B)
{
    Matrix multip(m_rowSize, B.getCols(), 0.0);
    if (m_colSize == B.getRows())
    {
        int i, j, k;
        double temp = 0.0;
        for (i = 0; i < m_rowSize; i++)
        {
            for (j = 0; j < B.getCols(); j++)
            {
                temp = 0.0;
                for (k = 0; k < m_colSize; k++)
                {
                    temp += m_matrix[i][k] * B(k, j);
                }
                multip(i, j) = temp;
            }
        }
        return multip;
    }
    else
    {
        return "Error";
    }
}


/*!
\param [in] rowNo - номер строки
\param [in] colNo - номер столбца
\return Matrix[rowNo, colNo] - элемент матрицы находящийся на строке rowNo и столбце colNo
*/
//!Фунция вернет элемент матрицы по индексам строки и столбца A(x,y)
double& Matrix::operator()(const int& rowNo, const int& colNo)
{
    return this->m_matrix[rowNo][colNo];
}

/*!
\return m_rowSize - количество строк в матрице
*/
//!Фунция вернет кол-во строк
unsigned Matrix::getRows() const
{
    return this->m_rowSize;
}

/*!
\return m_rowSize - количество столбцов в матрице
*/
//!Фунция вернет кол-во столбцов
unsigned Matrix::getCols() const
{
    return this->m_colSize;
}

/*!
\return Matrix - транспонированная матрица
*/
//!Функция транспонирование матрицы
Matrix Matrix::transpose()
{
    Matrix Transpose(m_colSize, m_rowSize, 0.0);
    for (int i = 0; i < m_colSize; i++)
    {
        for (int j = 0; j < m_rowSize; j++)
        {
            Transpose(i, j) = this->m_matrix[j][i];
        }
    }
    return Transpose;
}

//!Функция печати матрицы в консоль
void Matrix::print() const
{
    cout << "Matrix: " << endl;
    for (int i = 0; i < m_rowSize; i++)
    {
        for (int j = 0; j < m_colSize; j++)
        {
            cout << m_matrix[i][j] << " ";
        }
        cout << endl;
    }
}
