#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <QWidget>
#include <QPixmap>
#include <QMargins>
#include <QPainter>
#include <QRect>
#include <iostream>
#include <QThread>
#include <QCoreApplication>

using namespace std;


class Equalizer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect nrect READ nRect WRITE setNRect)
    Q_PROPERTY(QRect nrect2 READ nRect2 WRITE setNRect2)
    Q_PROPERTY(QRect nrect3 READ nRect3 WRITE setNRect3)
    Q_PROPERTY(QRect nrect4 READ nRect4 WRITE setNRect4)
    Q_PROPERTY(QRect nrect5 READ nRect5 WRITE setNRect5)
    Q_PROPERTY(QRect nrect6 READ nRect6 WRITE setNRect6)
    Q_PROPERTY(QRect nrect7 READ nRect7 WRITE setNRect7)
    Q_PROPERTY(QRect nrect8 READ nRect8 WRITE setNRect8)
    Q_PROPERTY(QRect nrect9 READ nRect9 WRITE setNRect9)
    Q_PROPERTY(QRect nrect10 READ nRect10 WRITE setNRect10)
    Q_PROPERTY(QRect nrect11 READ nRect11 WRITE setNRect11)
    Q_PROPERTY(QRect nrect12 READ nRect12 WRITE setNRect12)
    Q_PROPERTY(QRect nrect13 READ nRect13 WRITE setNRect13)
    Q_PROPERTY(QRect nrect14 READ nRect14 WRITE setNRect14)
    Q_PROPERTY(QRect nrect15 READ nRect15 WRITE setNRect15)
    Q_PROPERTY(QRect nrect16 READ nRect16 WRITE setNRect16)
    Q_PROPERTY(QRect nrect17 READ nRect17 WRITE setNRect17)
    Q_PROPERTY(QRect nrect18 READ nRect18 WRITE setNRect18)
    Q_PROPERTY(QRect nrect19 READ nRect19 WRITE setNRect19)
    Q_PROPERTY(QRect nrect20 READ nRect20 WRITE setNRect20)


    Q_PROPERTY(QLine nline READ nline WRITE setNline)
    Q_PROPERTY(QLine nline2 READ nline2 WRITE setNline2)
    Q_PROPERTY(QLine nline3 READ nline3 WRITE setNline3)
    Q_PROPERTY(QLine nline4 READ nline4 WRITE setNline4)
    Q_PROPERTY(QLine nline5 READ nline5 WRITE setNline5)
    Q_PROPERTY(QLine nline6 READ nline6 WRITE setNline6)
    Q_PROPERTY(QLine nline7 READ nline7 WRITE setNline7)
    Q_PROPERTY(QLine nline8 READ nline8 WRITE setNline8)
    Q_PROPERTY(QLine nline9 READ nline9 WRITE setNline9)
    Q_PROPERTY(QLine nline10 READ nline10 WRITE setNline10)
    Q_PROPERTY(QLine nline11 READ nline11 WRITE setNline11)
    Q_PROPERTY(QLine nline12 READ nline12 WRITE setNline12)
    Q_PROPERTY(QLine nline13 READ nline13 WRITE setNline13)
    Q_PROPERTY(QLine nline14 READ nline14 WRITE setNline14)
    Q_PROPERTY(QLine nline15 READ nline15 WRITE setNline15)
    Q_PROPERTY(QLine nline16 READ nline16 WRITE setNline16)
    Q_PROPERTY(QLine nline17 READ nline17 WRITE setNline17)
    Q_PROPERTY(QLine nline18 READ nline18 WRITE setNline18)
    Q_PROPERTY(QLine nline19 READ nline19 WRITE setNline19)



