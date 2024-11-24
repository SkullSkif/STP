#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>

class Expression {
    protected:
        std::vector<Expression> oper;
    public:
        virtual void add_operand(std::shared_ptr<Expression> oper){};
        virtual double eval(){};
};

class Number {
    private:
        double num;
    public:
        void add_operand(std::vector<Expression> oper)

}

int main(){

    return 0;
}