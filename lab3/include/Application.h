#ifndef GEOM_VISUALIZER_APPLICATION_H
#define GEOM_VISUALIZER_APPLICATION_H

#include "Geometry.h"
#include "EditorState.h"          
#include "Command.h"              
#include "CompositeManager.h"     
#include "DragAndDrop.h"   
#include "SelectionManager.h"     
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

namespace geom
{
    class Application
    {
    public:
        // Singleton Pattern implementation
        static Application& GetInstance();
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        // Facade Pattern: simplified interface methods
        void Initialize(const std::string& inputPath, const std::string& outputPath);
        void Run();
        void Shutdown();

        // Shape management
        void AddShape(std::shared_ptr<IGeometry> shape);
        void RemoveShape(std::shared_ptr<IGeometry> shape);

        const std::vector<std::shared_ptr<IGeometry>>& GetShapes() const
        {
            return m_shapes;
        }

        std::vector<std::shared_ptr<IGeometry>>& GetShapes()
        {
            return m_shapes;
        }

        // Selection management
        void SelectShape(std::shared_ptr<IGeometry> shape, bool addToSelection = false);
        void ClearSelection();

        const std::vector<std::shared_ptr<IGeometry>>& GetSelected() const
        {
            return m_selected;
        }

        std::vector<std::shared_ptr<IGeometry>>& GetSelected()
        {
            return m_selected;
        }

        // State Pattern: editor state management
        void SetState(std::unique_ptr<IEditorState> state);
        IEditorState* GetCurrentState() const
        {
            return m_currentState.get();
        }

        EditorMode GetCurrentMode() const;

        // Style management (for toolbar)
        void SetOutlineColor(const sf::Color& color)
        {
            m_outlineColor = color;
        }

        sf::Color GetOutlineColor() const
        {
            return m_outlineColor;
        }

        void SetFillColor(const sf::Color& color)
        {
            m_fillColor = color;
        }

        sf::Color GetFillColor() const
        {
            return m_fillColor;
        }

        void SetOutlineThickness(float thickness)
        {
            m_outlineThickness = thickness;
        }

        float GetOutlineThickness() const
        {
            return m_outlineThickness;
        }

        // Command Pattern: command execution and undo
        void ExecuteCommand(std::unique_ptr<ICommand> cmd);
        void Undo();

        // Window access
        sf::RenderWindow* GetWindow()
        {
            return m_window.get();
        }

        // Access to managers from lab 2
        SelectionManager& GetSelectionManager()
        {
            return m_selectionManager;
        }

        DragDropManager& GetDragDropManager()
        {
            return m_dragDropManager;
        }

        CompositeManager& GetCompositeManager()
        {
            return m_compositeManager;
        }

    private:
        // Private constructor for Singleton
        Application() = default;
        ~Application() = default;

        // Internal event processing
        void ProcessEvents();
        void HandleMouseButtonPressed(const sf::Event::MouseButtonPressed& event);
        void HandleMouseButtonReleased(const sf::Event::MouseButtonReleased& event);
        void HandleMouseMoved(const sf::Event::MouseMoved& event);
        void HandleKeyPressed(const sf::Event::KeyPressed& event);

        // Command creation for drag & drop
        void CreateMoveCommandForDragDrop();

        // Data members
        std::vector<std::shared_ptr<IGeometry>> m_shapes;
        std::vector<std::shared_ptr<IGeometry>> m_selected;
        std::unique_ptr<IEditorState> m_currentState;  // State Pattern

        // Style properties (for toolbar)
        sf::Color m_outlineColor = sf::Color::Black;
        sf::Color m_fillColor = sf::Color::White;
        float m_outlineThickness = 1.0f;

        // Command Pattern: history of commands for undo
        std::vector<std::unique_ptr<ICommand>> m_commandHistory;
        size_t m_commandHistoryIndex = 0;

        // Managers from lab 2
        SelectionManager m_selectionManager;
        DragDropManager m_dragDropManager;
        CompositeManager m_compositeManager;  // Composite Pattern

        // SFML window and toolbar
        std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<class Toolbar> m_toolbar;  // Uses State and Command patterns

        // File paths
        std::string m_inputPath;
        std::string m_outputPath;

        // Drag & Drop state
        bool m_dragging = false;
        sf::Vector2f m_lastMousePos;
        std::vector<sf::Vector2f> m_dragStartPositions;
    };

} 

#endif 