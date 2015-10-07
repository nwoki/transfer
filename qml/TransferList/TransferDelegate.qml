import QtQuick 2.4


Item {
    id: root;

    property string transferFileName;
    property string transferUserName;
    property string transferUserUuid;


    AcceptDeclineButton {
        id: acceptButton;

        color: "#8FFF78";
        height: 20;
        width: 20;

        onClicked: {
            // TODO start transfer
        }

        anchors {
            right: declineButton.left;
            rightMargin: 5;
            verticalCenter: parent.verticalCenter;
        }
    }

    AcceptDeclineButton {
        id: declineButton;

        color: "#FF7777";
        height: 20;
        width: 20;

        onClicked: {
            // TODO cancel transfer
        }

        anchors {
            right: parent.right;
            rightMargin: 10;
            verticalCenter: parent.verticalCenter;
        }
    }

    Text {
        text: "<b>" + root.transferFileName + "</b> from <b>" + root.transferUserName + "</b>";
        color: "black";
        smooth: true;
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        anchors {
            left: parent.left;
            leftMargin: 10;
            verticalCenter: parent.verticalCenter;
            right: acceptButton.left;
            rightMargin: 10;
        }
    }
}
