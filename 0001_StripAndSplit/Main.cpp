
#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// =============================================================================
std::string
Strip( std::string const& cStringToStrip,
       std::string const& cSymbolsToRemove );

std::vector<std::string>
Split( std::string const& cStringToSplit,
       std::string const& cDividerString );

// =============================================================================
namespace
{
    TEST(TestStripAndSplit, TestStrip)
    {
        EXPECT_EQ( Strip( "",   "" ), "" );
        EXPECT_EQ( Strip( "",   " " ), "" );
        EXPECT_EQ( Strip( " ",   "" ), " " );
        EXPECT_EQ( Strip( " ",   " " ), "" );
        EXPECT_EQ( Strip( "   , + - ",   " ,+-  " ), "" );
        EXPECT_EQ( Strip( "  Test Strip    ",   " " ), "Test Strip" );
        EXPECT_EQ( Strip( " ,Test Strip  + ", " ,+" ), "Test Strip" );
        EXPECT_EQ( Strip( " ,Test +-Strip  + ", " ,+" ), "Test +-Strip" );
    }

    TEST(TestStripAndSplit, TestSplit)
    {
        EXPECT_TRUE( Split( "",   "" ) == std::vector<std::string>{ "" } );
        EXPECT_TRUE( Split( "",   " " ) == std::vector<std::string>{ "" } );
        EXPECT_TRUE( Split( " ",   "" ) == std::vector<std::string>{ " " } );
        EXPECT_TRUE( ( Split( " ",   " " ) == std::vector<std::string>{ "", "" } ) );
        EXPECT_TRUE( ( Split( "abcdef",   "abcdef" ) == std::vector<std::string>{ "", "" } ) );
        EXPECT_TRUE( ( Split( "a b c d",   " " ) == std::vector<std::string>{ "a", "b", "c", "d" } ) );
        EXPECT_TRUE( ( Split( "a  d",   " " ) == std::vector<std::string>{ "a", "", "d" } ) );
        EXPECT_TRUE( ( Split( "   d",   " " ) == std::vector<std::string>{ "", "", "", "d" } ) );
        EXPECT_TRUE( ( Split( "a   ",   " " ) == std::vector<std::string>{ "a", "", "", "" } ) );
        EXPECT_TRUE( ( Split( "***",   "*" ) == std::vector<std::string>{ "", "", "", "" } ) );
        EXPECT_TRUE( ( Split( "***",   "**" ) == std::vector<std::string>{ "", "*" } ) );
    }
}

// =============================================================================
std::string
Strip( std::string const& cStringToStrip,
       std::string const& cSymbolsToRemove )
{
    std::set<char> symbolsToRemove;

    if( cStringToStrip.size() == 0 or cSymbolsToRemove.size() == 0 )
        return cStringToStrip;

    std::for_each( cSymbolsToRemove.cbegin(), cSymbolsToRemove.cend(),
                   [&symbolsToRemove]( char const symbol )
                   {
                       symbolsToRemove.insert( symbol );
                   } );

    auto startIdx = 0;
    while( startIdx < cStringToStrip.size() and
           symbolsToRemove.find( cStringToStrip[startIdx] ) != symbolsToRemove.end() )
        startIdx++;

    auto endIdx = cStringToStrip.size() - 1;
    while( endIdx >= 0 and
           symbolsToRemove.find( cStringToStrip[endIdx] ) != symbolsToRemove.end() )
        endIdx--;

    if( endIdx < startIdx )
        return "";

    return cStringToStrip.substr( startIdx, ( endIdx - startIdx + 1 ) );
}

// =============================================================================
std::vector<std::string>
Split( std::string const& cStringToSplit,
       std::string const& cDividerString )
{
    if( cStringToSplit.size() == 0 or cDividerString.size() == 0 or
        cStringToSplit.size() < cDividerString.size() )
        return { cStringToSplit };

    if( cStringToSplit == cDividerString )
        return { "", "" };

    std::vector<std::string> separatedStrings;
    auto startIdx = 0;

    while( true )
    {
        auto endIdx = cStringToSplit.find( cDividerString, startIdx );

        if( endIdx == std::string::npos )
        {
            separatedStrings.push_back( cStringToSplit.substr( startIdx, ( cStringToSplit.size() - startIdx ) ) );
            break;
        }
        else if( startIdx == endIdx )
            separatedStrings.push_back( "" );
        else
            separatedStrings.push_back( cStringToSplit.substr( startIdx, ( endIdx - startIdx ) ) );

        startIdx = endIdx + cDividerString.size();
    }

    return separatedStrings;
}