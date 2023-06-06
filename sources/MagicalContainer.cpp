#include "/home/ori/Desktop/C++/Ex5/Magical_Iterators_B-main/sources/MagicalContainer.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

namespace ariel
{
    bool isPrime(int num)
    {
        if (num <= 1)
        {
            return false;
        }
        else if (num == 2)
        {
            return true;
        }
        else
        {
            for (int i = 2; i <= sqrt(num); i++)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }

    void MagicalContainer::updateoriginalElements()
    {
        unsigned long n = _originalElements.size();

        for (unsigned long i = 0; i < n; ++i)
        {
            // Last i elements are already in place
            for (unsigned long j = 0; j < n - i - 1; ++j)
            {
                // Swap adjacent elements if they are in the wrong order
                if (_originalElements[j] > _originalElements[j + 1])
                {
                    std::swap(_originalElements[j], _originalElements[j + 1]);
                }
            }
        }
    }
    void MagicalContainer::updateSortedElements()
    {
        _sortedElements.clear();
        for (auto it = _originalElements.begin(); it != _originalElements.end(); ++it)
        {
            _sortedElements.push_back(&(*it));
        }
    }
    void MagicalContainer::updateCrossElements()
    {
        _crossElements.clear();
        auto start = _originalElements.begin();
        auto end = --_originalElements.end();
        while (start < end)
        {
            _crossElements.push_back(&(*start));
            _crossElements.push_back(&(*end));
            ++start;
            --end;
        }
        if (start == end)
        {
            _crossElements.push_back(&(*end));
        }
    }
    void MagicalContainer::updatePrimeElements()
    {
        _primeElements.clear();
        for (auto it = _originalElements.begin(); it != _originalElements.end(); ++it)
        {
            if (isPrime(*it))
            {
                _primeElements.push_back(&(*it));
            }
        }
    }

    void MagicalContainer::addElement(int element)
    {
        _originalElements.push_back(element);
        updateoriginalElements();

        updateCrossElements();

        updatePrimeElements();

        updateSortedElements();
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = std::find(_originalElements.begin(), _originalElements.end(), element);

        if (it == _originalElements.end())
        {
            throw std::runtime_error("Element not found in container");
            return;
        }
        _originalElements.erase(std::remove(_originalElements.begin(), _originalElements.end(), element), _originalElements.end());
        updateoriginalElements();
        updateSortedElements();
        updateCrossElements();
        updatePrimeElements();
    }
    int MagicalContainer::size()
    {
        return _originalElements.size();
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~AscendingIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~AscendingIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(container), iter(container._sortedElements.begin()), position(0)
    {
    }
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), iter(other.iter), position(other.position)
    {
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Cannot copy from diffrent conatainer");
        }
        container = other.container;
        position = other.position;
        iter = other.iter;

        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (iter == container._sortedElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++position;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*()
    {
        if (iter == container._sortedElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        return **iter;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        if (&container != &other.container)
            throw std::invalid_argument("Cant compare iterators from different containers");

        return position == other.position;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        if (&container != &other.container) // if they are not the same container
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position < other.position;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        if (&container != &other.container) // if they are not the same container
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position > other.position;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin()
    {
        iter = container._sortedElements.begin();
        position = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end()
    {
        iter = container._sortedElements.end();
        position = container._sortedElements.size();
        return *this;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~SideCrossIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~SideCrossIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(container), iter(container._crossElements.begin()), position(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), iter(other.iter), position(other.position) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Cannot copy from diffrent conatainer");
        }
        container = other.container;
        position = other.position;
        iter = other.iter;

        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (iter == container._crossElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++position;
        return *this;
    }
    int &MagicalContainer::SideCrossIterator::operator*()
    {
        if (iter == container._crossElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        return **iter;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
            throw std::invalid_argument("Cant compare iterators from different containers");

        return position == other.position;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position < other.position;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position > other.position;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin()
    {
        iter = container._crossElements.begin();
        position = 0;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end()
    {
        iter = container._crossElements.end();
        position = container._crossElements.size();
        return *this;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~PrimeIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~PrimeIterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(container), iter(container._primeElements.begin()), position(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container), iter(other.iter), position(other.position) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Cannot copy from diffrent conatainer");
        }
        container = other.container;
        position = other.position;
        iter = other.iter;

        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (iter == container._primeElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++position;
        return *this;
    }
    int &MagicalContainer::PrimeIterator::operator*()
    {
        if (iter == container._primeElements.end())
        {
            throw std::runtime_error("Out of range");
        }
        return **iter;
    }
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        if (&container != &other.container)
            throw std::invalid_argument("Cant compare iterators from different containers");

        return position == other.position;
    }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position < other.position;
    }
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        if (&container != &other.container)
        {
            throw std::invalid_argument("Cant compare iterators from different containers");
        }
        return position > other.position;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin()
    {
        iter = container._primeElements.begin();
        position = 0;
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end()
    {
        iter = container._primeElements.end();
        position = container._primeElements.size();
        return *this;
    }
}