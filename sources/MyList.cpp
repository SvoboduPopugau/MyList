#include "MyList.hpp"

MyList::MyList():_len(0),_first(nullptr),_last(nullptr),_correct(false)
{
}

MyList::MyList(unsigned len):_len(len),_correct(true)
{
    _last = nullptr;
    _first = nullptr;
    Structure* olds = nullptr;
    for(unsigned i = 0; i<len; i++){
        Structure* news =  (Structure*) malloc(sizeof (Structure));
        news ->val=get_rand_un_short(0,100);
//        cout << news ->val << " ";  // вывод для проверки
        if((int)len-1 == 0){
            news ->next = nullptr;
            news ->past = nullptr;
            _last = news;
            _first = news;
            continue;
        }
        if(i==0){
            news ->past = nullptr;
            _first = news;
        }
        if((i!=0)&&(i!=(len-1))){
            news ->past = olds;
            olds ->next = news;
        }
        if(i==(len-1)){
            _last = news;
            news ->next = nullptr;
            news ->past = olds;
            olds ->next = news;
        }
        olds = news;
    }
}

MyList::MyList(unsigned len, unsigned short value):_len(len),_correct(true)
{
    _last = nullptr;
    _first = nullptr;
    Structure* olds = nullptr;
    for(unsigned i = 0; i<len; i++){
        Structure* news =  (Structure*) malloc(sizeof (Structure));
        news ->val=value;
//        cout << news ->val << " ";  // вывод для проверки
        if((int)len-1 == 0){
            news ->next = nullptr;
            news ->past = nullptr;
            _last = news;
            _first = news;
            continue;
        }
        if(i==0){
            news ->past = nullptr;
            _first = news;
        }
        if((i!=0)&&(i!=(len-1))){
            news ->past = olds;
            olds ->next = news;
        }
        if(i==(len-1)){
            _last = news;
            news ->next = nullptr;
            news ->past = olds;
            olds ->next = news;
        }
        olds = news;
    }

}

MyList::MyList(MyList &other):_len(other.size()),_correct(true)
{
    _last = nullptr;
    _first = nullptr;
    Structure* olds = nullptr;
    for(unsigned i = 0; i<other.size(); i++){
        Structure* news =  (Structure*) malloc(sizeof (Structure));
        news ->val=other.get_value(i);
//        cout << news ->val << " ";  // вывод для проверки
        if((int)size()-1 == 0){
            news ->next = nullptr;
            news ->past = nullptr;
            _last = news;
            _first = news;
            continue;
        }
        if(i==0){
            news ->past = nullptr;
            _first = news;
        }
        if((i!=0)&&(i!=(size()-1))){
            news ->past = olds;
            olds ->next = news;
        }
        if(i==(size()-1)){
            _last = news;
            news ->next = nullptr;
            news ->past = olds;
            olds ->next = news;
        }
        olds = news;
    }
}

unsigned short MyList::get_rand_un_short(int min, int max) const
{
    unsigned short x = (unsigned short)(min + rand() % max);
    return  x;
}

bool MyList::is_empty() const
{
    if((_len == 0)&&(_first==nullptr)&&(_last==nullptr)&&(_correct==true))
        return true;
    else
        return false;
}

bool MyList::is_null() const
{
    if((_len == 0)&&(_first==nullptr)&&(_last==nullptr)&&(_correct==false))
        return true;
    else
        return false;

}

unsigned MyList::size() const
{
    return _len;
}

Structure* MyList::get_element(unsigned number) const
{
    Structure* find = _first;
    for (unsigned i=0; i<number; i++){
        find = find ->next;
    }
    return find;
}

void MyList::add_element(Structure *other, unsigned index)
{
    if(index > _len)          // Если указанный индекс больше размер массива добавляем элемент вконец
        add_element(other);

    if((index <= _len)&&(index > 0)){        // Если индекс элемента меньше или равен длине контейнера и не равен 0 добавляем в тело
        Structure* old = get_element(index);
        other ->past = old ->past;
        old ->past ->next = other;
        old ->past = other;
        other ->next = old;
        _len++;
    }

    if(index == 0){                       // Если индекс элемента равен индексу первого элемента добавляем в начало
        _first ->past = other;
        other ->next = _first;
        _first = other;
        other ->past = nullptr;
        _len++;
    }

}

