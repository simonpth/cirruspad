pragma ComponentBehavior: Bound
import QtQuick
import cirruspad

Item {
    id: root

    required property var file
    property string fileName: file.fileName
    property string filePath: file.filePath

    Loader {
        id: contentLoader

        anchors.fill: parent

        Component.onCompleted: {
            if (root.file instanceof NoteFile) {
                contentLoader.sourceComponent = noteViewComponent;
            } else if (root.file instanceof TodoFile) {
                contentLoader.sourceComponent = todoViewComponent;
            }
        }
    }

    Component {
        id: noteViewComponent
        NoteView {
            noteFile: root.file
        }
    }

    Component {
        id: todoViewComponent
        TodoView {
            todoFile: root.file
        }
    }
}
