#include "equalizer.h"
#include <QPropertyAnimation>
#include <QEventTransition>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QGraphicsScene>
#include <QDebug>

Equalizer::Equalizer(QWidget *parent) : QWidget(parent)
{


}

QRect Equalizer::nRect() const
{
    return mRect;
}

void Equalizer::setNRect(const QRect &rect)
{
    mRect = rect;
}

QRect Equalizer::nRect2() const
{
    return mRect2;
}

void Equalizer::setNRect2(const QRect &rect2)
{
    mRect2 = rect2;
}

QRect Equalizer::nRect3() const
{
    return mRect3;
}

void Equalizer::setNRect3(const QRect &rect3)
{
    mRect3 = rect3;
}

QRect Equalizer::nRect4() const
{
    return mRect4;
}

void Equalizer::setNRect4(const QRect &rect4)
{
    mRect4 = rect4;
}

QRect Equalizer::nRect5() const
{
    return mRect5;
}

void Equalizer::setNRect5(const QRect &rect5)
{
    mRect5 = rect5;
}

void Equalizer::setNRect6(const QRect &rect6)
{
    mRect6 = rect6;
}

QRect Equalizer::nRect6() const
{
    return mRect6;
}


void Equalizer::setNRect7(const QRect &rect7)
{
    mRect7 = rect7;
}

QRect Equalizer::nRect7() const
{
    return mRect7;
}

QRect Equalizer::nRect8() const
{
    return mRect8;
}


void Equalizer::setNRect8(const QRect &rect8)
{
    mRect8 = rect8;
}


QRect Equalizer::nRect9() const
{
    return mRect9;
}

void Equalizer::setNRect9(const QRect &rect9)
{
    mRect9 = rect9;
}

QRect Equalizer::nRect10() const
{
    return mRect10;
}

void Equalizer::setNRect10(const QRect &rect10)
{
    mRect10 = rect10;
}

QRect Equalizer::nRect11() const
{
    return mRect11;
}


void Equalizer::setNRect11(const QRect &rect11)
{
    mRect11 = rect11;
}

QRect Equalizer::nRect12() const
{
    return mRect12;
}

void Equalizer::setNRect12(const QRect &rect12)
{
    mRect12 = rect12;
}

QRect Equalizer::nRect13() const
{
    return mRect13;
}

void Equalizer::setNRect13(const QRect &rect13)
{
    mRect13 = rect13;
}

QRect Equalizer::nRect14() const
{
    return mRect14;
}

void Equalizer::setNRect14(const QRect &rect14)
{
    mRect14 = rect14;
}

QRect Equalizer::nRect15() const
{
    return mRect15;
}

void Equalizer::setNRect15(const QRect &rect15)
{
    mRect15 = rect15;
}

QRect Equalizer::nRect16() const
{
    return mRect16;
}

void Equalizer::setNRect16(const QRect &rect16)
{
    mRect16 = rect16;
}

QRect Equalizer::nRect17() const
{
    return mRect17;
}

void Equalizer::setNRect17(const QRect &rect17)
{
    mRect17 = rect17;
}

QRect Equalizer::nRect18() const
{
    return mRect18;
}

void Equalizer::setNRect18(const QRect &rect18)
{
    mRect18 = rect18;
}

QRect Equalizer::nRect19() const
{
    return mRect19;
}

void Equalizer::setNRect19(const QRect &rect19)
{
    mRect19 = rect19;
}

QRect Equalizer::nRect20() const
{
    return mRect20;
}

void Equalizer::setNRect20(const QRect &rect20)
{
    mRect20 = rect20;
}

QRect Equalizer::nRect21() const
{
    return mRect21;
}

void Equalizer::setNRect21(const QRect &rect21)
{
    mRect21 = rect21;
}


void Equalizer::setNRect22(const QRect &rect22)
{
    mRect22 = rect22;
}

QRect Equalizer::nRect22() const
{
    return mRect22;
}


void Equalizer::setNRect23(const QRect &rect23)
{
    mRect23 = rect23;
}

QRect Equalizer::nRect23() const
{
    return mRect23;
}

