// Generated by Flexc++ V2.01.00 on Sun, 13 Mar 2016 12:24:33 +0530

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// $insert class_ih
#include "Scanner.ih"


    // s_ranges__: use (unsigned) characters as index to obtain
    //           that character's range-number.
    //           The range for EOF is defined in a constant in the
    //           class header file
size_t const ScannerBase::s_ranges__[] =
{
     0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 7, 7, 8, 9,10,10,11,12,13,14,15,16,17,18,
    19,19,19,19,19,19,20,20,21,21,22,23,24,25,25,26,27,28,28,29,30,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,32,33,33,34,35,36,36,37,38,39,40,41,
    42,43,44,45,46,47,48,48,49,50,51,52,53,53,54,55,56,57,58,59,60,61,61,62,63,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,
};

    // s_dfa__ contains the rows of *all* DFAs ordered by start state.  The
    // enum class StartCondition__ is defined in the baseclass header
    // StartCondition__::INITIAL is always 0.  Each entry defines the row to
    // transit to if the column's character range was sensed. Row numbers are
    // relative to the used DFA, and d_dfaBase__ is set to the first row of
    // the subset to use.  The row's final two values are respectively the
    // rule that may be matched at this state, and the rule's FINAL flag. If
    // the final value equals FINAL (= 1) then, if there's no continuation,
    // the rule is matched. If the BOL flag (8) is also set (so FINAL + BOL (=
    // 9) is set) then the rule only matches when d_atBOL is also true.
int const ScannerBase::s_dfa__[][68] =
{
    // INITIAL
    {-1, 1,-1, 2, 1, 3, 4, 2, 5, 2, 2, 2, 6, 2, 7, 8, 9,10,11,11,
         11, 2,12,13,14, 2,15,15,15,15,15,15,15,15, 2, 2, 2,15, 2,15,
         15,15,15,16,17,15,15,18,15,15,15,15,15,15,19,20,15,15,21,22,
         15,15, 2,23, 2,-1,    -1, -1},  // 0
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     0, -1},  // 1
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 2
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 3
    {-1,25,25,-1,25,-1,26,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,25,25,25,
         25,-1,-1,-1,-1,-1,25,25,25,25,25,25,25,25,-1,25,-1,-1,-1,25,
         25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,
         25,25,-1,-1,-1,-1,    23, -1},  // 4
    {-1,-1,-1,-1,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 5
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 6
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 7
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,30,30,
         30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 8
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 9
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,33,33,33,
         11,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,35,-1,-1,-1,-1,-1,-1,-1,
         34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         35,-1,-1,-1,-1,-1,    19, -1},  // 10
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,11,11,11,
         11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    19, -1},  // 11
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,36,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 12
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 13
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    23, -1},  // 14
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 15
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,39,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 16
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,40,15,15,41,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 17
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,42,15,15,15,15,15,15,43,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 18
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,44,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 19
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,45,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 20
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,46,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 21
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,47,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 22
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,48,-1,-1,    23, -1},  // 23
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     8, -1},  // 24
    {-1,25,25,-1,25,-1,26,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,25,25,25,
         25,-1,-1,-1,-1,-1,25,25,25,25,25,25,25,25,-1,25,-1,-1,-1,25,
         25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,
         25,25,-1,-1,-1,-1,    -1, -1},  // 25
    {-1,25,25,-1,25,-1,26,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,25,25,25,
         25,-1,-1,-1,-1,-1,25,25,25,25,25,25,25,25,-1,25,-1,-1,-1,25,
         25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,
         25,25,-1,-1,-1,-1,    21, -1},  // 26
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    10, -1},  // 27
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    11, -1},  // 28
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    17, -1},  // 29
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,30,30,
         30,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 30
    {-1,31,31,31,31,31,31,31,31,31,31,50,31,31,31,31,31,31,31,31,
         31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
         31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
         31,31,31,31,31,-1,    -1, -1},  // 31
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,51,51,51,
         51,-1,-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 32
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,33,33,33,
         11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    19, -1},  // 33
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,34,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    19, -1},  // 34
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,35,35,
         35,-1,-1,-1,-1,-1,35,35,35,35,35,-1,-1,-1,-1,-1,-1,-1,-1,35,
         35,35,35,35,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    19, -1},  // 35
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     5, -1},  // 36
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     7, -1},  // 37
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     6, -1},  // 38
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,53,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 39
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,54,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 40
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,55,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 41
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    12, -1},  // 42
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,56,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 43
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,57,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 44
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,58,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 45
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,59,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 46
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,60,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 47
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,     9, -1},  // 48
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,-1,61,-1,-1,62,62,62,
         62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 49
    {-1,63,63,63,63,63,63,63,63,63,63,50,63,63,63,63,64,63,63,63,
         63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
         63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
         63,63,63,63,63,-1,    -1, -1},  // 50
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,51,51,51,
         51,-1,-1,-1,-1,-1,-1,-1,-1,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 51
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,-1,66,-1,-1,67,67,67,
         67,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 52
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,68,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 53
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,69,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 54
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    15, -1},  // 55
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,     2, -1},  // 56
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,70,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 57
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,71,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 58
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,72,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 59
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,73,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 60
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,62,62,
         62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 61
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,62,62,
         62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 62
    {-1,63,63,63,63,63,63,63,63,63,63,50,63,63,63,63,63,63,63,63,
         63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
         63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
         63,63,63,63,63,-1,    -1, -1},  // 63
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    18, -1},  // 64
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74,-1,74,-1,-1,75,75,75,
         75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 65
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,67,67,67,
         67,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 66
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,67,67,67,
         67,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 67
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    13, -1},  // 68
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,76,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 69
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,77,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 70
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,78,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 71
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,     1, -1},  // 72
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,79,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 73
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,75,75,
         75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    -1, -1},  // 74
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,75,75,
         75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,    20, -1},  // 75
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,     3, -1},  // 76
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,80,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 77
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,81,15,15,15,
         15,15,-1,-1,-1,-1,    22, -1},  // 78
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    14, -1},  // 79
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,     4, -1},  // 80
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,
         15,-1,-1,-1,-1,-1,15,15,15,15,15,15,15,15,-1,-1,-1,15,-1,15,
         15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
         15,15,-1,-1,-1,-1,    16, -1},  // 81
};


