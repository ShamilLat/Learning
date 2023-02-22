#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <iomanip>

namespace numbers
{
    class complex_stack
    {
    private:
        complex *stack_;
        int size_ = 0;
        int poz_ = 0;

    public:
        complex_stack () {
            stack_ = new complex[1];
            size_ = 0;
            poz_ = -1;
        }
        
        complex_stack (const complex num) {
            size_ = 1;
            poz_ = 0;
            stack_ = new complex[size_];
            stack_[0] = num;
        }

        complex_stack (const complex_stack &other_stack) {
            size_ = other_stack.size();
            poz_ = size_ - 1;
            stack_ = new complex[size_];
            for(int i = 0; i < size_; i++) {
                stack_[i] = other_stack[i];
            }
        }

        size_t size() const {
            return (size_t)(poz_ + 1);
        }

        friend complex_stack operator << (complex_stack other_stack, const complex num);
        friend complex operator + (const complex_stack &other_stack);
        friend complex_stack operator ~ (complex_stack other);

        complex_stack & operator = (const complex_stack &other_stack) {
            poz_ = other_stack.poz_;
            size_ = (int)other_stack.size();
            delete[] stack_;
            stack_ = new complex[size_];
            for (int i = 0; i < size_; i++) {
                stack_[i] = other_stack.stack_[i];
            }
            return *this;
        }

        const complex operator [] (int i) const {
            return complex(stack_[i].re(), stack_[i].im());
        }

        ~complex_stack () {
            delete [] stack_;
        }
    };

    complex_stack operator ~ (complex_stack other) {
        complex *resize = new complex[other.poz_];
        for (int i = 0; i < other.poz_; i++) {
            resize[i] = other.stack_[i];
        }
        other.poz_--;
        delete[] other.stack_;
        other.stack_ = resize;

        return other;
    }


    complex_stack operator << (complex_stack other, const complex num) {
        other.poz_++;
        if (other.poz_ == other.size_) {
            other.size_++;
            complex *resize = new complex[other.size_];
            for(int i = 0; i < other.poz_; i++) {
                resize[i] = other.stack_[i];
            }
            resize[other.poz_] = num;
            delete[] other.stack_;
            other.stack_ = resize;
            return other;
        } else {
            other.stack_[other.poz_] = num;
            return other;
        }
    }
    complex operator + (const complex_stack &other_stack) {
        return other_stack.stack_[other_stack.poz_];
    }

}