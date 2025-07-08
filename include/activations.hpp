#pragma once
#include <cmath>
#include <algorithm> // For std::max_element
#include "matrix.hpp"

// Sigmoid activation function
inline Matrix sigmoid(const Matrix& x) {
    Matrix result(x);
    for (int i = 0; i < result.get_row(); ++i) {
        for (int j = 0; j < result.get_col(); ++j) {
            float val = result.data[i][j];
            result.data[i][j] = 1.0f / (1.0f + std::exp(-val));
        }
    }
    return result;
}

inline Matrix sigmoid_derivative(const Matrix& activated) {
    Matrix result(activated);
    for (int i = 0; i < result.get_row(); ++i) {
        for (int j = 0; j < result.get_col(); ++j) {
            float val = result.data[i][j];
            result.data[i][j] = val * (1.0f - val);
        }
    }
    return result;
}

// ReLU activation function
inline Matrix relu(const Matrix& x) {
    Matrix result(x);
    for (int i = 0; i < result.get_row(); ++i) {
        for (int j = 0; j < result.get_col(); ++j) {
            float val = result.data[i][j];
            result.data[i][j] = val > 0.0f ? val : 0.0f;
        }
    }
    return result;
}

// Derivative of ReLU
inline Matrix relu_derivative(const Matrix& x) {
    Matrix result(x);
    for (int i = 0; i < result.get_row(); ++i) {
        for (int j = 0; j < result.get_col(); ++j) {
            float val = result.data[i][j];
            result.data[i][j] = val > 0.0f ? 1.0f : 0.0f;
        }
    }
    return result;
}

// Softmax activation function (applied row-wise for batch inputs)
inline Matrix softmax( Matrix& x) {
    Matrix result(x);
    for (int i = 0; i < result.get_row(); ++i) {
        // Find max for numerical stability
        float max_val = *std::max_element(x.data[i].begin(), x.data[i].end());
        
        // Compute exponentials and sum
        float sum = 0.0f;
        for (int j = 0; j < x.get_col(); ++j) {
            result.data[i][j] = std::exp(x.data[i][j] - max_val);
            sum += result.data[i][j];
        }
        // Normalize
        for (int j = 0; j < x.get_col(); ++j) {
            result.data[i][j] /= sum;
        }
    }
    return result;
}
