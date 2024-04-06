
template<class InputIterator>
void double_each_element(InputIterator begin, InputIterator end){
    for(auto itr = begin; itr != end; ++itr){
        (*itr) *= 2;
    }

    /*
    for(auto& val : container){
        val *= 2
    }
    */
}

template<class Containter>
void printContainer(const Containter &container, std::ostream &stream){
    for(const auto& val : container){
        stream << val << ", ";
    }
    stream << "\n";
}

template<class Itr, class UnaryPredicate>
Itr find_if(Itr first, Itr last, UnaryPredicate p){
  auto Itr itr = first;
  while(itr != last){
    if(p(*itr)) return itr;
    ++itr;
  }
  return itr;
}

template<class It, class U>
It find_if_not(It first, It last, U p) {
  auto result = std::find_if(first, last, [&](auto&& e){ return !p(e); }); 

  return result;
}
