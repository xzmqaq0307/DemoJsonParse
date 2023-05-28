#include <optional>
#include <iostream>

class Test {
public:
    int num1, num2;
    Test(int n1, int n2) {
        num1 = n1;
        num2 = n2;
    }
    bool isOk() {
        return num1 + num2 >= 0 ? true : false;
    }
};

std::optional<Test> foo(int num) {
    Test t(num, num);
    if (t.isOk()) {
        return t;
    }
    return std::nullopt;
}

int main()
{
    int age = 20;
    std::optional<Test> opt = foo(age);
    if (opt.has_value()) {
        std::cout << (opt.value()).num1 << std::endl;
    }
}