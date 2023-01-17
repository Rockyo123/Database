#include "Database.hpp"

template <typename T>
Database<T>::Database() 
{
    
}

//merge sort
template <typename T>
std::vector<std::string> Database<T>::mergeSort(std::vector<std::string> vec, size_t left, size_t right)
{
    if(left <= right)
    {
        size_t mid = left + (right-1)/2;
        mergeSort(vec,left, mid);
        mergeSort(vec, mid+1, right);
        merge(vec, left, mid, right);
    }
}
template <typename T>
std::vector<std::string> Database<T>::merge(std::vector<std::string> vec, size_t left, size_t mid, size_t right)
{
    std::vector<std::string> vec1;
    std::vector<std::string> vec2;
    for(size_t i = 0; i < (mid-left+1); i++)
    {
        vec1[i] = vec[left+i];
    }
    for(size_t i =0; i < (right - mid); i++)
    {
        vec2[i] = vec[mid+1+i];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while(i < vec1.size() && j < vec2.size())
    {
        if(vec1[i] <= vec2[j])
        {
            vec[k] = vec1[i];
            i++;
        }
        else
        {
            vec[k] = vec2[j];
            j++;
        }
        k++;
    }

    while(i < vec1.size())
    {
        vec[k] = vec1[i];
        i++;
        k++;
    }

    while(j < vec2.size())
    {
        vec[k] = vec2[j];
        j++;
        k++;
    }
}

template <typename T>
bool Database<T>::isEmpty() 
{
    if(lst.isEmpty())
    {
        return true;
    }
    return false;
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() 
{
    return lst.getLength();
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, const T& item) 
{
    bool one = false;
    bool two = false;
    size_t pos = lst.getLength()+1;
    if(BSTkey1.insert(key1,pos))
    {
        one = true;
    }
    if(BSTkey2.insert(key2,pos))
    {
        two = true;
    }
    if(one && two)
    {
        lst.insert(pos, item);
        keyVec.push_back({key1, key2});
        return true;
    }
    return false;
}

template <typename T>
bool Database<T>::remove(std::string key) 
{
    int i = 0;
    while(i < keyVec.size())
    {
        if(keyVec[i][0] == key || keyVec[i][1] == key)
        {
            break;
        }
        i++;
    }
    if(i >= keyVec.size())
    {
        return false;
    }
    size_t pos;
    if(BSTkey1.retrieve(key, pos))
    {
        lst.remove(pos);
        BSTkey1.remove(key);
        BSTkey2.remove(keyVec[i][1]);
        return true;
    }
    if(BSTkey2.retrieve(key,pos))
    {
        lst.remove(pos);
        BSTkey2.remove(key);
        BSTkey1.remove(keyVec[i][0]);
        return true;
    }
    return false;
}

template <typename T>
void Database<T>::clear() 
{
    lst.clear();
    BSTkey1.destroy();
    BSTkey2.destroy();
    keyVec.clear();
}

template <typename T>
T Database<T>::getValue(std::string key) 
{
    size_t pos;
    if(BSTkey1.retrieve(key, pos))
    {
        return lst.getEntry(pos);
    }
    if(BSTkey2.retrieve(key,pos))
    {
        return lst.getEntry(pos);
    }
}

template <typename T>
bool Database<T>::contains(std::string key) 
{
    size_t pos;
    if(BSTkey1.retrieve(key, pos) || BSTkey2.retrieve(key, pos))
    {
        return true;
    }
    return false;
}

template <typename T>
std::vector<T> Database<T>::getAllEntries(int keyIndex) 
{
    std::vector<T> retVec;
    if(keyIndex != 1 && keyIndex != 2)
    {
        throw std::logic_error("must use keyIndex of 1 or 2");
    }
    std::vector<std::string> keys1;
    std::vector<std::string> keys2;
    for(int i = 0; i < keyVec.size(); i++)
    {
        keys1[i] = keyVec[i][0];
        keys2[i] = keyVec[i][1];
    }

    //key1
    if(keyIndex == 1)
    {
        //sorting the keys
        keys1 = mergeSort(keys1, 0, keys1.size());

        //inserting into return vector
        size_t pos;
        for(int i =0; i < keys1.size(); i++)
        {
            BSTkey1.retrieve(keys1[i], pos);
            retVec.push_back(lst.getEntry(pos));
        }
        return retVec;
    }

    //key2
    if(keyIndex == 2)
    {
        //sorting the keys
        keys1 = mergeSort(keys2, 0, keys2.size());

        //inserting into return vector
        size_t pos;
        for(int i =0; i < keys2.size(); i++)
        {
            BSTkey1.retrieve(keys2[i], pos);
            retVec.push_back(lst.getEntry(pos));
        }
        return retVec;
    }
}