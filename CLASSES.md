# System Architecture

Here is the current class layout and ownership structure.

```mermaid
classDiagram
    %% Core Controller
    class MainController {
        <<Singleton>>
        +FileSystemModel* fileSystemModel
        -unique_ptr~FileSystemModel~ m_fileSystemModel
    }

    %% Qt Model
    class FileSystemModel {
        <<QAbstractItemModel>>
        +data(index, role)
        +index(row, col, parent)
        +addFolder()
        +addNote()
        -unique_ptr~FolderNode~ m_rootItem
    }

    %% Node Hierarchy
    class FileSystemNode {
        <<Abstract>>
        -QString m_name
        -FileSystemNode* m_parent
        +name()
        +getType()*
        +child(row)*
    }

    class FolderNode {
        -vector~unique_ptr~FileSystemNode~~ m_childItems
        +appendChild()
        +insertChild()
        +removeChild()
        +child(row)
    }

    class FileNode {
        <<Abstract>>
    }

    class NoteNode {
        -QString m_content
        +content()
        +setContent()
    }

    class TodoNode {
        -vector~TodoEntry~ m_todos
        +addTodo()
        +todos()
    }

    %% Relationships
    MainController *-- FileSystemModel : Owns
    FileSystemModel *-- FolderNode : Owns Root
    
    FileSystemNode <|-- FolderNode : Inherits
    FileSystemNode <|-- FileNode : Inherits
    FileNode <|-- NoteNode : Inherits
    FileNode <|-- TodoNode : Inherits

    FolderNode *-- FileSystemNode : Owns Children (unique_ptr)
```

### Key Interactions
1.  **Selection**: The GUI (Sidebar) talks to `FileSystemModel`.
2.  **Navigation**: `FileSystemModel` calls `FolderNode::child(row)` to generate Indexes.
3.  **Data**: `FileSystemModel::data()` casts the pointer to `NoteNode*` or `TodoNode*` to access specific getters (`content()`, `todos()`).
