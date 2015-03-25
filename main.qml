import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow {
    title: qsTr("LANMessenger")
    width: 640; maximumWidth: 640; minimumWidth: 640
    height: 480; maximumHeight: 480; minimumHeight: 480
    visible: true

    TextArea {
        id: chatText
        objectName: "chatText"
        anchors { top: parent.top; topMargin: 5; bottom: inputText.top; bottomMargin: 5; left: parent.left; leftMargin: 5; right: parent.right; rightMargin: 5 }
        readOnly: true
        wrapMode: TextEdit.Wrap

        function updateChat(message) {
            chatText.append(message);
        }
    }

    Button {
        id: sendButton
        objectName: "sendButton"
        anchors { bottom: parent.bottom; bottomMargin: 5; right: parent.right; rightMargin: 5 }
        text: qsTr("Send")

        signal notifyClick(string message)
        onClicked: {
            notifyClick(inputText.text)
            inputText.text = ""
        }
    }

    TextField {
        id: inputText
        height: sendButton.height
        anchors { bottom: parent.bottom; bottomMargin: 5; right: sendButton.left; rightMargin: 5; left: parent.left; leftMargin: 5 }
        onAccepted: sendButton.clicked()
    }
}
