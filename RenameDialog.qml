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

    property string currentName: ""
    property var targetIndex: null

    title: "Rename Item"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: Overlay.overlay
    popupType: Dialog.Native

    onAboutToShow: {
        nameField.text = currentName;
        nameField.selectAll();
        nameField.forceActiveFocus();
    }

    onAccepted: {
        if (nameField.text.trim() !== "" && root.targetIndex) {
            MainController.fileSystemModel.renameItem(root.targetIndex, nameField.text.trim());
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "New name:"
        }

        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: "Enter new name"

            Keys.onReturnPressed: {
                if (text.trim() !== "") {
                    root.accept();
                }
            }
        }
    }
}
