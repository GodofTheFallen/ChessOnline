#ifndef CHESSMESSAGE_H
#define CHESSMESSAGE_H

#include <QJsonDocument>
#include <QJsonArray>
#include "Chessman/abstractchessman.h"

enum class MsgType {Load,Move,Submission,Timeout,Win,Draw};

class ChessMessage
{
private:
    QList<ChessInfo> chessmenInfo;
    MsgType type;

public:
    ChessMessage(const QList<ChessInfo> &_Q, const MsgType &_t = MsgType::Move);
    ChessMessage(QJsonDocument);
    MsgType getType() const;
    void setType(const MsgType &value);
    QList<ChessInfo> getChessmenInfo() const;
    QJsonDocument transToJson() const;
};

#endif // CHESSMESSAGE_H
