#ifndef CHESSINFO_H
#define CHESSINFO_H

#include <QObject>

enum class ChessType {KING,QUEEN,BISHOP,KNIGHT,ROOK,PAWN};

enum class MoveType{MOVE,CAPTURE,PROMOTION,CASTLING};

enum class ChessColor{BLACK,WHITE};

typedef QPair<int,int> POS;

typedef QPair<MoveType,POS> MoveInfo;

class ChessInfo
{
private:
    ChessType type;
    ChessColor color;
    POS pos;

public:
    ChessInfo(const ChessType &_type, const ChessColor &_color, const POS & _pos);
    ChessType getType() const;
    ChessColor getColor() const;
    POS getPos() const;
};

#endif // CHESSINFO_H
