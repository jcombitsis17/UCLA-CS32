#include "ScoreList.h"

ScoreList::ScoreList()
{
    
}
// Create an empty score list.

bool ScoreList::add(unsigned long score)
{
    if (score > 100 || m_Sequence.size() >= DEFAULT_MAX_ITEMS)
        return false;
    m_Sequence.insert(m_Sequence.size(), score);
    return true;
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score)
{
    if (m_Sequence.empty() || m_Sequence.find(score) == -1)
        return false;
    m_Sequence.erase(m_Sequence.find(score));
    return true;
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.

int ScoreList::size() const
{
    return m_Sequence.size();
}
// Return the number of scores in the list.

unsigned long ScoreList::minimum() const
{
    if (m_Sequence.empty())
        return NO_SCORE;
    unsigned long min, compare;
    m_Sequence.get(0, min);
    for (int i = 0; i < m_Sequence.size(); i++)
    {
        m_Sequence.get(i, compare);
        if (compare < min)
            min = compare;
    }
    return min;
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const
{
    if (m_Sequence.empty())
        return NO_SCORE;
    unsigned long max, compare;
    m_Sequence.get(0, max);
    for (int i = 0; i < m_Sequence.size(); i++)
    {
        m_Sequence.get(i, compare);
        if (compare > max)
            max = compare;
    }
    return max;
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
