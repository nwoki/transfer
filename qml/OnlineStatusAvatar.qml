import QtQuick 2.4

Item {
    id: root;

    property bool online: false;

    Rectangle {
        id: statusIndicator;

        width: root.width;
        height: root.height;

        smooth: true;
        radius: 100;

        anchors.centerIn: parent;
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
