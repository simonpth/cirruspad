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
import cirruspad

Item {
    id: root
    property var currentIndex // QModelIndex

    Loader {
        id: contentLoader
        anchors.fill: parent
        source: {
            if (!root.currentIndex || !root.currentIndex.valid)
                return "";

            var itemType = MainController.fileSystemModel.data(root.currentIndex, FileSystemModel.TypeRole);

            if (itemType === "Note")
                return "NoteView.qml";
            if (itemType === "Todo")
                return "TodoView.qml";
            return "";
        }
    }

    // Binding content to the loaded item
    Binding {
        target: contentLoader.item
        property: "modelIndex"
        value: root.currentIndex
        when: contentLoader.status === Loader.Ready
    }
}
