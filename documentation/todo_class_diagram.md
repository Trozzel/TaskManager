# Todo Class Diagrams

``` mermaid
    classDiagram
    class Observer {
        +update()
    }
    <<interface>> Observer

    class Subject {
        +registerObserver(Observer)
        +removeObserver(Observer)
        +notifyObservers()
    }
    <<interface>> Subject

    Subject --o Observer : observers

    class GtdBase {
        - int uniqueId
        - str name
        - int parentId
        - datetime created
        - datetime modified
        +uniqueId()
        +tableName()
        +name()
        +parentId()
        +created()
        +updated()
        +name(string)
        +parentId(int)
        +update()
    }
    <<interface>> GtdBase

   TodoBase <-- Context
```