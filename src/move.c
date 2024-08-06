#include "move.h"

const char *const piece_str2[] =
    {
        [NONE] = "NONE",
        [PAWN] = "PAWN",
        [BISHOP] = "BISHOP",
        [KNIGHT] = "KNIGHT",
        [ROOK] = "ROOK",
        [QUEEN] = "QUEEN",
        [KING] = "KING"};

bool pawnOnHomeRow(player_color curr_player, int position)
{
    uint64_t pawnBB = 1ULL << position;

    // testing
    //  printf("\n");
    //  printBitString(pawnBB);
    //  printf("\n");
    //  printBitString(white_pawn_home);
    //  printf("\n");
    //  printf("%llu", pawnBB & white_pawn_home);

    if (curr_player == WHITE)
        return (pawnBB & white_pawn_home) >= 1 ? 1 : 0;
    else if (curr_player == BLACK)
        return (pawnBB & black_pawn_home) >= 1 ? 1 : 0;
    else
    {
        fprintf(stderr, "Player color not found\n");
        exit(1);
    }
}

bool isEmptySquare(Board *board, int target)
{
    uint64_t mask = 1ULL << target;
    return ((mask & fullBitBoard(board)) >= 1) ? 0 : 1;
}

bool isLegalMove(Board *board, int target, player_color curr_player)
{

    // check board bounds
    if (target >= 64 | target < 0)
        return false;

    uint64_t mask = 1ULL << target;

    // if enteringCheck() --> false

    // if (!isEmptySquare(board, target))
    //     return false;

    // if target square is same color as curr_player = illegal move
    if (curr_player == WHITE)
        return ((whitePieces(board) & mask) >= 1) ? false : true;

    if (curr_player == BLACK)
        return ((blackPieces(board) & mask) >= 1) ? false : true;

    fprintf(stderr, "Player color not found. in isLegalMove\n");
    exit(1);
}

bool canCapture(Board *board, int target, player_color curr_player)
{
    uint64_t opp_pieces = (curr_player == WHITE) ? blackPieces(board) : whitePieces(board);

    uint64_t mask = 1ULL << target;

    if ((opp_pieces & mask) >= 1)
    {
        return true;
    }
    return false;
}

int *findPawnMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    // a pawn can always have, at most, 4 legal moves (1 forward, capture left/right, first move 2)
    int index = 0;
    int shift;

    // white pawn move = negative shift on position
    // black pawn move = positive shift on position

    shift = (curr_player == WHITE) ? -8 : 8;
    if (isEmptySquare(board, position + shift))
    {
        possible_moves[index] = shift;
        index++;
    }

    if (pawnOnHomeRow(curr_player, position) && (possible_moves[0] == 8 || possible_moves[0] == -8))
    {
        shift = (curr_player == WHITE) ? -16 : 16;

        if (isEmptySquare(board, position + shift))
        {
            possible_moves[index] = shift;
            index++;
        }
        else
            printf("found something in square %d ", position + shift);
    }

    shift = (curr_player == WHITE) ? -9 : 9;
    if (isLegalBishopMove(position, position + shift) && isLegalMove(board, position + shift, curr_player) && canCapture(board, position + shift, curr_player))
    {
        possible_moves[index] = shift;
        index++;
    };

    shift = (curr_player == WHITE) ? -7 : 7;
    if (isLegalBishopMove(position, position + shift) && isLegalMove(board, position + shift, curr_player) && canCapture(board, position + shift, curr_player))
    {
        possible_moves[index] = shift;
        index++;
    };

    return possible_moves;
}

bool isLegalBishopMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if (dX == dY)
        return true;
    else
        return false;
}
int bishopMoves[4][7] = {{7, 14, 21, 28, 35, 42, 49}, {-7, -14, -21, -28, -35, -42, -49}, {9, 18, 27, 36, 45, 54, 63}, {-9, -18, -27, -36, -45, -54, -63}};

int *findBishopMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = bishopMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalBishopMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            else
                break;

            if (!isEmptySquare(board, target))
                break;
            // end this route
        }
    }

    return possible_moves;
}

int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};

bool isLegalKnightMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX == 1 && dY == 2) ^ (dX == 2 && dY == 1))
        return true;
    else
        return false;
}

// int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};
int *findKnightMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    // i know starting position = 47

    // there are 4 legal moves (+6, +15, -10, -17). and 4 illegal moves.
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        // -17
        shift = horseMoves[i];
        // printf("%d, ", shift);

        // 30 (good)
        target = position + shift;

        // printf("\ntarget = %d", target);
        if (isLegalKnightMove(position, target) && isLegalMove(board, target, curr_player))
        {
            possible_moves[index] = shift;
            index++;
        }
    }

    return possible_moves;
}

bool isLegalRookMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
        return true;
    else
        return false;
}

int rookMoves[4][7] = {{1, 2, 3, 4, 5, 6, 7}, {-1, -2, -3, -4, -5, -6, -7}, {8, 16, 24, 32, 40, 48, 56}, {-8, -16, -24, -32, -40, -48, -56}};
int *findRookMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = rookMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalRookMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;

            if (!isEmptySquare(board, target))
                break;
        }
    }
    return possible_moves;
}

int *findQueenMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            shift = rookMoves[i][j];
            target = position + shift;

            if (isLegalRookMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;

            if (!isEmptySquare(board, target))
                break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = bishopMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalBishopMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;
        }
    }

    return possible_moves;
}

