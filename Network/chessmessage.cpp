#include "chessmessage.h"

ChessMessage::ChessMessage(const QList<ChessInfo> &_Q, const MsgType &_t): chessmenInfo(_Q), type(_t) {}

ChessMessage::ChessMessage(QJsonDocument JD)
{
    QJsonArray JA = JD.array();
    type = static_cast<MsgType>(JA.at(0).toInt());
    int length = JA.at(1).toInt();
    QJsonArray CIL = JA.at(2).toArray();
    for (int i = 0; i < length; ++i) {
        QJsonArray CIE = CIL.at(i).toArray();
        chessmenInfo.append(
                    ChessInfo(
                        static_cast<ChessType>(CIE.at(0).toInt()),
                        static_cast<ChessColor>(CIE.at(1).toInt()),
                        POS(CIE.at(2).toInt(),CIE.at(3).toInt()))
                    );
    }
}

MsgType ChessMessage::getType() const
{
    return type;
}

void ChessMessage::setType(const MsgType &value)
{
    type = value;
}

QList<ChessInfo> ChessMessage::getChessmenInfo() const
{
    return chessmenInfo;
}

QJsonDocument ChessMessage::transToJson() const
{
    QJsonDocument JD;
    QJsonArray JA, CIL;
    JA.append(static_cast<int>(type));
    JA.append(chessmenInfo.size());
    for (auto CI : chessmenInfo) {
        QJsonArray CIE;
        CIE.append(static_cast<int>(CI.getType()));
        CIE.append(static_cast<int>(CI.getColor()));
        CIE.append(CI.getPos().first);
        CIE.append(CI.getPos().second);
        CIL.append(CIE);
    }
    JA.append(CIL);
    JD.setArray(JA);
    return JD;
}
