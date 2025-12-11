#include "App.h"
#include "Parser.h"
#include <iostream>

using namespace geom;

int main(int argc, char** argv)
{
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    bool noGui = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--input" && i + 1 < argc)
        {
            inputPath = argv[++i];
        }
        else if (arg == "--output" && i + 1 < argc)
        {
            outputPath = argv[++i];
        }
        else if (arg == "--no-gui")
        {
            noGui = true;
        }
    }

    if (noGui)
    {
        Parser parser;
        auto shapes = parser.ParseFile(inputPath);
        Parser::WriteResults(outputPath, shapes);
        return 0;
    }

    auto& app = App::GetInstance();
    app.Initialize(inputPath, outputPath);
    app.Run();
    app.Shutdown();

    return 0;
}