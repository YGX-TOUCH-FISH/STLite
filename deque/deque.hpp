#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>
#include <iostream>
namespace sjtu { 

template<class T>
class deque {
public:
    class block;
    friend class block;
    block *tail;
private:
    block *head;
    int all_size;
public:
	class const_iterator;
	class iterator {
    public:
		 friend class deque<T>;
		 block *blk_point;
		 deque<T> *que_point;
		 int index;
    public:
		iterator() :blk_point(nullptr), index(0), que_point(nullptr) {}

		iterator(const iterator &ec){
		    blk_point = ec.blk_point;
		    index = ec.index;
		    que_point = ec.que_point;
		}

		iterator(block *s, int ind, deque<T>* r):blk_point(s),index(ind),que_point(r){}

		iterator &operator=(const iterator &other){
            if (this == &other) return *this;
		    blk_point = other.blk_point;
		    index = other.index;
		    que_point = other.que_point;
            return *this;
		}

		iterator operator+(const int &n) const {
            if (n < 0) return *this - (-n);
            else {
                block *r = blk_point;
                int i = index + n;//偏移后的应有下标
                if (i < r->size) {
                    iterator answer(r, i, que_point);
                    return answer;
                }
                else {
                    while (i >= r->size){
                        if (i == r->size && r->next == nullptr) {
                            return iterator(r, i, que_point);
                        }
                        else {
                            i -= r->size;
                            r = r->next;
                            if (r == nullptr) throw invalid_iterator();
                        }
                    }
                    return iterator (r, i, que_point);
                }
            }
		}

		iterator operator-(const int &n) const {
            if (n < 0) return *this +(-n);
            else {
                block *r = blk_point;
                int i = index - n;
                if (i >= 0) {
                    return iterator(r, i, que_point);
                }
                else {
                    while (i < 0){
                        r = r->prev;
                        if (r == nullptr) throw invalid_iterator();
                        i += r->size;
                    }
                    iterator answer(r, i, que_point);
                    return answer;
                }
            }
		}

		bool valid() const{
            return que_point && blk_point && index >= 0 && index < blk_point->size;
		}

		int operator-(const iterator &rhs) const {
            if (que_point != rhs.que_point) throw invalid_iterator();
            if (blk_point == rhs.blk_point) return index - rhs.index;
            int i = index;
            block *r = blk_point->prev;
            while (r != nullptr) {
                i += r->size;
                if (r == rhs.blk_point) return i - rhs.index;
                else r = r->prev;
            }
            i = blk_point->size - index;
            r = blk_point->next;
            while (r != nullptr) {
                if (r == rhs.blk_point) return -(i + rhs.index);
                else {
                    i += r->size;
                    r = r->next;
                }
            }
            throw runtime_error();
		}
		iterator& operator+=(const int &n) {
            return *this = *this + n;
		}
		iterator& operator-=(const int &n) {
            return *this = *this - n;
		}
		iterator operator++(int) {
		    iterator answer = *this;
		    *this = *this + 1;
            return answer;
		}
		iterator& operator++() {
		    *this = *this + 1;
            return *this;
		}
		iterator operator--(int) {
		    iterator answer = *this;
		    *this = *this - 1;
            return answer;
		}
		iterator& operator--() {
		    *this = *this - 1;
            return *this;
		}
		T& operator*() const {
            if (!valid()) throw invalid_iterator();
            return blk_point->array[index][0];
		}
		T* operator->() const noexcept {
            if (!valid()) throw invalid_iterator();
            return blk_point->array[index];
		}
		bool operator==(const iterator &rhs) const {
            if (blk_point != rhs.blk_point) return false;
            if (index != rhs.index) return false;
            return true;
		}
		bool operator==(const const_iterator &rhs) const {
            if (blk_point != rhs.blk_point) return false;
            if (index != rhs.index) return false;
            return true;
		}
		bool operator!=(const iterator &rhs) const {
            if (blk_point != rhs.blk_point) return true;
            if (index != rhs.index) return true;
            return false;
		}
		bool operator!=(const const_iterator &rhs) const {
            if (blk_point != rhs.blk_point) return true;
            if (index != rhs.index) return true;
            return false;
		}
    };
	class const_iterator {
    private:
        friend class deque<T>;
        block *blk_point;
        const deque<T> *que_point;
        int index;
    public:
        const_iterator() :blk_point(nullptr), index(0), que_point(nullptr) {}