int const (*ScannerBase::s_dfaBase__[])[68] =
{
    s_dfa__ + 0,
};

size_t ScannerBase::s_istreamNr = 0;

// $insert inputImplementation
ScannerBase::Input::Input()
:
    d_in(0),
    d_lineNr(1)
{}

ScannerBase::Input::Input(std::istream *iStream, size_t lineNr)
:
    d_in(iStream),
    d_lineNr(lineNr)
{}

size_t ScannerBase::Input::get()
{
    switch (size_t ch = next())         // get the next input char
    {
        case '\n':
            ++d_lineNr;
        // FALLING THROUGH

        default:
        return ch;
    }
}

size_t ScannerBase::Input::next()
{
    size_t ch;

    if (d_deque.empty())                // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : static_cast<size_t>(AT_EOF);
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void ScannerBase::Input::reRead(size_t ch)
{
    if (ch < 0x100)
    {
        if (ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void ScannerBase::Input::reRead(std::string const &str, size_t fm)
{
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

ScannerBase::ScannerBase(std::istream &in, std::ostream &out)
:
    d_filename("-"),
    d_out(new std::ostream(out.rdbuf())),
// $insert interactiveInit
    d_in(0),
    d_input(new std::istream(in.rdbuf())),
    d_dfaBase__(s_dfa__)
{}

void ScannerBase::switchStream__(std::istream &in, size_t lineNr)
{
    d_input.close();
    d_input = Input(new std::istream(in.rdbuf()), lineNr);
}


ScannerBase::ScannerBase(std::string const &infilename, std::string const &outfilename)
:
    d_filename(infilename),
    d_out(outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
          outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                  new std::ofstream(outfilename)),
    d_input(new std::ifstream(infilename)),
    d_dfaBase__(s_dfa__)
{}

void ScannerBase::switchStreams(std::istream &in, std::ostream &out)
{
    switchStream__(in, 1);
    switchOstream(out);
}


void ScannerBase::switchOstream(std::ostream &out)
{
    *d_out << std::flush;
    d_out.reset(new std::ostream(out.rdbuf()));
}

// $insert debugFunctions
void ScannerBase::setDebug(bool onOff)
{}

bool ScannerBase::debug() const
{
    return false;
}

void ScannerBase::redo(size_t nChars)
{
    size_t from = nChars >= length() ? 0 : length() - nChars;
    d_input.reRead(d_matched, from);
    d_matched.resize(from);
}

void ScannerBase::switchOstream(std::string const &outfilename)
{
    *d_out << std::flush;
    d_out.reset(
            outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
            outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                    new std::ofstream(outfilename));
}


void ScannerBase::switchIstream(std::string const &infilename)
{
    d_input.close();
    d_filename = infilename;
    d_input = Input(new std::ifstream(infilename));
    d_atBOL = true;
}

void ScannerBase::switchStreams(std::string const &infilename,
                           std::string const &outfilename)
{
    switchOstream(outfilename);
    switchIstream(infilename);
}

void ScannerBase::pushStream(std::istream  &istr)
{
    std::istream *streamPtr = new std::istream(istr.rdbuf());
    p_pushStream("(istream)", streamPtr);
}

void ScannerBase::pushStream(std::string const &name)
{
    std::istream *streamPtr = new std::ifstream(name);
    if (!*streamPtr)
    {
        delete streamPtr;
        throw std::runtime_error("Cannot read " + name);
    }
    p_pushStream(name, streamPtr);
}


void ScannerBase::p_pushStream(std::string const &name, std::istream *streamPtr)
{
    if (d_streamStack.size() == s_maxSizeofStreamStack__)
    {
        delete streamPtr;
        throw std::length_error("Max stream stack size exceeded");
    }

    d_streamStack.push_back(StreamStruct{d_filename, d_input});
    d_filename = name;
    d_input = Input(streamPtr);
    d_atBOL = true;
}

bool ScannerBase::popStream()
{
    d_input.close();

    if (d_streamStack.empty())
        return false;

    StreamStruct &top = d_streamStack.back();

    d_input =   top.pushedInput;
    d_filename = top.pushedName;
    d_streamStack.pop_back();

    return true;
}



  // See the manual's section `Run-time operations' section for an explanation
  // of this member.
ScannerBase::ActionType__ ScannerBase::actionType__(size_t range)
{
    d_nextState = d_dfaBase__[d_state][range];

    if (d_nextState != -1)                  // transition is possible
        return ActionType__::CONTINUE;

    if (knownFinalState())                  // FINAL state reached
        return ActionType__::MATCH;         

    if (d_matched.size())
        return ActionType__::ECHO_FIRST;    // no match, echo the 1st char

    return range != s_rangeOfEOF__ ? 
                ActionType__::ECHO_CH 
            : 
                ActionType__::RETURN;
}

void ScannerBase::accept(size_t nChars)          // old name: less
{
    if (nChars < d_matched.size())
    {
        d_input.reRead(d_matched, nChars);
        d_matched.resize(nChars);
    }
}

void ScannerBase::setMatchedSize(size_t length)
{
    d_input.reRead(d_matched, length);  // reread the tail section
    d_matched.resize(length);           // return what's left
}

  // At this point a rule has been matched.  The next character is not part of
  // the matched rule and is sent back to the input.  The final match length
  // is determined, the index of the matched rule is determined, and then
  // d_atBOL is updated. Finally the rule's index is returned.
  // The numbers behind the finalPtr assignments are explained in the 
  // manual's `Run-time operations' section.
size_t ScannerBase::matched__(size_t ch)
{
    d_input.reRead(ch);

    FinalData *finalPtr;
                            
    if (not d_atBOL)                    // not at BOL
        finalPtr = &d_final.std;        // then use the std rule (3, 4)

                                        // at BOL
    else if (not available(d_final.std.rule))   // only a BOL rule avail.
            finalPtr = &d_final.bol;            // use the BOL rule (6)

    else if (not available(d_final.bol.rule)) // only a std rule is avail.
        finalPtr = &d_final.std;        // use the std rule (7)
        
    else if (                           // Both are available (8)
        d_final.bol.length !=           // check lengths of matched texts
        d_final.std.length              // unequal lengths, use the rule
    )                                   // having the longer match length
        finalPtr =              
            d_final.bol.length > d_final.std.length ?
                &d_final.bol
            :
                &d_final.std;

    else                            // lengths are equal: use 1st rule
        finalPtr = 
            d_final.bol.rule < d_final.std.rule ?
                &d_final.bol
            :
                &d_final.std;

    setMatchedSize(finalPtr->length);

    d_atBOL = d_matched.back() == '\n';


    return finalPtr->rule;
}

size_t ScannerBase::getRange__(int ch)       // using int to prevent casts
{
    return ch == AT_EOF ? as<size_t>(s_rangeOfEOF__) : s_ranges__[ch];
}

  // At this point d_nextState contains the next state and continuation is
  // possible. The just read char. is appended to d_match
void ScannerBase::continue__(int ch)
{
    d_state = d_nextState;

    if (ch != AT_EOF)
        d_matched += ch;
}

void ScannerBase::echoCh__(size_t ch)
{
    *d_out << as<char>(ch);
    d_atBOL = ch == '\n';
}


   // At this point there is no continuation. The last character is
   // pushed back into the input stream as well as all but the first char. in
   // the buffer. The first char. in the buffer is echoed to stderr. 
   // If there isn't any 1st char yet then the current char doesn't fit any
   // rules and that char is then echoed
void ScannerBase::echoFirst__(size_t ch)
{
    d_input.reRead(ch);
    d_input.reRead(d_matched, 1);
    echoCh__(d_matched[0]);
}

    // Update the rules associated with the current state, do this separately
    // for BOL and std rules.
    // If a rule was set, update the rule index and the current d_matched
    // length. 
void ScannerBase::updateFinals__()
{
    size_t len = d_matched.size();

    int const *rf = d_dfaBase__[d_state] + s_finIdx__;

    if (rf[0] != -1)        // update to the latest std rule
    {
        d_final.std = FinalData { as<size_t>(rf[0]), len };
    }

    if (rf[1] != -1)        // update to the latest bol rule
    {
        d_final.bol = FinalData { as<size_t>(rf[1]), len };
    }
}

void ScannerBase::reset__()
{
    d_final = Final{ 
                    FinalData{s_unavailable, 0}, 
                    FinalData {s_unavailable, 0} 
                };

    d_state = 0;
    d_return = true;

    if (!d_more)
        d_matched.clear();

    d_more = false;
}

int Scanner::executeAction__(size_t ruleIdx)
try
{
    switch (ruleIdx)
    {
        // $insert actions
        case 1:
        {
#line 4 "lex.l"
            return Parser::VOID;
        }
        break;
        case 2:
        {
#line 5 "lex.l"
            return Parser::INT;
        }
        break;
        case 3:
        {
#line 6 "lex.l"
            return Parser::FLOAT;
        }
        break;
        case 4:
        {
#line 8 "lex.l"
            return Parser::RETURN;
        }
        break;
        case 5:
        {
#line 9 "lex.l"
            return Parser::LE_OP;
        }
        break;
        case 6:
        {
#line 10 "lex.l"
            return Parser::GE_OP;
        }
        break;
        case 7:
        {
#line 11 "lex.l"
            return Parser::EQ_OP;
        }
        break;
        case 8:
        {
#line 12 "lex.l"
            return Parser::NE_OP;
        }
        break;
        case 9:
        {
#line 13 "lex.l"
            return Parser::OR_OP;
        }
        break;
        case 10:
        {
#line 14 "lex.l"
            return Parser::AND_OP;
        }
        break;
        case 11:
        {
#line 15 "lex.l"
            return Parser::INC_OP;
        }
        break;
        case 12:
        {
#line 16 "lex.l"
            return Parser::IF;
        }
        break;
        case 13:
        {
#line 17 "lex.l"
            return Parser::ELSE;
        }
        break;
        case 14:
        {
#line 18 "lex.l"
            return Parser::WHILE;
        }
        break;
        case 15:
        {
#line 19 "lex.l"
            return Parser::FOR;
        }
        break;
        case 16:
        {
#line 20 "lex.l"
            return Parser::STRUCT;
        }
        break;
        case 17:
        {
#line 21 "lex.l"
            return Parser::PTR_OP;
        }
        break;
        case 19:
        {
#line 25 "lex.l"
            {Parser::d_val__ = stoi(std::string(matched())); return Parser::INT_CONSTANT;}
        }
        break;
        case 20:
        {
#line 27 "lex.l"
            {Parser::d_val__ = stof(std::string(matched())); return Parser::FLOAT_CONSTANT;}
        }
        break;
        case 21:
        {
#line 29 "lex.l"
            {Parser::d_val__ = std::string(matched()); return Parser::STRING_LITERAL;}
        }
        break;
        case 22:
        {
#line 31 "lex.l"
            {Parser::d_val__ = std::string(matched()); return Parser::IDENTIFIER;}
        }
        break;
        case 23:
        {
#line 32 "lex.l"
            {Parser::d_val__ = std::string(matched()); return matched()[0];}
        }
        break;
    }
    noReturn__();
    return 0;
}
catch (Leave__ value)
{
    return static_cast<int>(value);
}

int Scanner::lex__()
{
    reset__();
    preCode();

    while (true)
    {
        size_t ch = get__();                // fetch next char
        size_t range = getRange__(ch);      // determine the range

        updateFinals__();                    // update the state's Final info

        switch (actionType__(range))        // determine the action
        {
            case ActionType__::CONTINUE:
                continue__(ch);
            continue;

            case ActionType__::MATCH:
            {
                d_token__ = executeAction__(matched__(ch));
                if (return__())
                {
                    print();
                    postCode(PostEnum__::RETURN);
                    return d_token__;
                }
                break;
            }

            case ActionType__::ECHO_FIRST:
                echoFirst__(ch);
            break;

            case ActionType__::ECHO_CH:
                echoCh__(ch);
            break;

            case ActionType__::RETURN:
                if (!popStream())
                {
                     postCode(PostEnum__::END);
                     return 0;
                }
                postCode(PostEnum__::POP);
             continue;
        } // switch

        postCode(PostEnum__::WIP);

        reset__();
        preCode();
    } // while
}

void ScannerBase::print__() const
{
}


