#include "list.hpp"

template <typename T>
List<T>::List() 
{
  array = new T[0];
  arraySize = 0;
}

template <typename T>
List<T>::~List() 
{
  delete [] array;
}

template <typename T>
List<T>::List(const List & rhs)
{
  arraySize = rhs.getLength();
  array = new T[arraySize];
  for(int i = 0; i < arraySize; i++)
  {
    array[i] = rhs.array[i];
  }
}

template <typename T>
List<T> & List<T>::operator=(const List & rhs)
{  
  delete []array;
  this -> arraySize = rhs.getLength();
  this -> array = new T[arraySize];
  for(int i = 0; i < arraySize; i++)
  {
    array[i] = rhs.array[i];
  }
  return *this;
}

template <typename T>
bool List<T>::isEmpty() const
{
  if(arraySize == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
std::size_t List<T>::getLength() const
{
  return arraySize;
}

template <typename T>
bool List<T>::insert(std::size_t position, const T& item)
{
  if(position > arraySize+1)
  {
    return false;
  }
    T *newArray = new T[arraySize+1];
    arraySize++;
    int j = 0;
    for(int i = 0; i < arraySize; i++)
    {
      if(i == position-1)
      {
        newArray[i] = item;
      }
      else
      {
        newArray[i] = array[j];
        j++;
      }
    }
    delete[] array;
    array = newArray;
    return true;
}

template <typename T>
bool List<T>::remove(std::size_t position)
{
  if(position > arraySize || position <= 0)
  {
    return false;
  }
  position--;
 for(int i = position; i<arraySize-1; i++)
 {
   array[i] = array[i+1];
 }
 arraySize--;
  T *newArray = new T[arraySize];
 for(int i = 0 ; i<arraySize; i++)
 {
   newArray[i] = array[i];
 }
  delete[] array;
  array = newArray;
  return true;
}

template<typename T>
void List<T>::clear()
{
  delete [] array;
  array = new T[0];
  arraySize = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const 
{
  position--;
  if(position < arraySize)
  {
    return array[position];
  }
  
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue) 
{
  position--;
  if(position < arraySize)
  {
    array[position] = newValue;
  }
}
