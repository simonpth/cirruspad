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
pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import cirruspad

Item {
    id: root

    // Signal when a file (leaf node) is selected
    signal fileSelected(var index)

    // The DelegateModel allows us to "filter" the tree to just the children of 'rootIndex'
    DelegateModel {
        id: visualModel
        model: MainController.fileSystemModel
        rootIndex: helper.currentRootIndex

        delegate: ItemDelegate {
            required property var model
            required property int index

            width: parent.width
            text: model.name
            icon.name: model.isFolder ? "folder" : (model.type === "Note" ? "text-x-generic" : "checkbox")

            onClicked: {
                if (model.isFolder) {
                    // Drill down
                    helper.currentRootIndex = visualModel.modelIndex(index);
                } else {
                    // Open file
                    root.fileSelected(visualModel.modelIndex(index));
                }
            }
        }
    }

    // QtObject helper to store the current root index (because DelegateModel properties can be tricky)
    QtObject {
        id: helper
        property var currentRootIndex: MainController.fileSystemModel.rootIndex
        // Note: The model's generic "invalid" index usually represents the abstract root.
    }

    ColumnLayout {
        anchors.fill: parent

        // Header / Up Button
        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 5

            Button {
                text: "Back"
                enabled: helper.currentRootIndex && helper.currentRootIndex.valid
                onClicked: {
                    helper.currentRootIndex = MainController.fileSystemModel.parent(helper.currentRootIndex);
                }
            }

            Label {
                text: (helper.currentRootIndex && helper.currentRootIndex.valid) ? MainController.fileSystemModel.data(helper.currentRootIndex, Qt.DisplayRole) : "Home"
                Layout.fillWidth: true
                elide: Text.ElideRight
                font.bold: true
            }

            Button {
                text: "+"
                onClicked: {
                    // MVP: Just add a folder for testing
                    MainController.fileSystemModel.addFolder(helper.currentRootIndex, "New Folder");
                }
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: visualModel
        }
    }
}
