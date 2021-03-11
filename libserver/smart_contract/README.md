c++调用python3.8
References https://docs.python.org/3.8/extending/embedding.html#compiling

编译命令 
g++ -I/usr/include/python3.8/  example_main.cpp -o example_main -L/usr/lib/ -lpython3.8
