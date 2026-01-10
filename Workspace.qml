pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import cirruspad

Page {
    id: root

    property list<var> openFiles

    function openFile(index) {
        var itemType = MainController.fileSystemModel.data(index, FileSystemModel.TypeRole);
        var file;
        if (itemType === "Todo") {
            file = MainController.fileSystemModel.data(index, FileSystemModel.ContentFileRole);
        } else if (itemType === "Note") {
            file = MainController.fileSystemModel.data(index, FileSystemModel.ContentFileRole);
        }
        if (!openFiles.includes(file)) {
            openFiles.push(file);
            stackLayout.currentIndex = openFiles.length - 1;
        }
    }

    function closeFile(file) {
        if (openFiles.includes(file)) {
            openFiles.splice(openFiles.indexOf(file));
            if (stackLayout.currentIndex > openFiles.length - 1) {
                stackLayout.currentIndex = openFiles.length - 1;
            }
        }
    }

    header: TabBar {
        id: tabBar

        Repeater {
            model: root.openFiles.length
            delegate: TabButton {
                id: tabButton
                required property int index
                text: root.openFiles[index] ? root.openFiles[index].fileName : ""
                onClicked: stackLayout.currentIndex = index
                checked: stackLayout.currentIndex === index

                Button {
                    id: closeButton
                    icon.source: "assets/icons/close.svg"
                    icon.color: palette.active.text
                    display: AbstractButton.IconOnly
                    flat: true
                    visible: tabButton.checked
                    onClicked: root.closeFile(root.openFiles[tabButton.index])

                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 0

                    width: height
                }
            }
        }
    }

    contentItem: StackLayout {
        id: stackLayout

        Repeater {
            model: root.openFiles.length
            delegate: FileView {
                id: fileView
                required property var index
                file: root.openFiles[index]

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    Component {
        id: todoView
        TodoView {}
    }

    Component {
        id: noteView
        NoteView {}
    }
}
