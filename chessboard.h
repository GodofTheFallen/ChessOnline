#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Chessman/chessmen"
#include "Network/chessmessage.h"

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

class ChessBoard : public QWidget
{
    Q_OBJECT
private:
    bool Operating;
    QTimer Timer;
    int TIME_MAX, remTime;

    QList<ChessInfo> ChessInfoList;

    AbstractChessman *Board[64];

    AbstractChessman *ChosenChessman;

    QList<MoveInfo> MoveList;

    ChessMessage genMessage(MsgType);

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
    ChessColor Player;
    static const QPoint OPos;
    static const int GridWidth;
    static const double XScale;
    static const double YScale;
    static const QColor ColorCho,ColorChoE;
    static const QColor ColorMv,ColorMvE;
    static const QColor ColorCap,ColorCapE;
    static const QColor ColorPro,ColorProE;
    static const QColor ColorCas,ColorCasE;

    QList<ChessInfo> getChessInfoList() const;

    QString getRemBoard();

    int getTIME_MAX() const;

signals:
    void timeDisplay(int);
    void sendMsg(const ChessMessage &);
    void inCheck(bool);

public slots:
    void startOperating();

    void stopOperating();

    void setTIME_MAX(int value);

    void loadFromMsg();

    void saveToMsg();

    void receiveMsg(ChessMessage);

    void initialize();

private slots:
    void timeDec();

    void timeUseUp();

    void handleMove(MoveInfo);

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

};

#endif // CHESSBOARD_H
