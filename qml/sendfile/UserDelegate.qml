import QtQuick 2.4

Item {
    id: root;

    property string clientAvatar: "qrc:/images/icons/avatar_placeholder_128.jpg";
    property string clientUuid: "";
    property string clientUserName: "";

    Rectangle {
        id: bg;
        anchors.fill: parent;
        color: "white";
    }

    Avatar {
        id: avatar;

        avatarSrc: root.clientAvatar;

        width: 48;
        height: 48;

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
            bottom: parent.verticalCenter;
        }

        font {
            bold: true;
            pixelSize: 16;
        }
    }

    SelectionStatus {
        id: selectionStatus;

//        selected: root.clientSelected;
        selected: false;

        width: 25;
        height: 25;

        anchors {
            verticalCenter: parent.verticalCenter;
            right: parent.right;
            rightMargin: 20;
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

    MouseArea {
        id: clickArea;
        anchors.fill: parent;
        onClicked: {
//            selectionStatus.state = "selected";
            userListModel.toggleSelected(root.clientUuid);
        }
    }
}
