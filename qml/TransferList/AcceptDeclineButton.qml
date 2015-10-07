import QtQuick 2.4

Item {
    id: root;

    signal clicked;
    property string color: "grey";

    Rectangle {
        id: botton;

        color: root.color;
        radius: 100;
        smooth: true;
        anchors.fill: parent;
    }

    MouseArea {
        id: mouseArea;
        anchors.fill: parent;

        onClicked: {
            root.clicked();
        }
    }
}