QRect Equalizer::nRect24() const
{
    return mRect24;
}

void Equalizer::setNRect24(const QRect &rect24)
{
    mRect24 = rect24;
}


//////

QLine Equalizer::nLine() const
{
    return mLine;
}

void Equalizer::setNLine(const QLine &line)
{
    mLine = line;
}

QLine Equalizer::nLine2() const
{
    return mLine2;
}

void Equalizer::setNLine2(const QLine &line2)
{
    mLine2  = line2;
}

QLine Equalizer::nLine3() const
{
    return mLine3;
}

void Equalizer::setNLine3(const QLine &line3)
{
    mLine3  = line3;
}

QLine Equalizer::nLine4() const
{
    return mLine4;
}

void Equalizer::setNLine4(const QLine &line4)
{
    mLine4  = line4;
}

QLine Equalizer::nLine5() const
{
    return mLine5;
}

void Equalizer::setNLine5(const QLine &line5)
{
    mLine5 = line5;
}

QLine Equalizer::nLine6() const
{
    return mLine6;
}

void Equalizer::setNLine6(const QLine &line6)
{
    mLine6  = line6;
}

QLine Equalizer::nLine7() const
{
    return mLine7;
}

void Equalizer::setNLine7(const QLine &line7)
{
    mLine7  = line7;
}

QLine Equalizer::nLine8() const
{
    return mLine8;
}

void Equalizer::setNLine8(const QLine &line8)
{
    mLine8  = line8;
}

QLine Equalizer::nLine9() const
{
    return mLine9;
}

void Equalizer::setNLine9(const QLine &line9)
{
    mLine9  = line9;
}

QLine Equalizer::nLine10() const
{
    return mLine10;
}

void Equalizer::setNLine10(const QLine &line10)
{
    mLine10  = line10;
}

QLine Equalizer::nLine11() const
{
    return mLine11;
}

void Equalizer::setNLine11(const QLine &line11)
{
    mLine11  = line11;
}

QLine Equalizer::nLine12() const
{
    return mLine12;
}

void Equalizer::setNLine12(const QLine &line12)
{
    mLine12  = line12;
}

QLine Equalizer::nLine13() const
{
    return mLine13;
}

void Equalizer::setNLine13(const QLine &line13)
{
    mLine13  = line13;
}

QLine Equalizer::nLine14() const
{
    return mLine14;
}


void Equalizer::setNLine14(const QLine &line14)
{
    mLine14  = line14;
}


QLine Equalizer::nLine15() const
{
    return mLine15;
}

void Equalizer::setNLine15(const QLine &line15)
{
    mLine15  = line15;
}

QLine Equalizer::nLine16() const
{
    return mLine16;
}

void Equalizer::setNLine16(const QLine &line16)
{
    mLine16  = line16;
}

QLine Equalizer::nLine17() const
{
    return mLine17;
}

void Equalizer::setNLine17(const QLine &line17)
{
    mLine17  = line17;
}

QLine Equalizer::nLine18() const
{
    return mLine18;
}

void Equalizer::setNLine18(const QLine &line18)
{
    mLine18  = line18;
}

QLine Equalizer::nLine19() const
{
    return mLine19;
}


void Equalizer::setNLine19(const QLine &line19)
{
    mLine19  = line19;
}

QLine Equalizer::nLine20() const
{
    return mLine20;
}

void Equalizer::setNLine20(const QLine &line20)
{
    mLine20  = line20;
}

QLine Equalizer::nLine21() const
{
    return mLine21;
}

void Equalizer::setNLine21(const QLine &line21)
{
    mLine21  = line21;
}

QLine Equalizer::nLine22() const
{
    return mLine22;
}

void Equalizer::setNLine22(const QLine &line22)
{
    mLine22  = line22;
}

QLine Equalizer::nLine23() const
{
    return mLine23;
}

void Equalizer::setNLine23(const QLine &line23)
{
    mLine23  = line23;
}

QLine Equalizer::nLine24() const
{
    return mLine24;
}

void Equalizer::setNLine24(const QLine &line24)
{
    mLine24  = line24;
}

