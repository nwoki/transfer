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
//                clientSelected: selected;

                height: 60;
                width: parent.width;

                Component.onCompleted: {
                    console.log("SELECTED IS: " + selected);
                }

//                 onSelectedChanged: {
//                     console.log("SELECTED IS: " + selected);
//                 }
            }

        Rectangle {
            anchors.fill: parent;
            color: "transparent";
            border.color: "purple";
        }
    }
}
