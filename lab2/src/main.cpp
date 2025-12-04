//D: 
//cd D:\Nikita\3_COURSE\OOD\lab2\build\Release
//geom_app.exe --input D:\Nikita\3_COURSE\OOD\lab2\input.txt --output D:\Nikita\3_COURSE\OOD\lab2\output.txt

#include "App.h"

int main(int argc, char** argv)
{
    geom::App app;
    return app.run(argc, argv);
}