        const_iterator(const const_iterator &ec){
            blk_point = ec.blk_point;
            index = ec.index;
            que_point = ec.que_point;
        }

        const_iterator(const iterator &ec){
            blk_point = ec.blk_point;
            index = ec.index;
            que_point = ec.que_point;
        }

        const_iterator(block *s, int ind, const deque<T>* r):blk_point(s),index(ind),que_point(r){}

        const_iterator &operator=(const const_iterator &other){
            if (this == &other) return *this;
            blk_point = other.blk_point;
            index = other.index;
            que_point = other.que_point;
            return *this;
        }

        const_iterator operator+(const int &n) const {
            if (n < 0) return *this - (-n);
            else {
                block *r = blk_point;
                int i = index + n;//偏移后的应有下标
                if (i < r->size) {
                    const_iterator answer(r, i, que_point);
                    return answer;
                }
                else {
                    while (i >= r->size){
                        if (i == r->size && r->next == nullptr) {
                            return const_iterator(r, i, que_point);
                        }
                        else {
                            i -= r->size;
                            r = r->next;
                            if (r == nullptr) throw invalid_iterator();
                        }
                    }
                    return const_iterator (r, i, que_point);
                }
            }
        }

        const_iterator operator-(const int &n) const {
            if (n < 0) return *this +(-n);
            else {
                block *r = blk_point;
                int i = index - n;
                if (i >= 0) {
                    return const_iterator(r, i, que_point);
                }
                else {
                    while (i < 0){
                        r = r->prev;
                        if (r == nullptr) throw invalid_iterator();
                        i += r->size;
                    }
                    return const_iterator (r, i, que_point);
                }
            }
        }

        bool valid() const{
            return que_point && blk_point && index >= 0 && index < blk_point->size;
        }

        int operator-(const const_iterator &rhs) const {
            if (que_point != rhs.que_point) throw invalid_iterator();
            if (blk_point == rhs.blk_point) return index - rhs.index;
            int i = index;
            block *r = blk_point->prev;
            while (r != nullptr) {
                i += r->size;
                if (r == rhs.blk_point) return i - rhs.index;
                else r = r->prev;
            }
            i = blk_point->size - index;
            r = blk_point->next;
            while (r != nullptr) {
                if (r == rhs.blk_point) return -(i + rhs.index);
                else {
                    i += r->size;
                    r = r->next;
                }
            }
            throw runtime_error();
        }
        const_iterator& operator+=(const int &n) {
            return *this = *this + n;
        }
        const_iterator& operator-=(const int &n) {
            return *this = *this - n;
        }
        const_iterator operator++(int) {
            const_iterator answer = *this;
            *this = *this + 1;
            return answer;
        }
        const_iterator& operator++() {
            *this = *this + 1;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator answer = *this;
            *this = *this - 1;
            return answer;
        }
        const_iterator& operator--() {
            *this = *this - 1;
            return *this;
        }
        const T& operator*() const {
            if (!valid()) throw invalid_iterator();
            return blk_point->array[index][0];
        }
        const T* operator->() const noexcept {
            if (!valid()) throw invalid_iterator();
            return blk_point->array[index];
        }
        bool operator==(const iterator &rhs) const {
            if (blk_point != rhs.blk_point) return false;
            if (index != rhs.index) return false;
            return true;
        }
        bool operator==(const const_iterator &rhs) const {
            if (blk_point != rhs.blk_point) return false;
            if (index != rhs.index) return false;
            return true;
        }
        bool operator!=(const iterator &rhs) const {
            if (blk_point != rhs.blk_point) return true;
            if (index != rhs.index) return true;
            return false;
        }
        bool operator!=(const const_iterator &rhs) const {
            if (blk_point != rhs.blk_point) return true;
            if (index != rhs.index) return true;
            return false;
        }
    };
	friend class iterator;
	friend class const_iterator;
    class block{
    public:
        friend class deque<T>;
        T **array;
        block *next;
        block *prev;
        int size = 0;
    public:
        block(){
            array = new T* [2*200+10]{0};
            size = 0;
            next = nullptr;
            prev = nullptr;
        }

        ~block(){
            for(int i = 0; i < size ; ++i){
                delete array[i];
                array[i] = nullptr;
            }
            delete []array;
            array = nullptr;
        }

