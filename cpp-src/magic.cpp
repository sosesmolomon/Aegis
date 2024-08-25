#include <stdlib.h>
#include <stdio.h>

#include "print.h"
#include "init.h"
#include "magic.h"
#include "utils.h"

int RBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

int BBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

const u64 RMagic[64] = {
    0xa8002c000108020ULL,
    0x6c00049b0002001ULL,
    0x100200010090040ULL,
    0x2480041000800801ULL,
    0x280028004000800ULL,
    0x900410008040022ULL,
    0x280020001001080ULL,
    0x2880002041000080ULL,
    0xa000800080400034ULL,
    0x4808020004000ULL,
    0x2290802004801000ULL,
    0x411000d00100020ULL,
    0x402800800040080ULL,
    0xb000401004208ULL,
    0x2409000100040200ULL,
    0x1002100004082ULL,
    0x22878001e24000ULL,
    0x1090810021004010ULL,
    0x801030040200012ULL,
    0x500808008001000ULL,
    0xa08018014000880ULL,
    0x8000808004000200ULL,
    0x201008080010200ULL,
    0x801020000441091ULL,
    0x800080204005ULL,
    0x1040200040100048ULL,
    0x120200402082ULL,
    0xd14880480100080ULL,
    0x12040280080080ULL,
    0x100040080020080ULL,
    0x9020010080800200ULL,
    0x813241200148449ULL,
    0x491604001800080ULL,
    0x100401000402001ULL,
    0x4820010021001040ULL,
    0x400402202000812ULL,
    0x209009005000802ULL,
    0x810800601800400ULL,
    0x4301083214000150ULL,
    0x204026458e001401ULL,
    0x40204000808000ULL,
    0x8001008040010020ULL,
    0x8410820820420010ULL,
    0x1003001000090020ULL,
    0x804040008008080ULL,
    0x12000810020004ULL,
    0x1000100200040208ULL,
    0x430000a044020001ULL,
    0x280009023410300ULL,
    0xe0100040002240ULL,
    0x200100401700ULL,
    0x2244100408008080ULL,
    0x8000400801980ULL,
    0x2000810040200ULL,
    0x8010100228810400ULL,
    0x2000009044210200ULL,
    0x4080008040102101ULL,
    0x40002080411d01ULL,
    0x2005524060000901ULL,
    0x502001008400422ULL,
    0x489a000810200402ULL,
    0x1004400080a13ULL,
    0x4000011008020084ULL,
    0x26002114058042ULL,
};

const u64 BMagic[64] = {
    0x89a1121896040240ULL,
    0x2004844802002010ULL,
    0x2068080051921000ULL,
    0x62880a0220200808ULL,
    0x4042004000000ULL,
    0x100822020200011ULL,
    0xc00444222012000aULL,
    0x28808801216001ULL,
    0x400492088408100ULL,
    0x201c401040c0084ULL,
    0x840800910a0010ULL,
    0x82080240060ULL,
    0x2000840504006000ULL,
    0x30010c4108405004ULL,
    0x1008005410080802ULL,
    0x8144042209100900ULL,
    0x208081020014400ULL,
    0x4800201208ca00ULL,
    0xf18140408012008ULL,
    0x1004002802102001ULL,
    0x841000820080811ULL,
    0x40200200a42008ULL,
    0x800054042000ULL,
    0x88010400410c9000ULL,
    0x520040470104290ULL,
    0x1004040051500081ULL,
    0x2002081833080021ULL,
    0x400c00c010142ULL,
    0x941408200c002000ULL,
    0x658810000806011ULL,
    0x188071040440a00ULL,
    0x4800404002011c00ULL,
    0x104442040404200ULL,
    0x511080202091021ULL,
    0x4022401120400ULL,
    0x80c0040400080120ULL,
    0x8040010040820802ULL,
    0x480810700020090ULL,
    0x102008e00040242ULL,
    0x809005202050100ULL,
    0x8002024220104080ULL,
    0x431008804142000ULL,
    0x19001802081400ULL,
    0x200014208040080ULL,
    0x3308082008200100ULL,
    0x41010500040c020ULL,
    0x4012020c04210308ULL,
    0x208220a202004080ULL,
    0x111040120082000ULL,
    0x6803040141280a00ULL,
    0x2101004202410000ULL,
    0x8200000041108022ULL,
    0x21082088000ULL,
    0x2410204010040ULL,
    0x40100400809000ULL,
    0x822088220820214ULL,
    0x40808090012004ULL,
    0x910224040218c9ULL,
    0x402814422015008ULL,
    0x90014004842410ULL,
    0x1000042304105ULL,
    0x10008830412a00ULL,
    0x2520081090008908ULL,
    0x40102000a0a60140ULL,
};

