import QtQuick 2.4

Item {
    id: root;

    property bool selected: false;

    state: root.selected ? "selected" : "unselected";

    Rectangle {
        id: selector;
        anchors.centerIn: parent;
        radius: 100;

        ColorAnimation on color {
            duration: 1000;
            to: "red";
        }
    }

    states: [
        State {
            name: "selected";
            PropertyChanges {
                target: selector;
                width: root.width;
                height: root.height;
                color: "red";
            }
        },
        State {
            name: "unselected";
            PropertyChanges {
                target: selector;
                width: 0;
                height: 0;
                color: "transparent";
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                properties: "opacity, width, height";
                duration: 400;
                easing.type: Easing.InOutBounce;
            }
        }
    ]

}
