/*
    Copyright 2026, Simon Thal

    This file is part of CirrusPad.

    CirrusPad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CirrusPad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CirrusPad. If not, see <http://www.gnu.org/licenses/>.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import cirruspad

Dialog {
    id: root
    title: "Create New Item"
    modal: true
    anchors.centerIn: Overlay.overlay
    width: 300
    height: 250
    popupType: Dialog.Native

    required property var parentIndex

    // Custom standard buttons handling to enable/disable OK
    footer: DialogButtonBox {
        Button {
            text: "Cancel"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }
        Button {
            text: "Create"
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            enabled: stackLayout.currentIndex === 2 && nameField.text.length > 0
        }
    }

    property string selectedType: ""
    property string selectedFileType: ""

    onOpened: {
        // Reset state
        stackLayout.currentIndex = 0;
        selectedType = "";
        selectedFileType = "";
        nameField.text = "";
    }

    onAccepted: {
        if (stackLayout.currentIndex === 2) {
            if (selectedType === "Folder") {
                MainController.fileSystemModel.addFolder(parentIndex, nameField.text);
            } else if (selectedType === "File") {
                if (selectedFileType === "Note") {
                    MainController.fileSystemModel.addNote(parentIndex, nameField.text);
                } else if (selectedFileType === "Todo") {
                    MainController.fileSystemModel.addTodoList(parentIndex, nameField.text);
                }
            }
        }
    }

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: 0

        // Step 1: Type Selection
        GridLayout {
            rows: 3
            columns: 2
            uniformCellWidths: true
            Label {
                text: "What would you like to create?"
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.row: 0
                Layout.columnSpan: 2
            }

            Button {
                text: "Folder"
                icon.source: "assets/icons/folder.svg"
                icon.color: palette.active.text
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: width
                Layout.row: 1
                Layout.column: 0
                onClicked: {
                    root.selectedType = "Folder";
                    stackLayout.currentIndex = 2; // Skip to name
                }
            }

            Button {
                text: "File"
                icon.source: "assets/icons/note.svg"
                icon.color: palette.active.text
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: width
                Layout.row: 1
                Layout.column: 1
                onClicked: {
                    root.selectedType = "File";
                    stackLayout.currentIndex = 1; // Go to file type selection
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.row: 2
                Layout.columnSpan: 2
            }
        }

        // Step 2: File Type Selection
        GridLayout {
            rows: 4
            columns: 2
            uniformCellWidths: true
            Label {
                text: "Select file type:"
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.row: 0
                Layout.columnSpan: 2
            }
            Button {
                text: "Note"
                icon.source: "assets/icons/note.svg"
                icon.color: palette.active.text
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: width
                Layout.row: 1
                Layout.column: 0
                onClicked: {
                    root.selectedFileType = "Note";
                    stackLayout.currentIndex = 2; // Go to name
                }
            }
            Button {
                text: "Todo List"
                icon.source: "assets/icons/todo.svg"
                icon.color: palette.active.text
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: width
                Layout.row: 1
                Layout.column: 1
                onClicked: {
                    root.selectedFileType = "Todo";
                    stackLayout.currentIndex = 2; // Go to name
                }
            }

            Button {
                text: "Back"
                //flat: true
                Layout.row: 2
                Layout.columnSpan: 2
                onClicked: stackLayout.currentIndex = 0
            }
            Item {
                Layout.fillHeight: true
                Layout.row: 3
                Layout.columnSpan: 2
            }
        }

        // Step 3: Name Input
        GridLayout {
            rows: 4
            columns: 1
            uniformCellWidths: true
            Label {
                text: "Enter name:"
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.row: 0
            }

            TextField {
                id: nameField
                Layout.fillWidth: true
                Layout.row: 1
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                placeholderText: "Name..."
                focus: true
                onAccepted: {
                    if (text.length > 0)
                        root.accept();
                }
            }

            Button {
                text: "Back"
                //flat: true
                Layout.row: 2
                onClicked: {
                    if (root.selectedType === "Folder") {
                        stackLayout.currentIndex = 0;
                    } else {
                        stackLayout.currentIndex = 1;
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.row: 3
            }
        }
    }
}
