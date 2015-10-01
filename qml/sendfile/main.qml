import QtQuick 2.4

Item {
    id: root;

    width: 300;
    height: 400;

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

                height: 30;
                width: parent.width;
            }
    }
}
