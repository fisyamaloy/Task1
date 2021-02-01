#pragma once
#include <vector>
#include <numeric>

template<class T>
struct AlgebraicAction {
    virtual T calculate(const std::vector<T>& numbers) const = 0;
};

template<class T>
struct Addition : AlgebraicAction<T> {
    T calculate(const std::vector<T>& numbers) const override {
        return std::accumulate(numbers.begin(), numbers.end(), (T)0);
    }
};

template<class T>
struct Multiplication : AlgebraicAction<T> {
    T calculate(const std::vector<T>& numbers) const override {
        return std::accumulate(numbers.begin(), numbers.end(), (T)1, std::multiplies<T>());
    }
};

template<class T>
struct SquaresAddition : AlgebraicAction<T> {
    T calculate(const std::vector<T>& numbers) const override {
        return std::accumulate(numbers.begin(), numbers.end(), (T)0, [](const T firstNum, const T secondNum) {
            return firstNum + secondNum * secondNum;
        });
    }
};