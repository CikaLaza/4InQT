import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "darkgreen"

    signal onTableClick(int column)

    signal movePlayed(int column, int row, int player)
    onMovePlayed: {
        if (row < 0) {
            console.log("onMoved: invalid move")
            return
        }

        // speedy clicking hack
        //while(droppingTimer.running == true) console.log("wait")

        //console.log("onMoved: row " + row + " column " + column)
        var newColor
        if (player == 1)
            newColor = "red"
        else
            newColor = "yellow"

        if (row == 0) {
            columnRepeater.itemAt(row * mainTableGrid.columns + column).circleColor = newColor
        }
        else {
            // setup dropping
            droppingCnt = 0

            droppingTimer.targetRow = row
            droppingTimer.column = column
            droppingTimer.running = true
            droppingTimer.color = newColor
        }
    }

    signal victory(int player)
    onVictory: {
        console.log("Victory")
    }

    property int droppingCnt: 0
    function onDroppingTimerTriggered()
    {
        //console.log("onDroppingTimerTriggered " + droppingCnt + " " + droppingTimer.targetRow)
        if (droppingCnt == droppingTimer.targetRow) {
            droppingTimer.running = false
            return
        }

        if (droppingCnt < mainTableGrid.rows)
            columnRepeater.itemAt((droppingCnt) * mainTableGrid.columns + droppingTimer.column).circleColor = "#00000000"
        droppingCnt++
        columnRepeater.itemAt(droppingCnt * mainTableGrid.columns + droppingTimer.column).circleColor = droppingTimer.color
    }

    Timer {
        id: droppingTimer
        interval: 50
        repeat: true
        running: false
        triggeredOnStart: true
        onTriggered: onDroppingTimerTriggered()

        property int currentRow: droppingCnt
        property int targetRow: 0
        property int column: 0
        property string color: ""
    }

    Rectangle {
        id: anchoredRectangle
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter // or, for example: anchors.right: parent.right

        color: "black"


        width: parent.width * 0.8
        height: parent.height * 0.8

        border.color: "black"
        border.width: 2
        radius: 5

        Grid {
            id: mainTableGrid
            rows: 6
            columns: 7
            spacing: 5

            anchors.fill: parent

            //anchors.margins: (width - (spacing * (columns - 1)) - (elemWidth * columns)) / 4
            anchors.margins: 5

            property int elemWidth: (width - (spacing * (columns - 1))) / columns
            property int elemHeight: (height - (spacing * (rows - 1))) / rows


            Repeater {
                id: columnRepeater
                model: parent.rows * parent.columns
                Rectangle
                {
                    width: mainTableGrid.elemWidth
                    height: mainTableGrid.elemHeight

                    color: "blue"
                    property color circleColor: "#00000000"

                    //Text { text: index; font.pointSize: 30; anchors.centerIn: parent }

                    Rectangle {
                        id: innerCircle
                        width: parent.width * 0.8
                        height: parent.height * 0.8
                        anchors.centerIn: parent
                        radius: width*0.5
                        color: parent.circleColor
                    }


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            mainWindow.onTableClick(index)
                        }
                    }
                }
            }
        }
    }
}
