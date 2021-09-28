#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cassert>
#include <ostream>
#include <iosfwd>

template<typename T>
class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<T>> matrix;
public:
    Matrix(std::initializer_list<std::initializer_list<T>>&& matrix) :
    rows(matrix.size()) , cols((*matrix.begin()).size()) {
        for(const auto & row : matrix) {
            this->matrix.push_back(row);
        }
    }

    explicit Matrix(unsigned int rows , unsigned int cols) :
    rows(rows) , cols(cols) {
        for(auto i = 0; i < rows; ++i) {
            std::vector<T> row(cols);
            for(auto j = 0; j < cols; ++j) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
    }

    const std::vector<T> & operator[](unsigned int index) const {
        return matrix[index];
    }

    std::vector<T> & operator[](unsigned int index) {
        return matrix[index];
    }

    Matrix(Matrix<T> & that) :
    rows(that.rows) , cols(that.cols) {
        for(auto i = 0; i < that.rows; ++i) {
            std::vector<T> row(that.cols);
            for(auto j = 0; j < that.cols; ++j) {
                row[j] = that[i][j];
            }
            matrix.push_back(row);
        }
    }

    Matrix() :
    rows(0) , cols(0) , matrix(nullptr)
    {}

    Matrix<T> operator+(const Matrix<T> & that) {
        Matrix m = *(this);
        for(auto i = 0; i < rows; ++i) {
            for(auto j = 0 ; j < cols ; j++) {
                m[i][j] += that[i][j];
            }
        }
        return m;
    }

    Matrix<T> operator-(const Matrix<T> & that) {
        Matrix m = *(this);
        for(auto i = 0; i < rows; ++i) {
            for(auto j = 0 ; j < cols ; j++) {
                m[i][j] -= that[i][j];
            }
        }
        return m;
    }


    Matrix<T> operator!() {
        Matrix<T> m = *(this);
        for(auto i = 0 ; i < m.rows ; i++) {
            for(auto j = 0 ; j < m.cols ; j++) {
                m[i][j] = (*this)[j][i];
            }
        }
        return m;
    }

    bool operator==(const Matrix<T> & that) const {
        for(auto i = 0 ; i < that.rows ; i++) {
            for(auto j = 0 ; j < that.cols ; j++) {
                if ((*this)[i][j] != that[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }


    Matrix<T> operator*(int num) {
        Matrix<T> m = *(this);
        for(auto i = 0 ; i < m.rows ; i++) {
            for(auto j = 0 ; j < m.cols ; j++) {
                m[i][j] *= num;
            }
        }
        return m;
    }

    Matrix<T> operator*(const Matrix<T> & that) {
        Matrix<T> m = *(this);
        for(auto i = 0 ; i < m.rows ; i++) {
            for(auto j = 0 ; that.cols ; j++) {
                m[i][j] = 0;
                for(auto k = 0 ; k < m.cols ; k++) {
                    m[i][j] += (*this)[i][k] + that[k][j];
                }
            }
        }
        return m;
    }

    friend std::ostream & operator<<(std::ostream & out ,const Matrix<T> & that) {
        for(auto i = 0 ; i < that.rows ; i++) {
            for(auto j = 0 ; j < that.cols ; j++) {
                out << that[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    ~Matrix() {
        matrix.clear();
    }
};

#endif

