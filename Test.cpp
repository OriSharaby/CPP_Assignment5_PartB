#include <iostream>
#include <stdexcept>
#include <sstream>
#include "doctest.h"
#include "/home/ori/Desktop/C++/Ex5/Magical_Iterators-main/sources/MagicalContainer.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("Test addElement and removeElement")
{
    MagicalContainer container;
    CHECK(container.size() == 0);

    container.addElement(1);
    CHECK(container.size() == 1);

    container.addElement(2);
    container.addElement(3);

    CHECK(container.size() == 3);

    container.removeElement(2);
    CHECK(container.size() == 2);

    container.removeElement(1);
    container.removeElement(3);

    CHECK(container.size() == 0);
}

TEST_CASE("Test SortedIterator")
{
    MagicalContainer container;
    container.addElement(3);
    container.addElement(4);
    container.addElement(2);

    MagicalContainer::AscendingIterator ascIter(container);

    CHECK_EQ(*ascIter, 2);
    ++ascIter;
    CHECK_EQ(*ascIter, 3);
    ++ascIter;
    CHECK_EQ(*ascIter, 4);
    ++ascIter;
    CHECK_EQ(ascIter, ascIter.end());
}

TEST_CASE("Test SideCrossIterator")
{
    MagicalContainer container;
    container.addElement(2);
    container.addElement(3);
    container.addElement(1);

    MagicalContainer::SideCrossIterator crossIter(container);

    CHECK(*crossIter == 1);
    ++crossIter;
    CHECK(*crossIter == 3);
    ++crossIter;
    CHECK(*crossIter == 2);
    ++crossIter;
    CHECK_EQ(crossIter, crossIter.end());
}

TEST_CASE("Test PrimeIterator")
{
    MagicalContainer container;
    container.addElement(3);
    container.addElement(5);
    container.addElement(6);
    container.addElement(7);

    MagicalContainer::PrimeIterator primeIter(container);

    CHECK(*primeIter == 3);
    ++primeIter;
    CHECK(*primeIter == 5);
    ++primeIter;
    CHECK(*primeIter == 7);
    ++primeIter;
    CHECK_EQ(primeIter, primeIter.end());
}

TEST_CASE("Test Iterator comparison")
{
    MagicalContainer container;
    container.addElement(3);
    container.addElement(4);
    container.addElement(2);

    MagicalContainer::AscendingIterator ascendingIter1(container);
    MagicalContainer::AscendingIterator ascendingIter2(container);
    MagicalContainer::SideCrossIterator crossIter1(container);
    MagicalContainer::SideCrossIterator crossIter2(container);
    MagicalContainer::PrimeIterator primeIter1(container);
    MagicalContainer::PrimeIterator primeIter2(container);

    CHECK_EQ(ascendingIter1, ascendingIter2);
    CHECK_EQ(crossIter1, crossIter2);
    CHECK_EQ(primeIter1, primeIter2);

    ++ascendingIter1;
    CHECK_NE(ascendingIter1, ascendingIter2);
    CHECK_GT(ascendingIter1, ascendingIter2);
    CHECK_LT(ascendingIter2, ascendingIter1);

    ++crossIter1;
    CHECK_NE(crossIter1, crossIter2);
    CHECK_GT(crossIter1, crossIter2);
    CHECK_LT(crossIter2, crossIter1);

    ++primeIter1;
    CHECK_NE(primeIter1, primeIter2);
    CHECK_GT(primeIter1, primeIter2);
    CHECK_LT(primeIter2, primeIter1);

    ++ascendingIter2;
    CHECK_EQ(ascendingIter1, ascendingIter2);

    ++crossIter2;
    CHECK_EQ(crossIter1, crossIter2);

    ++primeIter2;
    CHECK_EQ(primeIter1, primeIter2);
}