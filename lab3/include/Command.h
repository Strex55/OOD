#ifndef GEOM_VISUALIZER_COMMAND_H
#define GEOM_VISUALIZER_COMMAND_H

namespace geom
{

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

} 

#endif 