#include <iostream>
#include <string>

#include "./headers/linked_stack.h"

using namespace std;

int main() {

    //char xmlfilename[100];

    //std::cin >> xmlfilename;  // entrada
    
    /*
     
       COLOQUE SEU CODIGO AQUI
    
    */
    structures::LinkedStack<string> tag_stack;

    tag_stack.push("testando");
    tag_stack.push("teste2");
    cout << tag_stack.pop() << endl;
    cout << tag_stack.pop() << endl;
    cout << tag_stack.top() << endl;

    //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida

    return 0;
}