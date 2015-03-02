import QtQuick 2.4

Item {
    id: root;

    property string clientUuid;
    property string clientUserName;

    Rectangle {
        anchors.fill: parent;
        color: "green";
    }

    Text {
        id: userNameText;
        text: root.clientUuid + " - " + root.clientUserName;
        color: "white";
        smooth: true;

        anchors {
            centerIn: parent;
        }
    }
}
