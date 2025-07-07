#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix() {};

    Matrix(int row_, int col_)
    {
        row = row_;
        col = col_;
        data.resize(row, std::vector<float>(col, 0.0));
    }
    void initialize(int row_, int col_)
    {
        row = row_;
        col = col_;
        data.resize(row, std::vector<float>(col, 0.0));
    }
    void randomize_matrix()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] = rand() % 100;
            }
        }
    }
    Matrix operator+=(const Matrix &other)
    {
        check_same_size(other);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }
    Matrix operator-=(const Matrix &other)
    {
        check_same_size(other);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }
    Matrix operator*=(const Matrix &other)
    {
        check_same_size(other);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] *= other.data[i][j];
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix &other) const
    {
        Matrix result = *this;
        result += other;
        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        check_same_size(other);
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (col != other.row)
            throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
        Matrix result(row, other.col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < other.col; ++j)
                for (int k = 0; k < col; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }
    Matrix operator*(float scalar) const
    {
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.data[i][j] = data[i][j] * scalar;
        return result;
    }

    Matrix operator/(float scalar) const
    {
        if (scalar == 0.0f)
            throw std::invalid_argument("Division by zero in matrix operator/");
        Matrix result(row, col);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.data[i][j] = data[i][j] / scalar;
        return result;
    }

    Matrix transpose() const
    {
        Matrix result(col, row);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                result.data[j][i] = data[i][j];
        return result;
    }
    void print_matrix()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void print_matrix_with_index()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                std::cout << "[" << i << "][" << j << "] = " << data[i][j] << std::endl;
            }
        }
    }
    void set_values(float val)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] = val;
            }
        }
    }
    
    
private:
    int row, col;
    std::vector<std::vector<float>> data;
    void check_same_size(const Matrix &other) const
    {
        if (row != other.row || col != other.col)
            throw std::invalid_argument("Matrix dimensions do not match.");
    }
};