void MyList::add_element(unsigned short value, unsigned index)
{
    Structure* added = (Structure*) malloc(sizeof (Structure));
    added ->val = value;
    add_element(added,index);
}

void MyList::add_element(unsigned short value)
{
    Structure* added = (Structure*) malloc(sizeof (Structure));
    added ->val = value;
    add_element(added);
}

void MyList::delete_element(unsigned index)
{
    Structure* del = get_element(index);
//    cout << "DELETED "<<index << ":"<< del->val <<endl;
//    cout << "FIRST "<<":"<< _first ->val <<endl;
//    cout << "LAST "<<":"<< _last ->val <<endl;
    if((_first == del)&&(_last != del)){
        _first ->next ->past = nullptr;
        _first = _first ->next;
        _len--;
        free(del);
        del = nullptr;
        return;
//    cout << "NEW FIRST "<<":"<< _first ->val <<endl;
//    cout << "LAST "<<":"<< _last ->val <<endl;
    }
    if((_first == del)&&(_last == del)){
        _first = nullptr;
        _last = nullptr;
        _len = 0;
        free(del);
        del = nullptr;
        return;
    }
    if((_first != del)&&(_last == del)){
        _last ->past ->next = nullptr;
        _last = _last ->past;
        _len--;
        free(del);
        del = nullptr;
        return;
    }
    if((_first != del)&&(_last != del)){
        del ->past ->next = del ->next;
        del ->next ->past = del ->past;
        _len--;
        free(del);
        del = nullptr;
        return;
    }
}

void MyList::resize(int delta)
{
    if(delta >= 0){
//    List add (delta,0);
//    _last ->next = add.getFirst();
//    _last = add.getLast();
        Structure* olds = _last;
        for(unsigned i =0; i <(unsigned)delta; i++){
            Structure* news =  (Structure*) malloc(sizeof (Structure));
            news ->val = 0;
            news ->next = nullptr;
            olds ->next = news;
            news ->past = olds;
            _last = news;
            olds = news;
        }
        _len += delta;
    }

    if(delta < 0){
        for(unsigned i = 0; i<(unsigned)abs(delta); i++){
            delete_element(size()-1);
        }

    }

}

unsigned short MyList::get_value(unsigned index) const
{
    return get_element(index)->val;
}

void MyList::set_value(unsigned short value, unsigned index)
{
    get_element(index)->val = value;
}

void MyList::add_element(Structure *other)
{
    _last ->next = other;
    other ->past = _last;
    other ->next = nullptr;
    _last = other;
    _len ++;
}

Structure *MyList::getFirst() const
{
    return _first;
}

Structure *MyList::getLast() const
{
    return _last;
}

MyList &MyList::operator =(const MyList &cop)
{
    if(!is_empty()){
        resize(cop.size()-size());
        for(unsigned i = 0; i<cop.size();i++)
            set_value(cop.get_value(i),i);
    }
    else{
        _len = cop.size();
        Structure* olds = nullptr;
        for(unsigned i = 0; i<cop.size(); i++){
            Structure* news =  (Structure*) malloc(sizeof (Structure));
            news ->val=cop.get_value(i);
//            cout << news ->val << " ";  // вывод для проверки
            if((int)cop.size()-1 == 0){
                news ->next = nullptr;
                news ->past = nullptr;
                _last = news;
                _first = news;
                continue;
            }
            if(i==0){
                news ->past = nullptr;
                _first = news;
            }
            if((i!=0)&&(i!=(cop.size()-1))){
                news ->past = olds;
                olds ->next = news;
            }
            if(i==(cop.size()-1)){
                _last = news;
                news ->next = nullptr;
                news ->past = olds;
                olds ->next = news;
            }
            olds = news;
        }
    }
    return *this;
}

void MyList::print() const
{
    for(unsigned i = 0; i < _len; i++)
        cout << get_value(i) << " ";
    cout << endl;
}

MyList::~MyList()
{
//    cout << "Destructer"<< endl;
    for(int i = _len-1; i >= 0; i--){
//        cout << "DELETED "<<i << ":"<< get_value(i) <<endl;
        free(get_element(i));
//        delete_element(i);
    }
    _last = nullptr;
    _first =nullptr;
    _len = 0;
    _correct = false;
}
