#ifndef GEOM_VISUALIZER_APP_H
#define GEOM_VISUALIZER_APP_H

#include <string>

namespace geom
{

    class App
    {
    public:
        int run(int argc, char** argv);

    private:
        struct Config
        {
            std::string inputPath;
            std::string outputPath;
            bool noGui = false;
        };

        Config parseArguments(int argc, char** argv);
        void runVisualization(const std::string& inputPath, const std::string& outputPath, bool noGui);
    };

} 

#endif