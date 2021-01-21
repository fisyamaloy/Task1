#pragma once
#include <vector>
#include <numeric>

template<class T>
struct AlgebraicAction {
    virtual T getResultOfAlgebraicAction(const std::vector<T>& numbers) const = 0;
};

template<class T>
struct Addition : AlgebraicAction<T> {
    T getResultOfAlgebraicAction(const std::vector<T>& numbers) const override {
        return std::accumulate(numbers.begin(), numbers.end(), (T)0);
    }
};

template<class T>
struct Multiplication : AlgebraicAction<T> {
    T getResultOfAlgebraicAction(const std::vector<T>& numbers) const override {
        return std::accumulate(numbers.begin(), numbers.end(), (T)1, [](const T firstNum, const T secondNum) {
            return firstNum * secondNum;
        });
    }
};

template<class T>
struct SquaresAddition : AlgebraicAction<T> {
    T getResultOfAlgebraicAction(const std::vector<T>& numbers) const override {
        T sumOfSquares = 0;
        for (size_t i = 0; i < numbers.size(); ++i) {
            sumOfSquares += numbers[i] * numbers[i];
        }

        return sumOfSquares;
    }
};