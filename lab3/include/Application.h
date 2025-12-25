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
        // Реализация шаблона Singleton
        static Application& GetInstance();
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        // Шаблон Facade: упрощенные методы интерфейса
        void Initialize(const std::string& inputPath, const std::string& outputPath);
        void Run();
        void Shutdown();

        // Управление фигурами
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

        // Управление выделением
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

        // State Pattern: управление состоянием редактора
        void SetState(std::unique_ptr<IEditorState> state);
        IEditorState* GetCurrentState() const
        {
            return m_currentState.get();
        }

        EditorMode GetCurrentMode() const;

        // Управление стилями (для панели инструментов)
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

        // Command Pattern: выполнение команд и отмена
        void ExecuteCommand(std::unique_ptr<ICommand> cmd);
        void Undo();
        void Redo();

        // Доступ к окну
        sf::RenderWindow* GetWindow()
        {
            return m_window.get();
        }

        // Доступ к менеджерам из лабораторной работы 2
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
        // Приватный конструктор для Singleton
        Application();
        ~Application() = default;

        // Внутренняя обработка событий
        void ProcessEvents();
        void HandleMouseButtonPressed(const sf::Event::MouseButtonPressed& event);
        void HandleMouseButtonReleased(const sf::Event::MouseButtonReleased& event);
        void HandleMouseMoved(const sf::Event::MouseMoved& event);
        void HandleKeyPressed(const sf::Event::KeyPressed& event);

        // Создание команды для перетаскивания
        void CreateMoveCommandForDragDrop();

        // Рендеринг
        void Render();

        // Члены данных
        std::vector<std::shared_ptr<IGeometry>> m_shapes;
        std::vector<std::shared_ptr<IGeometry>> m_selected;
        std::unique_ptr<IEditorState> m_currentState;  // State Pattern

        // Свойства стилей (для панели инструментов)
        sf::Color m_outlineColor = sf::Color::Black;
        sf::Color m_fillColor = sf::Color::White;
        float m_outlineThickness = 1.0f;

        // Command Pattern: история команд для отмены
        std::vector<std::unique_ptr<ICommand>> m_commandHistory;
        size_t m_commandHistoryIndex = 0;

        // Менеджеры из лабораторной работы 2
        SelectionManager m_selectionManager;
        DragDropManager m_dragDropManager;
        CompositeManager m_compositeManager;  // Composite Pattern

        // SFML окно и панель инструментов
        std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<class Toolbar> m_toolbar;  // Использует State и Command patterns

        // Пути к файлам
        std::string m_inputPath;
        std::string m_outputPath;

        // Состояние перетаскивания
        bool m_dragging = false;
        sf::Vector2f m_lastMousePos;
        sf::Vector2f m_dragStartMousePos;  // Начальная позиция мыши при начале перетаскивания
        std::vector<sf::Vector2f> m_dragStartPositions;
        float m_totalDragX = 0.0f;  // Общее перемещение по X за время перетаскивания
        float m_totalDragY = 0.0f;  // Общее перемещение по Y за время перетаскивания
    };

}

#endif