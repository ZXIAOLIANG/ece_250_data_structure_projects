#include <iostream>
#include <cstring>

class try_sth{
    public:
        int num;
        void print_sth();
        try_sth();
    private:
        void print_in_private();
    
};

try_sth::try_sth(){
    this->num = 1;
}

void try_sth::print_sth(){
    std::cout << "i'm here" << std::endl;
    this->print_in_private();
}
void try_sth::print_in_private(){
    std::cout << this->num << std::endl;
}

int main(){
    int *array = new int[5];
    for (int i = 0; i < 5; ++i ){
        array[i] = i;
    }
    std::cout << " -1%6 " << -1%6 << std::endl;
    std::cout << *array << std::endl;
    std::cout << *(array+1) << std::endl;
    try_sth *obj = new try_sth();
    obj->print_sth();

}