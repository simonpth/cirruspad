pragma ComponentBehavior: Bound
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

Item {
    id: root
    property TodoFile todoFile

    ListView {
        id: todoList
        anchors.fill: parent
        anchors.margins: 10
        model: root.todoFile ? root.todoFile.todos : []
        spacing: 5
        clip: true

        delegate: Item {
            id: todoDelegate
            required property var modelData
            required property int index
            width: todoList.width
            height: todoLayout.implicitHeight

            RowLayout {
                id: todoLayout
                anchors.fill: parent
                spacing: 5

                CheckBox {
                    id: todoCheckbox
                    checked: todoDelegate.modelData.checked
                    onToggled: {
                        root.todoFile.setTodoChecked(todoDelegate.index, checked);
                    }
                }

                TextField {
                    Layout.fillWidth: true
                    text: todoDelegate.modelData.text
                    font.strikeout: todoDelegate.modelData.checked
                    opacity: todoDelegate.modelData.checked ? 0.6 : 1.0
                    background: null
                    verticalAlignment: TextInput.AlignVCenter
                    onEditingFinished: {
                        root.todoFile.setTodoText(todoDelegate.index, text);
                    }
                }
            }
        }

        footer: Item {
            width: todoList.width
            height: footerLayout.implicitHeight + 5
            visible: root.todoFile !== null

            RowLayout {
                id: footerLayout
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.rightMargin: 5
                spacing: 5

                CheckBox {
                    id: footerCheckbox
                    enabled: false
                    opacity: 0.3
                }

                TextField {
                    id: newTodoInput
                    Layout.fillWidth: true
                    placeholderText: "Add a new todo..."
                    background: null
                    verticalAlignment: TextInput.AlignVCenter
                    onAccepted: {
                        if (text.trim() !== "") {
                            root.todoFile.addTodo(text);
                            text = "";
                        }
                    }
                }

                Button {
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 40
                    Layout.alignment: Qt.AlignCenter
                    icon.source: "assets/icons/checkmark.svg"
                    icon.color: palette.active.text
                    display: AbstractButton.IconOnly
                    flat: true
                    visible: newTodoInput.text.trim() !== ""
                    onClicked: newTodoInput.accepted()
                }
            }
        }
    }

    Button {
        id: deleteButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        width: 50
        height: 50
        icon.source: "assets/icons/trash.svg"
        icon.color: palette.active.text
        display: AbstractButton.IconOnly
        ToolTip.visible: hovered
        ToolTip.text: "Delete checked todos"

        onClicked: {
            if (root.todoFile) {
                root.todoFile.deleteCheckedTodos();
            }
        }
    }
}
