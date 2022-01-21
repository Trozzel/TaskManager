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

    class TodoBase {
        #int uniqueId
        #string name
        #int parentId
        #datetime created
        #datetime updated
        +getUniqueId()
        +getName()
        +getParentId()
        +getCreated()
        +getUpdated()
        +setName(string)
        +setParentId(int)
        +update()
    }
    <<interface>> TodoBase

   TodoBase <-- Context
```