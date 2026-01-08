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
import cirruspad

Item {
    id: root
    property var modelIndex

    ListView {
        anchors.fill: parent
        anchors.margins: 10
        model: root.modelIndex && root.modelIndex.valid ? MainController.fileSystemModel.data(root.modelIndex, FileSystemModel.TodosRole) : []

        delegate: CheckBox {
            required property var modelData

            width: ListView.view.width
            text: modelData.text
            checked: modelData.checked
            onToggled: {
                MainController.fileSystemModel.setTodoChecked(root.modelIndex, modelData.index, checked);
            }
        }
    }
}