// bishop attacks table [square][occupancies]
u64 bishop_attacks[64][512];

// rook attacks rable [square][occupancies]
u64 rook_attacks[64][4096];

// typedef struct sMagic
// {
//     u64 *attacks;
//     u64 mask; // attacks based on emptyboard
//     u64 magic;
//     int shift;
// }sMagic;

// m can be Bishop or Rook, and it will work the sae

u64 getRookAttacks(int sq, u64 occ)
{
    occ &= mRookTab[sq].mask;
    occ *= mRookTab[sq].magic;
    occ >>= mRookTab[sq].shift;
    return rook_attacks[sq][occ];
}
u64 getBishopAttacks(int sq, u64 occ)
{
    occ &= mBishopTab[sq].mask;
    occ *= mBishopTab[sq].magic;
    occ >>= mBishopTab[sq].shift;
    return bishop_attacks[sq][occ];
}

void initMagic(CBoard *board)
{
    init_sliders_attacks(board, 1);
    init_sliders_attacks(board, 0);
    // printf("Starting init() for magic.cpp\n");
    for (int sq = a1; sq <= h8; sq++)
    {
        mBishopTab[sq].attacks = bishop_attacks[sq];
        mBishopTab[sq].shift = (64 - BBits[sq]);
        mBishopTab[sq].magic = BMagic[sq];
        mBishopTab[sq].mask = board->bishopPosAttacks[sq];
    }
    for (int sq = a1; sq <= h8; sq++)
    {
        mRookTab[sq].attacks = rook_attacks[sq];
        mRookTab[sq].shift = (64 - RBits[sq]);
        mRookTab[sq].magic = RMagic[sq];
        mRookTab[sq].mask = board->rookPosAttacks[sq];
    }

    // for (int sq = a1; sq <= a4; sq++) {
    //     printf("{\n  square = %d\n", sq);
    //     printBitString(board->rookPosAttacks[sq]);
    //     printf("  mask = \n");
    //     printBitString(mRookTab[sq].mask);
    //     printf("  magic = \n");
    //     printBitString(mRookTab[sq].magic);
    //     printf("  attacks: \n");
    //     printBitString(*mRookTab[sq].attacks);
    //     printf("}\n");
    // }
}

u64 random_u64()

{
    u64 u1, u2, u3, u4;
    u1 = (u64)(random()) & 0xFFFF;
    u2 = (u64)(random()) & 0xFFFF;
    u3 = (u64)(random()) & 0xFFFF;
    u4 = (u64)(random()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

u64 random_u64_fewbits()
{
    return random_u64() & random_u64() & random_u64();
}

const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8};

int pop_1st_bit(u64 *bb)
{
    u64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

u64 index_to_u64(int index, int bits, u64 m)
{
    int i, j, k;
    u64 result = 0ULL;
    for (i = 0; i < bits; i++)
    {
        j = pop_1st_bit(&m);
        if (index & (1 << i))
            result |= (1ULL << j);
    }
    return result;
}

u64 rmask(int sq)
{
    u64 result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1; r <= 6; r++)
        result |= (1ULL << (fl + r * 8));
    for (r = rk - 1; r >= 1; r--)
        result |= (1ULL << (fl + r * 8));
    for (f = fl + 1; f <= 6; f++)
        result |= (1ULL << (f + rk * 8));
    for (f = fl - 1; f >= 1; f--)
        result |= (1ULL << (f + rk * 8));
    return result;
}

u64 bmask(int sq)
{
    u64 result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1, f = fl + 1; r <= 6 && f <= 6; r++, f++)
        result |= (1ULL << (f + r * 8));
    for (r = rk + 1, f = fl - 1; r <= 6 && f >= 1; r++, f--)
        result |= (1ULL << (f + r * 8));
    for (r = rk - 1, f = fl + 1; r >= 1 && f <= 6; r--, f++)
        result |= (1ULL << (f + r * 8));
    for (r = rk - 1, f = fl - 1; r >= 1 && f >= 1; r--, f--)
        result |= (1ULL << (f + r * 8));
    return result;
}

