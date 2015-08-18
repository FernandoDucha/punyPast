/* 
 * File:   BufferedManagerIterator.h
 * Author: fordem
 *
 * Created on March 6, 2015, 11:10 PM
 */

#ifndef BUFFERITERATOR_H
#define	BUFFERITERATOR_H
#include <typeinfo>
#include <string.h>
#include <vector>
#include <assert.h>
#include "RWLocPair.h"
#include "FileInStreamInterface.h"
#include "FileOutStreamInterface.h"
#include "RWBufferedDpBase.h"
#include "RWBufferedVecBase.h"
using namespace std;

template <class Type, class Def>class RWBufferIterator {
public:
    typedef vector<RWLocPair>::iterator baseIter;
    RWBufferIterator(baseIter beg, baseIter end, FileInStreamInterface<Type> * input, FileOutStreamInterface<Type> * output);
    virtual ~RWBufferIterator();
    RWBufferIterator<Type, Def>& operator++();
    RWBufferIterator<Type, Def>& operator--();
    RWBufferIterator<Type, Def>& operator++(int);
    RWBufferIterator<Type, Def>& operator--(int);
    Def & operator[](uint64_t);
    Def * operator->();
    Def & operator*();
    bool last();
    bool first();
    Def & goBeg();
    Def & goEnd();
private:
    FileInStreamInterface<Type> * _input;
    FileOutStreamInterface<Type> * _output;
    baseIter _beg, _end, _cur;
    Def _baseRet;
};

template <class Type, class Def>Def & RWBufferIterator<Type, Def>::operator[](uint64_t off) {
    Def aux(_input, _output, _cur[off]);
    _baseRet.setFInitPos(_cur[off][RWLocPair::POS]);
    _baseRet.setNpoints(_cur[off][RWLocPair::LEN ]);
    _baseRet = aux;
    return _baseRet;
}

template <class Type, class Def>RWBufferIterator<Type, Def>& RWBufferIterator<Type, Def>::operator++(int off) {
    for (int i = 0; i <= off; i++) {
        if (_cur != _end) {
            _cur++;
        }
    }
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    return *this;
}

template <class Type, class Def>RWBufferIterator<Type, Def>& RWBufferIterator<Type, Def>::operator--(int off) {
    for (int i = 0; i <= off; i++) {
        if (_cur != _beg) {
            _cur--;
        }
    }
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    return *this;
}

template <class Type, class Def> Def& RWBufferIterator<Type, Def>::goBeg() {
    _cur = _beg;
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    return _baseRet;
}

template <class Type, class Def> Def& RWBufferIterator<Type, Def>::goEnd() {
    _cur = _end;
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    return _baseRet;
}

template <class Type, class Def>bool RWBufferIterator<Type, Def>::last() {
    return _end == _cur;
}

template <class Type, class Def>bool RWBufferIterator<Type, Def>::first() {
    return _beg == _cur;
}

template <class Type, class Def>RWBufferIterator<Type, Def>& RWBufferIterator<Type, Def>::operator++() {
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    _cur++;
    return *this;
}

template <class Type, class Def>RWBufferIterator<Type, Def>& RWBufferIterator<Type, Def>::operator--() {
    Def aux(_input, _output, *_cur);
    _baseRet.setFInitPos((*_cur)[RWLocPair::POS]);
    _baseRet.setNpoints((*_cur)[RWLocPair::LEN ]);
    _baseRet = aux;
    _cur--;
    return *this;
}

template <class Type, class Def>Def* RWBufferIterator<Type, Def>::operator->() {
    return &_baseRet;
}

template <class Type, class Def>Def& RWBufferIterator<Type, Def>::operator*() {
    return _baseRet;
}

template <class Type, class Def> RWBufferIterator<Type, Def>::RWBufferIterator(baseIter beg, baseIter end, FileInStreamInterface<Type> * input, FileOutStreamInterface<Type> * output) : _baseRet(input, output) {
    assert(typeid (typename Def::internType) == typeid (Type)&&"Incompatible basic types from RWBufferIterator, make sure they are the same.");
    Def temp(input, output);
    assert(dynamic_cast<IRWBufferedItem<Type>*> (&temp) != 0);
    _input = input;
    _output = output;
    _cur = _beg = beg;
    _end = end;
}

template <class Type, class Def>RWBufferIterator<Type, Def>::~RWBufferIterator() {

}
#endif	/* BUFFEREDMANAGERITERATOR_H */

