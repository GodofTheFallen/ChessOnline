#include "chessmessage.h"

ChessMessage::ChessMessage(const QList<ChessInfo> &_Q, const MsgType &_t): chessmenInfo(_Q), type(_t) {}

MsgType ChessMessage::getType() const
{
    return type;
}

void ChessMessage::setType(const MsgType &value)
{
    type = value;
}