u64 ratt(int sq, u64 block)
{
    u64 result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1; r <= 7; r++)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (r = rk - 1; r >= 0; r--)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (f = fl + 1; f <= 7; f++)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    for (f = fl - 1; f >= 0; f--)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    return result;
}

u64 batt(int sq, u64 block)
{
    u64 result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1, f = fl + 1; r <= 7 && f <= 7; r++, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk + 1, f = fl - 1; r <= 7 && f >= 0; r++, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl + 1; r >= 0 && f <= 7; r--, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl - 1; r >= 0 && f >= 0; r--, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    return result;
}

int transform(u64 b, u64 magic, int bits)
{
#if defined(USE_32_BIT_MULTIPLICATIONS)
    return (unsigned)((int)b * (int)magic ^ (int)(b >> 32) * (int)(magic >> 32)) >> (32 - bits);
#else
    return (int)((b * magic) >> (64 - bits));
#endif
}

u64 find_magic(int sq, int m, int bishop)
{
    u64 mask, b[4096], a[4096], used[4096], magic;
    int i, j, k, n, mbits, fail;

    mask = bishop ? bmask(sq) : rmask(sq);
    n = countBits(mask);

    for (i = 0; i < (1 << n); i++)
    {
        b[i] = index_to_u64(i, n, mask);
        a[i] = bishop ? batt(sq, b[i]) : ratt(sq, b[i]);
    }
    for (k = 0; k < 100000000; k++)
    {
        magic = random_u64_fewbits();
        if (countBits((mask * magic) & 0xFF00000000000000ULL) < 6)
            continue;
        for (i = 0; i < 4096; i++)
            used[i] = 0ULL;
        for (i = 0, fail = 0; !fail && i < (1 << n); i++)
        {
            j = transform(b[i], magic, m);
            if (used[j] == 0ULL)
                used[j] = a[i];
            else if (used[j] != a[i])
                fail = 1;
        }
        if (!fail)
            return magic;
    }
    printf("***Failed***\n");
    return 0ULL;
}

// init slider piece's attack tables
void init_sliders_attacks(CBoard *b, int bishop)
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init bishop & rook masks
        // b->bishopPosAttacks[square]; and rook
        // bishop_masks[square] = mask_bishop_attacks(square);
        // rook_masks[square] = mask_rook_attacks(square);

        // init current mask
        u64 attack_mask = bishop ? b->bishopPosAttacks[square] : b->rookPosAttacks[square];

        // init relevant occupancy bit count
        int relevant_bits_count = countBits(attack_mask);

        // init occupancy indicies
        int occupancy_indicies = (1 << relevant_bits_count);

        // loop over occupancy indicies
        for (int index = 0; index < occupancy_indicies; index++)
        {
            // bishop
            if (bishop)
            {
                // init current occupancy variation
                u64 occupancy = index_to_u64(index, relevant_bits_count, attack_mask);

                // init magic index
                int magic_index = (occupancy * BMagic[square]) >> (64 - BBits[square]);

                // init bishop attacks
                bishop_attacks[square][magic_index] = batt(square, occupancy);
            }

            // rook
            else
            {
                // init current occupancy variation
                u64 occupancy = index_to_u64(index, relevant_bits_count, attack_mask);

                // init magic index
                int magic_index = (occupancy * RMagic[square]) >> (64 - RBits[square]);

                // init bishop attacks
                rook_attacks[square][magic_index] = ratt(square, occupancy);
            }
        }
    }
}

// int main()
// {
//     int square;
//     u64 magic;

//     CBoard *b = initCBoard();
//     initMagic(b);

//     Bitboard occ;

//     occ.b = 0ULL;
//     occ.set(c5);
//     occ.set(f2);
//     occ.set(g7);
//     occ.set(b2);
//     occ.set(g5);
//     occ.set(e2);
//     occ.set(e7);
//     printBitString(occ, e5);

//     printBitString(getAttacks(b, d4, mBishopTab, 1, occ), d4);

//     return 0;

//     printf("const u64 RMagic[64] = {\n");
//     for (square = 0; square < 64; square++)
//         printf("  0x%llxULL,\n", find_magic(square, RBits[square], 0));
//     printf("};\n\n");

//     printf("const u64 BMagic[64] = {\n");
//     for (square = 0; square < 64; square++)
//         printf("  0x%llxULL,\n", find_magic(square, BBits[square], 1));
//     printf("};\n\n");

//     return 0;
// }