public:
    explicit Equalizer(QWidget *parent = 0);

    QRect nRect() const;
    void setNRect(const QRect &rect);

    QRect nRect2() const;
    void setNRect2(const QRect &rect2);

    QRect nRect3() const;
    void setNRect3(const QRect &rect3);

    QRect nRect4() const;
    void setNRect4(const QRect &rect4);

    QRect nRect5() const;
    void setNRect5(const QRect &rect5);

    QRect nRect6() const;
    void setNRect6(const QRect &rect6);

    QRect nRect7() const;
    void setNRect7(const QRect &rect7);

    QRect nRect8() const;
    void setNRect8(const QRect &rect8);

    QRect nRect9() const;
    void setNRect9(const QRect &rect9);

    QRect nRect10() const;
    void setNRect10(const QRect &rect10);

    QRect nRect11() const;
    void setNRect11(const QRect &rect11);

    QRect nRect12() const;
    void setNRect12(const QRect &rect12);

    QRect nRect13() const;
    void setNRect13(const QRect &rect13);

    QRect nRect14() const;
    void setNRect14(const QRect &rect14);

    QRect nRect15() const;
    void setNRect15(const QRect &rect15);

    QRect nRect16() const;
    void setNRect16(const QRect &rect16);

    QRect nRect17() const;
    void setNRect17(const QRect &rect17);

    QRect nRect18() const;
    void setNRect18(const QRect &rect18);

    QRect nRect19() const;
    void setNRect19(const QRect &rect19);

    QRect nRect20() const;
    void setNRect20(const QRect &rect20);

    QRect nRect21() const;
    void setNRect21(const QRect &rect21);

    QRect nRect22() const;
    void setNRect22(const QRect &rect22);

    QRect nRect23() const;
    void setNRect23(const QRect &rect23);

    QRect nRect24() const;
    void setNRect24(const QRect &rect24);
///
    QLine nLine() const;
    void setNLine(const QLine &line);

    QLine nLine2() const;
    void setNLine2(const QLine &line2);

    QLine nLine3() const;
    void setNLine3(const QLine &line3);

    QLine nLine4() const;
    void setNLine4(const QLine &line4);

    QLine nLine5() const;
    void setNLine5(const QLine &line5);

    QLine nLine6() const;
    void setNLine6(const QLine &line6);

    QLine nLine7() const;
    void setNLine7(const QLine &line7);

    QLine nLine8() const;
    void setNLine8(const QLine &line8);

    QLine nLine9() const;
    void setNLine9(const QLine &line9);

    QLine nLine10() const;
    void setNLine10(const QLine &line10);

    QLine nLine11() const;
    void setNLine11(const QLine &line11);

    QLine nLine12() const;
    void setNLine12(const QLine &line12);

    QLine nLine13() const;
    void setNLine13(const QLine &line13);

    QLine nLine14() const;
    void setNLine14(const QLine &line14);

    QLine nLine15() const;
    void setNLine15(const QLine &line15);

    QLine nLine16() const;
    void setNLine16(const QLine &line16);

    QLine nLine17() const;
    void setNLine17(const QLine &line17);

    QLine nLine18() const;
    void setNLine18(const QLine &line18);

    QLine nLine19() const;
    void setNLine19(const QLine &line19);


    void setChunk(double *chunk, int * startYArr);


private:

    QRect mRect;
    QRect mRect2;
    QRect mRect3;
    QRect mRect4;
    QRect mRect5;
    QRect mRect6;
    QRect mRect7;
    QRect mRect8;
    QRect mRect9;
    QRect mRect10;
    QRect mRect11;
    QRect mRect12;
    QRect mRect13;
    QRect mRect14;
    QRect mRect15;
    QRect mRect16;
    QRect mRect17;
    QRect mRect18;
    QRect mRect19;
    QRect mRect20;



    QLine mLine;
    QLine mLine2;
    QLine mLine3;
    QLine mLine4;
    QLine mLine5;
    QLine mLine6;
    QLine mLine7;
    QLine mLine8;
    QLine mLine9;
    QLine mLine10;
    QLine mLine11;
    QLine mLine12;
    QLine mLine13;
    QLine mLine14;
    QLine mLine15;
    QLine mLine16;
    QLine mLine17;
    QLine mLine18;
    QLine mLine19;



private:

    double chunk[24];
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // EQUALIZER_H
