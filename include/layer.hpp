#pragma once
#include <iostream>
#include <functional>
#include "matrix.hpp"

class Layer {
public:
    // Constructor
    Layer(int input_neurons, int output_neurons, std::function<Matrix(const Matrix&)> activation_func):     
        input_neurons_(input_neurons),
        output_neurons_(output_neurons),
        weights_(input_neurons, output_neurons),
        biases_(1, output_neurons),
        activation_function_(activation_func)
    {}

    // Forward pass: computes output given input activations
    Matrix forward(const Matrix& input) {
        Matrix Z = (input * weights_).broadcast_add(biases_);
        return activation_function_(Z);
    }
    

private:
    int input_neurons_;
    int output_neurons_;
    Matrix weights_; // Dimensions: input_neurons x output_neurons
    Matrix biases_;  // Dimensions: 1 x output_neurons
    std::function<Matrix(const Matrix&)> activation_function_;
};

