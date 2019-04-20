#include <iostream>

template<typename F>
void apply(int& x, const F& f){
    x = f(x);
}

int main(){
    int x = 1;
    apply(x,[](const int& x){ return x * 2;});
    std::cout << x << std::endl;
    return 0;
}