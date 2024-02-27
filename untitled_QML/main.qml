import QtQuick 2.12
import QtQuick.Window 2.12

/*
  *
  *
  *
  *
  *
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    //Item用于布局及组合其他元素,所有可视化元素的基础对象
    //Row以行的形式排列
    //Rectangle矩形框
    //Text文本
    //image图像
    //MouseArea//鼠标区域

    Item {
        id: name
        Row{             //Row以行的形式排列
            spacing: 10  //设置以下矩形框之间的间距
            Rectangle{   //Rectangle矩形框
                //z:1    //默认是0现在是1就出来了  z代表堆叠次序
                id:rect1
                width: 100
                height: 100
                color: "red"
            }//rect1 end
            //
            Rectangle{
                id:rect2
                width: 100
                height: 100
                color: "blue"
            }//redct2 end
            //
            Rectangle{
                id:rect3
                width: 100
                height: 100
                border.width: 5      //设置边界宽度
                border.color: "red"  //设置边界颜色
                color: "green"
                radius: 50           //设置圆角半径
            }//redct3 end
            //以下为画个圆
            Rectangle{
                id:rect4
                width: 100
                height: width
                radius: width/2    //设置圆角半径
                color: "yellow"
            }//rect4 end

        }//Row end

        //        Rectangle{
        //            z:1  //默认是0现在是1就出来了
        //            id:rect1
        //            width: 100
        //            height: 100
        //            color: "red"
        //        }//rect1
        //        //
        //        Rectangle{
        //            id:rect2
        //            width: 100
        //            height: 100
        //            color: "green"
        //        }//redct2
    }//Item end
/////////////////////////////////////////////////////////
    //text的使用方法
    Item {
        id: name1
        //anchors.centerIn: parent   //将子控件放在父控件中心
        x:0     //位置
        y:100   //位置
        Column  //盒子
        {
            Text {
                id: text1
                text: qsTr("你好哇,李银河")
                color: "#303030"
                font.family: "Ubuntu"
                font.pixelSize: 28
            }//text end
            Text {
                id: text2
                text: qsTr("HelloWorld")
                color: "#303030"
                font.family: "Ubuntu"
                font.pixelSize: 28
            }//text end
        }//Column end
    }//item  end
    ////////////////////////////////////////////////////////////////
    //image的使用方法
    Item {
        id: nam2
        x:0 ;y:180
        Row{  //Row横向排列
             spacing: 5  //设置间距
             Image {
                 id: imag1
                 width: 150
                 height: 250
                 source: "qrc:/image/111.jpg"
             } //image end
             Image {
                 id: imag2
                 width: 150
                 height: 250
                 source: "qrc:/image/222.jpg"
             } //image end
             Image {
                 id: imag3
                 width: 150
                 height: 250
                 source: "qrc:/image/333.jpg"
             } //image end
             Image {
                 id: imag4
                 width: 200
                 height: 250
                 source: "qrc:/image/444.jpg"
             } //image end

        }//Row end

    }//item end



}//window end
  *
  *
  *
  *
  *
*/

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Window {
    id:wind
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool isClicked01:false  //QML使用property关键字定义属性
    property bool isClicked02:false  //QML使用property关键字定义属性
    property bool isClicked03:false  //QML使用property关键字定义属性

    //设置三个按钮
    Row
    {
        //anchors.centerIn: parent  //将子控件放在父控件中心
        x:160;y:0
        spacing: 20   //间距
        Rectangle{
            id:rect1
            width: 100
            height: 40
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //加外边框
            border.color: "red"
            border.width: 5
            radius: 10  //半径
            //鼠标点击
            MouseArea  //鼠标点击
            {
                anchors.fill: parent
                onClicked:
                {
                    isClicked01=!isClicked01;
                    if(isClicked01)
                    {
                        text4.visible=true;
                        wind.color="red";  //将窗口颜色改为红色
                    }
                    else
                    {
                        text4.visible=flase;
                        wind.color="green"; //将窗口颜色改为白色
                    }
                }//onClicked end
            }//MouseArea end


        }//rect1 end
        Rectangle{
            id:rect2
            width: 100
            height: 40
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //加外边框
            border.color: "red"
            border.width: 5
            radius: 10  //半径
        }//rect2 end
        Rectangle{
            id:rect3
            width: 100
            height: 40
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //加外边框
            border.color: "red"
            border.width: 5
            radius: 10  //半径
        }//rect3 end
    }//row end
    ////////////////////////////按钮上显示文字////////////////////////////////
    Row
    {
        x:185;y:10
        spacing:70
        Text {
            id: text1
            text: qsTr("按钮1")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 20
        }
        Text {
            id: text2
            text: qsTr("按钮2")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 20
        }
        Text {
            id: text3
            text: qsTr("按钮3")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 20
        }

    }//row end
    ////////////////////////////////设置文本///////////////////////////////////
    Column
    {
        x:50;y:50
        spacing: 20
        Text {
            id: text4
            text: qsTr("red")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 28
            visible: false  //设置默认不可见，点击按钮出现
        }
        Text {
            id: text5
            text: qsTr("green")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 28
            visible: false  //设置默认不可见，点击按钮出现
        }
        Text {
            id: text6
            text: qsTr("blue")
            color: "#303030"
            font.family: "Ubuntu"
            font.pixelSize: 28
            visible: false  //设置默认不可见，点击按钮出现
        }

    }//Column end
    ////////////////////////////////设置三个圆形////////////////////////////////
    Row
    {
        x:150;y:175
        spacing: 20   //间距
        Rectangle{
            id:rect4
            width: 100
            height:width
            radius: width/2  //半径
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //外边框
            border.color: "red"
            border.width: 5
        }//rect1 end
        Rectangle{
            id:rect5
            width: 100
            height: width
            radius: width/2  //半径
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //加外边框
            border.color: "red"
            border.width: 5
        }//rect2 end
        Rectangle{
            id:rect6
            width: 100
            height: width
            radius: width/2  //半径
            color: "red"
            gradient: Gradient   //渐变色
            {
                GradientStop { position:0.0;color:"lightsteelblue"}
                GradientStop { position:1.0;color:"slategray"}
            }
            //加外边框
            border.color: "red"
            border.width: 5
        }//rect3 end

    }//row end
    ////////////////////////最后一个矩形////////////////////////////
    Rectangle{
        x:250;y:300
        id:rect7
        width: 150
        height:150
        color: "red"
        gradient: Gradient   //渐变色
        {
            GradientStop { position:0.0;color:"lightsteelblue"}
            GradientStop { position:1.0;color:"slategray"}

        }
    }//rect7 end

}//window end
