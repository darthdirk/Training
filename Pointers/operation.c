

// use typedef for readability 
typedef int (operation_ptr)(int,int);

int add(int a, int b) {return a + b;}
int mult(int a, int b) {return a * b;}
int sub(int a, int b) {return a - b;}
int div(int a, int b) {return a / b;}

int do_operation(operation_ptr op, int x, int y) {
    return op(x,y);
}

int main(int argc, char **argv) {
    int result = do_operation(add, 5, 34);
    int result2 = do_operation(mult, 2, 3);
}