int * Equalizer::setChunk(double *chunk, int * startYArr)
{

    if(startYArr == NULL)
    {
        startYArr = new int[24];
        for(int i = 0 ; i < 24 ; i++)
        {
            *(startYArr + i) = 150;
        }
    }


    int xCoordinateArray[24];
    int yCoordinateArray[24];

    for(int i = 0 ; i < 24 ; i++)
    {
        yCoordinateArray[i] = *(chunk + i) * 5;
        xCoordinateArray[i] = 100 + i*25;
    }

    qDebug() << "Chunk initialized";
    for(int i = 0 ; i < 24 ; i++)
    {
        qDebug() << *(startYArr + i);
    }



    QPropertyAnimation *animation = new QPropertyAnimation(this , "nrect");
    animation->setDuration(2000);
    animation->setStartValue(QRect(xCoordinateArray[0] , *(startYArr + 0) , 10 , 10));
    animation->setEndValue(QRect(xCoordinateArray[0] , 150 - yCoordinateArray[0] , 10 , 10));
    animation->start();
    connect(animation, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation2 = new QPropertyAnimation(this , "nrect2");
    animation2->setDuration(2000);
    animation2->setStartValue(QRect(xCoordinateArray[1] , *(startYArr + 1), 10 , 10));
    animation2->setEndValue(QRect(xCoordinateArray[1] ,  150 - yCoordinateArray[1] , 10 , 10));
    animation2->start();
    connect(animation2, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation3 = new QPropertyAnimation(this , "nrect3");
    animation3->setDuration(2000);
    animation3->setStartValue(QRect(xCoordinateArray[2] , *(startYArr +2) , 10 , 10));
    animation3->setEndValue(QRect(xCoordinateArray[2] ,  150 - yCoordinateArray[2] , 10 , 10));
    animation3->start();
    connect(animation3, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation4 = new QPropertyAnimation(this , "nrect4");
    animation4->setDuration(2000);
    animation4->setStartValue(QRect(xCoordinateArray[3] , *(startYArr + 3) , 10 , 10));
    animation4->setEndValue(QRect(xCoordinateArray[3] ,  150 - yCoordinateArray[3] , 10 , 10));
    animation4->start();
    connect(animation4, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation5 = new QPropertyAnimation(this , "nrect5");
    animation5->setDuration(2000);
    animation5->setStartValue(QRect(xCoordinateArray[4] , *(startYArr + 4) , 10 , 10));
    animation5->setEndValue(QRect(xCoordinateArray[4] ,  150 - yCoordinateArray[4] , 10 , 10));
    animation5->start();
    connect(animation5, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation6 = new QPropertyAnimation(this , "nrect6");
    animation6->setDuration(2000);
    animation6->setStartValue(QRect(xCoordinateArray[5] , *(startYArr + 5) , 10 , 10));
    animation6->setEndValue(QRect(xCoordinateArray[5] ,  150 - yCoordinateArray[5] , 10 , 10));
    animation6->start();
    connect(animation6, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation7 = new QPropertyAnimation(this , "nrect7");
    animation7->setDuration(2000);
    animation7->setStartValue(QRect(xCoordinateArray[6] , *(startYArr + 6) , 10 , 10));
    animation7->setEndValue(QRect(xCoordinateArray[6] ,  150 - yCoordinateArray[6] , 10 , 10));
    animation7->start();
    connect(animation7, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation8 = new QPropertyAnimation(this , "nrect8");
    animation8->setDuration(2000);
    animation8->setStartValue(QRect(xCoordinateArray[7] , *(startYArr + 7) , 10 , 10));
    animation8->setEndValue(QRect(xCoordinateArray[7] ,  150 - yCoordinateArray[7] , 10 , 10));
    animation8->start();
    connect(animation8, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation9 = new QPropertyAnimation(this , "nrect9");
    animation9->setDuration(2000);
    animation9->setStartValue(QRect(xCoordinateArray[8] , *(startYArr + 8) , 10 , 10));
    animation9->setEndValue(QRect(xCoordinateArray[8] ,  150 - yCoordinateArray[8] , 10 , 10));
    animation9->start();
    connect(animation9, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation10 = new QPropertyAnimation(this , "nrect10");
    animation10->setDuration(2000);
    animation10->setStartValue(QRect(xCoordinateArray[9] , *(startYArr + 9) , 10 , 10));
    animation10->setEndValue(QRect(xCoordinateArray[9] ,  150 - yCoordinateArray[9] , 10 , 10));
    animation10->start();
    connect(animation10, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation11 = new QPropertyAnimation(this , "nrect11");
    animation11->setDuration(2000);
    animation11->setStartValue(QRect(xCoordinateArray[10] , *(startYArr + 10) , 10 , 10));
    animation11->setEndValue(QRect(xCoordinateArray[10] ,  150 - yCoordinateArray[10] , 10 , 10));
    animation11->start();
    connect(animation11, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation12 = new QPropertyAnimation(this , "nrect12");
    animation12->setDuration(2000);
    animation12->setStartValue(QRect(xCoordinateArray[11] , *(startYArr + 11) , 10 , 10));
    animation12->setEndValue(QRect(xCoordinateArray[11] ,  150 - yCoordinateArray[11] , 10 , 10));
    animation12->start();
    connect(animation12, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation13 = new QPropertyAnimation(this , "nrect13");
    animation13->setDuration(2000);
    animation13->setStartValue(QRect(xCoordinateArray[12] , *(startYArr + 12) , 10 , 10));
    animation13->setEndValue(QRect(xCoordinateArray[12] ,  150 - yCoordinateArray[12] , 10 , 10));
    animation13->start();
    connect(animation3, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation14 = new QPropertyAnimation(this , "nrect14");
    animation14->setDuration(2000);
    animation14->setStartValue(QRect(xCoordinateArray[13] , *(startYArr + 13) , 10 , 10));
    animation14->setEndValue(QRect(xCoordinateArray[13] ,  150 - yCoordinateArray[13] , 10 , 10));
    animation14->start();
    connect(animation14, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation15 = new QPropertyAnimation(this , "nrect15");
    animation15->setDuration(2000);
    animation15->setStartValue(QRect(xCoordinateArray[14] , *(startYArr + 14) , 10 , 10));
    animation15->setEndValue(QRect(xCoordinateArray[14] ,  150 - yCoordinateArray[14] , 10 , 10));
    animation15->start();
    connect(animation15, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation16 = new QPropertyAnimation(this , "nrect16");
    animation16->setDuration(2000);
    animation16->setStartValue(QRect(xCoordinateArray[15] , *(startYArr + 15) , 10 , 10));
    animation16->setEndValue(QRect(xCoordinateArray[15] ,  150 - yCoordinateArray[15] , 10 , 10));
    animation16->start();
    connect(animation16, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation17 = new QPropertyAnimation(this , "nrect17");
    animation17->setDuration(2000);
    animation17->setStartValue(QRect(xCoordinateArray[16] , *(startYArr + 16) , 10 , 10));
    animation17->setEndValue(QRect(xCoordinateArray[16] ,  150 - yCoordinateArray[16] , 10 , 10));
    animation17->start();
    connect(animation17, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation18 = new QPropertyAnimation(this , "nrect18");
    animation18->setDuration(2000);
    animation18->setStartValue(QRect(xCoordinateArray[17] , *(startYArr + 17) , 10 , 10));
    animation18->setEndValue(QRect(xCoordinateArray[17] ,  150 - yCoordinateArray[17] , 10 , 10));
    animation18->start();
    connect(animation18, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation19 = new QPropertyAnimation(this , "nrect19");
    animation19->setDuration(2000);
    animation19->setStartValue(QRect(xCoordinateArray[18] , *(startYArr + 18) , 10 , 10));
    animation19->setEndValue(QRect(xCoordinateArray[18] ,  150 - yCoordinateArray[18] , 10 , 10));
    animation19->start();
    connect(animation19, &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animation20 = new QPropertyAnimation(this , "nrect20");
    animation20->setDuration(2000);
    animation20->setStartValue(QRect(xCoordinateArray[19] , *(startYArr + 19) , 10 , 10));
    animation20->setEndValue(QRect(xCoordinateArray[19] ,  150 - yCoordinateArray[19] , 10 , 10));
    animation20->start();
    connect(animation20, &QPropertyAnimation::valueChanged , [=](){update();});

//////////////////
    QPropertyAnimation *animationLine = new QPropertyAnimation(this , "nline");
    animationLine->setDuration(2000);
    animationLine->setStartValue(QLine(xCoordinateArray[0] + 5 , 150 , xCoordinateArray[1] , 150));
    animationLine->setEndValue(QLine(xCoordinateArray[0] + 5 , 150 - yCoordinateArray[0] , xCoordinateArray[1] ,  150 - yCoordinateArray[1]));
    animationLine->start();
    connect(animationLine , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine2 = new QPropertyAnimation(this , "nline2");
    animationLine2->setDuration(2000);
    animationLine2->setStartValue(QLine(xCoordinateArray[1] + 5 , 150 , xCoordinateArray[2] ,150));
    animationLine2->setEndValue(QLine( xCoordinateArray[1] + 5 , 150 - yCoordinateArray[1]  ,xCoordinateArray[2] , 150 - yCoordinateArray[2]));
    animationLine2->start();
    connect(animationLine2 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine3 = new QPropertyAnimation(this , "nline3");
    animationLine3->setDuration(2000);
    animationLine3->setStartValue(QLine(xCoordinateArray[2] + 5 , 150 , xCoordinateArray[3] , 150));
    animationLine3->setEndValue(QLine( xCoordinateArray[2] + 5 , 150 - yCoordinateArray[2]  ,xCoordinateArray[3] , 150 - yCoordinateArray[3]));
    animationLine3->start();
    connect(animationLine3 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine4 = new QPropertyAnimation(this , "nline4");
    animationLine4->setDuration(2000);
    animationLine4->setStartValue(QLine(xCoordinateArray[3] + 5 , 150 , xCoordinateArray[4] , 150));
    animationLine4->setEndValue(QLine( xCoordinateArray[3] + 5 , 150 - yCoordinateArray[3]  ,xCoordinateArray[4] , 150 - yCoordinateArray[4]));
    animationLine4->start();
    connect(animationLine4 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine5 = new QPropertyAnimation(this , "nline5");
    animationLine5->setDuration(2000);
    animationLine5->setStartValue(QLine(xCoordinateArray[4] + 5 , 150 , xCoordinateArray[5] , 150));
    animationLine5->setEndValue(QLine( xCoordinateArray[4] + 5 , 150 - yCoordinateArray[4]  ,xCoordinateArray[5] , 150 - yCoordinateArray[5]));
    animationLine5->start();
    connect(animationLine5 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine6 = new QPropertyAnimation(this , "nline6");
    animationLine6->setDuration(2000);
    animationLine6->setStartValue(QLine(xCoordinateArray[5] + 5 , 150 , xCoordinateArray[6] , 150));
    animationLine6->setEndValue(QLine( xCoordinateArray[5] + 5 , 150 - yCoordinateArray[5]  ,xCoordinateArray[6] , 150 - yCoordinateArray[6]));
    animationLine6->start();
    connect(animationLine6 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine7 = new QPropertyAnimation(this , "nline7");
    animationLine7->setDuration(2000);
    animationLine7->setStartValue(QLine(xCoordinateArray[6] + 5 , 150 , xCoordinateArray[7] , 150));
    animationLine7->setEndValue(QLine( xCoordinateArray[6] + 5 , 150 - yCoordinateArray[6]  ,xCoordinateArray[7] , 150 - yCoordinateArray[7]));
    animationLine7->start();
    connect(animationLine7 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine8 = new QPropertyAnimation(this , "nline8");
    animationLine8->setDuration(2000);
    animationLine8->setStartValue(QLine(xCoordinateArray[7] + 5 , 150 , xCoordinateArray[8] , 150));
    animationLine8->setEndValue(QLine( xCoordinateArray[7] + 5 , 150 - yCoordinateArray[7]  ,xCoordinateArray[8] , 150 - yCoordinateArray[8]));
    animationLine8->start();
    connect(animationLine8 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine9 = new QPropertyAnimation(this , "nline9");
    animationLine9->setDuration(2000);
    animationLine9->setStartValue(QLine(xCoordinateArray[8] + 5 , 150 , xCoordinateArray[9] , 150));
    animationLine9->setEndValue(QLine( xCoordinateArray[8] + 5 , 150 - yCoordinateArray[8]  ,xCoordinateArray[9] , 150 - yCoordinateArray[9]));
    animationLine9->start();
    connect(animationLine9 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine10 = new QPropertyAnimation(this , "nline10");
    animationLine10->setDuration(2000);
    animationLine10->setStartValue(QLine(xCoordinateArray[9] + 5 , 150 , xCoordinateArray[10] , 150));
    animationLine10->setEndValue(QLine( xCoordinateArray[9] + 5 , 150 - yCoordinateArray[9]  ,xCoordinateArray[10] , 150 - yCoordinateArray[10]));
    animationLine10->start();
    connect(animationLine10 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine11 = new QPropertyAnimation(this , "nline11");
    animationLine11->setDuration(2000);
    animationLine11->setStartValue(QLine(xCoordinateArray[10] + 5 , 150 , xCoordinateArray[11] , 150));
    animationLine11->setEndValue(QLine( xCoordinateArray[10] + 5 , 150 - yCoordinateArray[10]  ,xCoordinateArray[11] , 150 - yCoordinateArray[11]));
    animationLine11->start();
    connect(animationLine11 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine12 = new QPropertyAnimation(this , "nline12");
    animationLine12->setDuration(2000);
    animationLine12->setStartValue(QLine(xCoordinateArray[11] + 5 , 150 , xCoordinateArray[12] , 150));
    animationLine12->setEndValue(QLine( xCoordinateArray[11] + 5 , 150 - yCoordinateArray[11]  ,xCoordinateArray[12] , 150 - yCoordinateArray[12]));
    animationLine12->start();
    connect(animationLine12 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine13 = new QPropertyAnimation(this , "nline13");
    animationLine13->setDuration(2000);
    animationLine13->setStartValue(QLine(xCoordinateArray[12] + 5 , 150 , xCoordinateArray[13] , 150));
    animationLine13->setEndValue(QLine( xCoordinateArray[12] + 5 , 150 - yCoordinateArray[12]  ,xCoordinateArray[13] , 150 - yCoordinateArray[13]));
    animationLine13->start();
    connect(animationLine13 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine14 = new QPropertyAnimation(this , "nline14");
    animationLine14->setDuration(2000);
    animationLine14->setStartValue(QLine(xCoordinateArray[13] + 5 , 150 , xCoordinateArray[14] , 150));
    animationLine14->setEndValue(QLine( xCoordinateArray[13] + 5 , 150 - yCoordinateArray[13]  ,xCoordinateArray[14] , 150 - yCoordinateArray[14]));
    animationLine14->start();
    connect(animationLine14 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine15 = new QPropertyAnimation(this , "nline15");
    animationLine15->setDuration(2000);
    animationLine15->setStartValue(QLine(xCoordinateArray[14] + 5 , 150 , xCoordinateArray[15] , 150));
    animationLine15->setEndValue(QLine( xCoordinateArray[14] + 5 , 150 - yCoordinateArray[14]  ,xCoordinateArray[15] , 150 - yCoordinateArray[15]));
    animationLine15->start();
    connect(animationLine15 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine16 = new QPropertyAnimation(this , "nline16");
    animationLine16->setDuration(2000);
    animationLine16->setStartValue(QLine(xCoordinateArray[15] + 5 , 150 , xCoordinateArray[16] , 150));
    animationLine16->setEndValue(QLine( xCoordinateArray[15] + 5 , 150 - yCoordinateArray[15]  ,xCoordinateArray[16] , 150 - yCoordinateArray[16]));
    animationLine16->start();
    connect(animationLine16 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine17 = new QPropertyAnimation(this , "nline17");
    animationLine17->setDuration(2000);
    animationLine17->setStartValue(QLine(xCoordinateArray[16] + 5 , 150 , xCoordinateArray[17] , 150));
    animationLine17->setEndValue(QLine( xCoordinateArray[16] + 5 , 150 - yCoordinateArray[16]  ,xCoordinateArray[17] , 150 - yCoordinateArray[17]));
    animationLine17->start();
    connect(animationLine11 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine18 = new QPropertyAnimation(this , "nline18");
    animationLine18->setDuration(2000);
    animationLine18->setStartValue(QLine(xCoordinateArray[17] + 5 , 150 , xCoordinateArray[18] , 150));
    animationLine18->setEndValue(QLine( xCoordinateArray[17] + 5 , 150 - yCoordinateArray[17]  ,xCoordinateArray[18] , 150 - yCoordinateArray[18]));
    animationLine18->start();
    connect(animationLine18 , &QPropertyAnimation::valueChanged , [=](){update();});

    QPropertyAnimation *animationLine19 = new QPropertyAnimation(this , "nline19");
    animationLine19->setDuration(2000);
    animationLine19->setStartValue(QLine(xCoordinateArray[18] + 5 , 150 , xCoordinateArray[19] , 150));
    animationLine19->setEndValue(QLine( xCoordinateArray[18] + 5 , 150 - yCoordinateArray[18]  ,xCoordinateArray[19] , 150 - yCoordinateArray[19]));
    animationLine19->start();
    connect(animationLine19 , &QPropertyAnimation::valueChanged , [=](){update();});

    return &yCoordinateArray[0];
}




void Equalizer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QRect ellipse(mRect);
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse);

    QRect ellipse2(mRect2);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse2);

    QRect ellipse3(mRect3);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse3);

    QRect ellipse4(mRect4);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse4);

    QRect ellipse5(mRect5);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse5);

    QRect ellipse6(mRect6);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse6);

    QRect ellipse7(mRect7);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse7);

    QRect ellipse8(mRect8);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse8);

    QRect ellipse9(mRect9);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse9);

    QRect ellipse10(mRect10);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse10);

    QRect ellipse11(mRect11);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse11);

    QRect ellipse12(mRect12);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse12);

    QRect ellipse13(mRect13);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse13);

    QRect ellipse14(mRect14);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse14);

    QRect ellipse15(mRect15);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse15);

    QRect ellipse16(mRect16);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse16);

    QRect ellipse17(mRect17);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse17);

    QRect ellipse18(mRect18);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse18);

    QRect ellipse19(mRect19);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse19);

    QRect ellipse20(mRect20);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse20);

    QRect ellipse21(mRect21);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse21);

    QRect ellipse22(mRect22);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse22);

    QRect ellipse23(mRect23);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse23);

    QRect ellipse24(mRect24);
    painter.setBrush(Qt::red);
    painter.drawEllipse(ellipse24);


    QLine line(mLine);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line);

    QLine line2(mLine2);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line2);

    QLine line3(mLine3);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line3);

    QLine line4(mLine4);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line4);

    QLine line5(mLine5);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line5);

    QLine line6(mLine6);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line6);

    QLine line7(mLine7);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line7);

    QLine line8(mLine8);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line8);

    QLine line9(mLine9);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line9);

    QLine line10(mLine10);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line10);

    QLine line11(mLine11);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line11);

    QLine line12(mLine12);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line12);

    QLine line13(mLine13);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line13);

    QLine line14(mLine14);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line14);

    QLine line15(mLine15);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line15);

    QLine line16(mLine16);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line16);

    QLine line17(mLine17);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line17);

    QLine line18(mLine18);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line18);

    QLine line19(mLine19);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line19);

    QLine line20(mLine20);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line20);

    QLine line21(mLine21);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line21);

    QLine line22(mLine22);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line22);

    QLine line23(mLine23);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line23);

    QLine line24(mLine24);
    painter.setPen(QPen(Qt::blue , 2));
    painter.drawLine(line24);

}