        void split(){
            block *n = next;
            auto add = new block;
            add->next = n;
            if (n != nullptr) n->prev = add;
            add->size = 200;
            for(int i = size-200 ; i < size ; ++i){
                add->array[i-size+200] = new T (array[i][0]);
                delete array[i];
                array[i] = nullptr;
            }
            size -= 200;

            next = add;
            add->prev = this;
        }

        void merge_next(){
            block *n = next;
            block *m = n->next;
            next = m;
            if (m != nullptr) m->prev = this;
            for(int i = size ; i < size + n->size ; ++i)
                array[i] = new T (n->array[i-size][0]);
            size += n->size;
            delete n;
        }

        void insert(const int &ind, const T &value){
            if (size == 0) {
                array[0] = new T(value);
                ++size;
                return;
            }
            else {
                array[size] = new T(array[size-1][0]);
                for(int i = size-1 ; i >= ind ; --i)
                    array[i+1][0] = array[i][0];
                array[ind][0] = value;
                ++size;
                return;
            }
        }

        void erase(const int &ind){
            if (ind == size-1) {
                delete array[ind];
                array[ind] = nullptr;
                --size;
            }
            else {
                for(int i = ind ; i < size-1 ; ++i)
                    array[i][0] = array[i+1][0];
                delete array[size-1];
                array[size-1] = nullptr;
                --size;
            }
        }
    };

    deque() {
	    head = tail = new block;
	    head->size = 0;
	    head->next = nullptr;
	    head->prev = nullptr;
	    head->size = 0;
	    all_size = 0;
	}

	deque(const deque &other) {
        all_size = 0;
        head = new block;
        tail = head;
        block *p = other.head;
        while (true) {
            for(int i = 0 ; i < p->size ; ++i)
                push_back(p->array[i][0]);
            if (p->next == nullptr) {
                p = head;
                while (p->next != nullptr) p = p->next;
                tail = p;
                break;
            }
            else p = p->next;
        }
	}

	~deque() {
	    block *p, *q;
	    p = head;
	    q = head->next;
        while (q != nullptr) {
            delete p;
            p = q;
            q = p->next;
        }
        delete p;
        head = nullptr;
        tail = nullptr;
	}

	deque &operator=(const deque &other) {
        if (this == &other) return *this;
        del();
        all_size = 0;
        head = new block; tail = head;
        head->size = 0;
        head->next = nullptr;
        head->prev = nullptr;
        block *p = other.head;
        while (true) {
            for(int i = 0 ; i < p->size ; ++i)
                push_back(p->array[i][0]);
            if (p->next == nullptr) {
                p = head;
                while (p->next != nullptr) p = p->next;
                tail = p;
                break;
            }
            else p = p->next;
        }
        return *this;
	}

	T & get_val(const size_t &pos) const{
        if (pos >= all_size) throw index_out_of_bound();
        block *p = head;
        int index = pos;
        while (p != nullptr) {
            if (index >= p->size){
                index -= p->size;
                p = p->next;
            }
            else return p->array[index][0];
        }
    }
	T & at(const size_t &pos) {
        return get_val(pos);
	}
	const T & at(const size_t &pos) const {
        return get_val(pos);
	}
	T & operator[](const size_t &pos) {
        return get_val(pos);
	}
	const T & operator[](const size_t &pos) const {
        return get_val(pos);
	}

	const T & front() const {
        if (all_size == 0) throw container_is_empty();
        return head->array[0][0];
	}
	const T & back() const {
        if (all_size == 0) throw container_is_empty();
        return tail->array[tail->size-1][0];
	}

	iterator begin() {
	    iterator answer(head, 0, this);
        return answer;
	}
	const_iterator cbegin() const{
        return const_iterator (head, 0, this);
	}
	iterator end() {
	    iterator answer(tail, tail->size, this);
        return answer;
	}
	const_iterator cend() const{
        return const_iterator (tail, tail->size, this);
	}

	bool empty() const {
        if (all_size == 0) return true;
        else return false;
	}
	size_t size() const {
        return all_size;
	}
	void clear() {
        del();
        head = new block; tail = head;
        head->next = nullptr;
        head->prev = nullptr;
        all_size = 0;
	}

