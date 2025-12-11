#ifndef GEOM_VISUALIZER_COMMAND_H
#define GEOM_VISUALIZER_COMMAND_H

namespace geom {

class ICommand {
public:
  virtual ~ICommand() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
};

}

#endif