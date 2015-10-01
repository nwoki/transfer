import QtQuick 2.4

Item {
    id: root;

    property bool online: false;

    Rectangle {
        id: statusIndicator;

        width: root.width;
        height: root.height;

        smooth: true;

        anchors.centerIn: parent;
        color: "red";

        radius: 100;
    }

    onOnlineChanged: {
        console.log("CHANGED TO: " + root.online)
    }

    states: [
        State {
            name: "online";
            when: root.online === true;

            PropertyChanges {
                target: statusIndicator;
                color: "green";
            }
        },
        State {
            name: "offline";
            when: root.online === false;

            PropertyChanges {
                target: statusIndicator;
                color: "gray";
            }
        }
    ]
}
