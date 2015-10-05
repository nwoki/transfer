import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: root;

    property string clientUuid: "";
    property string clientUserName: "";
    property bool clientOnlineStatus;


    OnlineStatusAvatar {
        id: avatar;

        online: root.clientOnlineStatus;
        width: 24;
        height: 24;

        anchors {
            left: parent.left;
            leftMargin: 10;
            verticalCenter: parent.verticalCenter;
        }
    }

    Text {
        id: userNameText;
        text: root.clientUserName;
        color: "black";
        smooth: true;

        anchors {
            left: avatar.right;
            leftMargin: 20;
            verticalCenter: parent.verticalCenter;
        }

        font {
            bold: true;
            pixelSize: 16;
        }
    }

    Button {
        id: sendFileButton;

        height: 25;
        width: 25;

        anchors {
            right: parent.right;
            rightMargin: 10;
            verticalCenter: parent.verticalCenter;
        }

        onClicked: {
            if (!root.clientOnlineStatus) {
                console.log("Client not online. Not showing menu");
            } else {
                console.log("Let's send this file");
                userListModel.sendFileToUser(root.clientUuid);
            }
        }
    }

    Rectangle {
        id: seperator;
        height: 1;
        width: (parent.width/3)*2;
        color: "black";

        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter;
        }
    }

    // Connect with the user object for online status
    Connections {
        target: userListModel.user(root.clientUuid);

        onOnlineStatusChanged: {
            root.clientOnlineStatus = userListModel.user(root.clientUuid).online;
        }
    }
}