	void del() {
        block *p = head, *q = p->next;
        while (q != nullptr) {
            delete p;
            p = q;
            q = p->next;
        }
        delete p;
        head = nullptr;
        tail = nullptr;
        all_size = 0;
    }

	iterator insert(iterator pos, const T &value) {
        if (this != pos.que_point) throw invalid_iterator();
        if (!pos.blk_point || !pos.que_point) throw invalid_iterator();
        if (pos.index < 0 || pos.index > pos.blk_point->size) throw invalid_iterator();
        pos.blk_point->insert(pos.index, value); ++all_size;
        if (pos.blk_point->size >= 2*200 ){
            pos.blk_point->split();
            if (tail->next != nullptr) tail = tail->next;
        }
        if (pos.index >= pos.blk_point->size) return iterator(pos.blk_point->next, pos.index - pos.blk_point->size, this);
        else return iterator(pos.blk_point, pos.index, this);
	}

	iterator erase(iterator pos) {
        if (this != pos.que_point) throw invalid_iterator();
        if (!pos.valid()) throw invalid_iterator();
        pos.blk_point->erase(pos.index);
        --all_size;
        if (pos.blk_point == head) {
            if (pos.blk_point->next != nullptr && pos.blk_point->size + pos.blk_point->next->size <= 200){
                if (pos.blk_point->next == tail) tail = tail->prev;
                pos.blk_point->merge_next();
                return iterator(pos.blk_point, pos.index, this);
            }
            else if (pos.blk_point->next != nullptr && pos.blk_point->size == 0){
                block *p = head;
                block *q = head->next;
                q->prev = p->prev;
                head = q;
                delete p;
                return iterator(head, 0, this);
            }//删光head，head后移
            else if (pos.blk_point->next != nullptr && pos.index == pos.blk_point->size){
                return iterator(pos.blk_point->next, 0, this);
            }//删掉块中最后一位，返回后移
            else return iterator(pos.blk_point, pos.index, this);//单节点
        }
        else if (pos.blk_point == tail) {
            if (pos.blk_point->prev != nullptr && pos.blk_point->size + pos.blk_point->prev->size <= 200){
                tail = pos.blk_point->prev;
                iterator answer(pos.blk_point->prev, pos.index + pos.blk_point->prev->size, this);
                pos.blk_point->prev->merge_next();
                return answer;
            }
            else if (pos.blk_point->next != nullptr && pos.blk_point->size == 0){
                block *p = tail;
                block *q = tail->prev;
                q->next = p->next;
                tail = q;
                delete p;
                return iterator(tail, tail->size, this);
            }//删光tail，tail前移
            return iterator(pos.blk_point, pos.index, this);//单节点
        }
        else {
            if (pos.blk_point->prev == nullptr || pos.blk_point->next == nullptr) throw invalid_iterator();
            if (pos.blk_point->size + pos.blk_point->next->size <= 200){
                if (pos.blk_point->next == tail) tail = tail->prev;
                pos.blk_point->merge_next();
                return iterator(pos.blk_point, pos.index, this);
            }//向后merge，无需判断是否delete块尾
            else if (pos.blk_point->size + pos.blk_point->prev->size <= 200){
                iterator answer;
                if (pos.index == pos.blk_point->size) answer = iterator(pos.blk_point->next, 0, this);
                else answer = iterator(pos.blk_point->prev, pos.index + pos.blk_point->prev->size, this);
                pos.blk_point->prev->merge_next();
                return answer;
            }//向前merge，需要判断是否delete块尾

            else if (pos.blk_point->size == 0){
                block *p = pos.blk_point->prev;
                block *q = pos.blk_point->next;
                p->next = q;
                q->prev = p;
                delete pos.blk_point;
                pos.blk_point = nullptr;
                return iterator(q, 0, this);
            }//删光块，删除块
            else if (pos.index == pos.blk_point->size) return iterator(pos.blk_point->next, 0, this);//删掉块中最后一位，返回后移
            else return iterator(pos.blk_point, pos.index, this);
        }
	}

	void push_back(const T &value) {
	    insert(end(), value);
	}
	void pop_back() {
        if (empty()) throw container_is_empty();
        erase(end()-1);
	}
	void push_front(const T &value) {
        insert(begin(), value);
	}
	void pop_front() {
	    if (empty()) throw container_is_empty();
        erase(begin());
	}
};

}

#endif
