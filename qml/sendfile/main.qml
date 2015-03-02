import QtQuick 2.4

Item {
    id: root;

    width: 400;
    height: 400;

    Rectangle {
        color: "transparent";
        anchors.fill: parent;
        border.color: "red";
    }

    ListView {
        id: userList;

        model: userListModel;

        anchors {
            fill: parent;
        }

        height: parent.height;
        width: parent.width/2;


        delegate:
            UserDelegate {
                clientUuid: uuid;
                clientUserName: userName;

                height: 20;
                width: parent.width;
            }

        Rectangle {
            anchors.fill: parent;
            color: "transparent";
            border.color: "purple";
        }
    }
}