int kingMoves[] = {1, -1, 8, -8, 9, -9, 7, -7};
int *findKingMoves(Board *board, int *possible_moves, player_color curr_player, int position)
{
    // todo: look for castle opportunity

    int shift;
    int index = 0;
    int target = position;

    for (int i = 0; i < 8; i++)
    {
        shift = kingMoves[i];
        target = position + shift;

        if ((isLegalBishopMove(position, target) || isLegalRookMove(position, target)) && isLegalMove(board, target, curr_player))
        {
            possible_moves[index] = shift;
            index++;
        }
    }

    return possible_moves;
}

void makeMove(Board *board, int start, int shift, piece_type piece, player_color curr)
{
    // square we are moving the curr color piece to
    uint64_t mask = 1ULL << (start + shift);

    // bitboard of the piece we are moving
    uint64_t *board_p;

    // bitboard of the piece we are potentially capturing
    uint64_t *opp_board_p;

    // player_color opp_color_check = (curr == WHITE) ? BLACK : WHITE;
    player_color opp_color;

    switch (piece)
    {
    case PAWN:
        board_p = (curr == WHITE) ? &board->pawn_W : &board->pawn_B;
        break;
    case BISHOP:
        board_p = (curr == WHITE) ? &board->bishop_W : &board->bishop_B;
        break;
    case KNIGHT:
        board_p = (curr == WHITE) ? &board->knight_W : &board->knight_B;
        break;
    case ROOK:
        board_p = (curr == WHITE) ? &board->rook_W : &board->rook_B;
        break;
    case QUEEN:
        board_p = (curr == WHITE) ? &board->queen_W : &board->queen_B;
        break;
    case KING:
        board_p = (curr == WHITE) ? &board->king_W : &board->king_B;
        break;
    case NONE:
        break;
    default:
        break;
    }

    // identifies a piece -- and code will only run if opp_color != curr_player
    piece_type curr_piece = identifyPieceType(mask, board, &opp_color);

    if (curr_piece != NONE)
    {
        if (opp_color != curr)
        {
            printf("CAPTURING SQUARE %s FROM SQUARE %s, \n CHAD_PIECE = %s  |  BITCH_PIECE = %s\n", square_names[start + shift], square_names[start], piece_str2[piece], piece_str2[curr_piece]);
            if (curr == WHITE)
                printf("curr == WHITE");
            else
                printf("curr == BLACK");
            printf("\n");
            if (opp_color == WHITE)
                printf("opp == WHITE");
            else
                printf("opp == BLACK");

            printf("\n");

            // saves the bitboard we want to REMOVE a piece from
            switch (curr_piece)
            {
            case PAWN:
                opp_board_p = (opp_color == WHITE) ? &board->pawn_W : &board->pawn_B;
                break;
            case BISHOP:
                opp_board_p = (opp_color == WHITE) ? &board->bishop_W : &board->bishop_B;
                break;
            case KNIGHT:
                opp_board_p = (opp_color == WHITE) ? &board->knight_W : &board->knight_B;
                break;
            case ROOK:
                opp_board_p = (opp_color == WHITE) ? &board->rook_W : &board->rook_B;
                break;
            case QUEEN:
                opp_board_p = (opp_color == WHITE) ? &board->queen_W : &board->queen_B;
                break;
            case KING:
                opp_board_p = (opp_color == WHITE) ? &board->king_W : &board->king_B;
                break;
            case NONE:
                break;
            default:
                break;
            }

            // turn off original position
            *opp_board_p = *opp_board_p ^ mask;
        }
        else
            printf("COLOR CHECK FAILED\n");
    }
    // else
    // printf("NOT CAPTURING A PIECE\n");

    // turn off start position
    *board_p = *board_p ^ (1ULL << start);

    // mask = stores end position
    *board_p = *board_p | mask;
}

possible_move *getAllMovesFromCurrentBoard(Board *board, player_color curr_player, int **scalarArrays)
{
    possible_move *all_curr_player_moves = (possible_move *)malloc(sizeof(possible_move) * 256);
    piece_type curr_piece;
    player_color piece_color = curr_player;
    uint64_t square = 1ULL;
    int move_index = 0;

    // get all possible moves from every piece on the board.
    for (int i = 0; i < 64; i++)
    {
        curr_piece = identifyPieceType(square, board, &piece_color);

        // find moves based on the color of the current piece

        // printPossibleMoves(pawn_moves, i);

        if (curr_piece != NONE)
        {

            findMoves(board, curr_piece, piece_color, i, false);

            int *moves;
            int moves_count;
            switch (curr_piece)
            {
            case PAWN:
                moves = pawn_moves;
                moves_count = 4;
                break;
            case BISHOP:
                moves = bishop_moves;
                moves_count = 28;

                break;
            case KNIGHT:
                moves = knight_moves;
                moves_count = 8;

                break;
            case ROOK:
                moves = rook_moves;
                moves_count = 28;

                break;
            case QUEEN:
                moves = queen_moves;
                moves_count = 56;

                break;
            case KING:
                moves = king_moves;
                moves_count = 8;

                break;
            case NONE:
                break;
            }

            int index = 0;

            float eval = evaluateBoard(board, scalarArrays);

            while (moves[index] != 0 && index < moves_count)
            {
                all_curr_player_moves[move_index].start = i;

                all_curr_player_moves[move_index].shift = moves[index];

                all_curr_player_moves[move_index].piece = curr_piece;

                all_curr_player_moves[move_index].color = piece_color;

                Board fake_board = *board;
                makeMove(&fake_board, i, moves[index], curr_piece, piece_color);
                all_curr_player_moves[move_index].eval_after_move = evaluateBoard(&fake_board, scalarArrays) - eval;
                // makeMove(board, i + moves[index], -(moves[index]), curr_piece, piece_color);

                move_index++;
                index++;
            }

            free(moves);
        }

        square = square << 1;
    }
    return all_curr_player_moves;
}