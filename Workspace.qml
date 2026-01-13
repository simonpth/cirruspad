pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import cirruspad

Page {
    id: root

    topPadding: 0

    //SETTINGS PROPERTY
    property bool dragAndDropActive: true

    property list<var> openFiles

    function openFile(index) {
        var file = MainController.fileSystemModel.data(index, FileSystemModel.ContentFileRole);
        if (file && !openFiles.includes(file)) {
            openFiles.push(file);
            stackLayout.currentIndex = openFiles.length - 1;
        } else if (openFiles.includes(file)) {
            stackLayout.currentIndex = openFiles.indexOf(file);
        }
    }

    function closeFile(file) {
        if (openFiles.includes(file)) {
            openFiles.splice(openFiles.indexOf(file), 1);
            if (stackLayout.currentIndex > openFiles.length - 1) {
                stackLayout.currentIndex = Math.max(0, openFiles.length - 1);
            }
        }
    }

    //move function for js array
    function moveFile(from, to) {
        var item = openFiles[from];
        openFiles.splice(from, 1);

        if (to > from) {
            to--;
        }

        openFiles.splice(to, 0, item);
    }

    header: ListView {
        id: tabBarList
        height: 30
        orientation: ListView.Horizontal
        width: parent.width

        clip: true

        interactive: true

        model: root.openFiles
        delegate: TabButton {
            id: content

            required property var modelData
            required property int index

            width: content.implicitWidth + closeButton.width + 38
            height: 30

            MouseArea {
                id: dragHandler

                property point hotSpot

                anchors.fill: parent
                drag.target: root.dragAndDropActive ? content : null

                drag.axis: Drag.XAxis

                onReleased: {
                    if (content.Drag.target !== null) {
                        var from = content.index;
                        var to = from;
                        if (content.Drag.target.targetIndex !== undefined) {
                            to = content.Drag.target.targetIndex;
                        }
                        root.moveFile(from, to);
                        stackLayout.currentIndex = to > from ? to - 1 : to;
                    } else {
                        root.moveFile(content.index, content.index);
                        stackLayout.currentIndex = content.index;
                    }
                }

                onPressed: {
                    hotSpot = Qt.point(mouseX, mouseY);
                    stackLayout.currentIndex = content.index;
                }
            }

            Drag.active: dragHandler.drag.active
            Drag.source: content
            Drag.hotSpot: dragHandler.hotSpot

            background.opacity: dragHandler.drag.active ? 0.5 : 1.0

            z: dragHandler.drag.active ? 3 : 2

            text: modelData ? modelData.fileName : ""

            checked: stackLayout.currentIndex === index

            ToolButton {
                id: closeButton
                icon.source: "assets/icons/close.svg"
                icon.color: palette.text
                display: AbstractButton.IconOnly
                flat: true
                visible: stackLayout.currentIndex === content.index
                onClicked: {
                    root.closeFile(content.modelData);
                }

                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 4
                height: parent.height - 4
                width: height
            }

            DropArea {
                id: leftDropArea
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: parent.width / 2

                property int targetIndex: content.index

                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    width: 4

                    color: palette.active.text

                    visible: leftDropArea.containsDrag
                }
            }

            DropArea {
                id: rightDropArea
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                width: parent.width / 2

                property int targetIndex: content.index + 1

                Rectangle {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    width: 4

                    color: palette.active.text

                    visible: rightDropArea.containsDrag
                }
            }
        }
    }

    contentItem: StackLayout {
        id: stackLayout
        // currentIndex managed via openFile and tabs

        Repeater {
            model: root.openFiles
            delegate: FileView {
                id: fileView
                required property var modelData
                file: modelData

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
