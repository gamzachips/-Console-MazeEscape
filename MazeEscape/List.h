#pragma once

template<typename T>
struct Node
{
	Node(T data) : _data(data) {}
	T _data;
	Node* _next;
	Node* _prev;
};

template<typename T>
class List
{
public:
	class iterator
	{
	public:
		iterator(Node<T>* node) : _current(node) {}
		bool operator!=(const iterator& other) const
		{
			return _current != other._current;
		}
		iterator& operator++()
		{
			_current = _current->_next;
			return *this;
		}
		T operator*()
		{
			return _current->_data;
		}
	private:
		Node<T>* _current;
		friend class List<T>;
	};

	List()
	{
		_head = new Node<T>(T{});
		_tail= new Node<T>(T{});
		_head->_prev = _head->_next = _tail;
		_tail->_prev = _tail->_next = _head;
	}
	~List()
	{
		//메모리 해제
		Node<T>* now = _head;
		while (_head->_next != _tail)
		{
			erase(_head->_next);
		}
		delete _head;
		delete _tail;
	}
	iterator begin() const
	{
		return iterator(_head->_next);
	}
	iterator end() const
	{
		return iterator(_tail);
	}
	void push_back(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		newNode->_prev = _tail->_prev;
		newNode->_next = _tail;
		_tail->_prev->_next = newNode;
		_tail->_prev = newNode;
	}
	iterator erase(const iterator& it)
	{
		if (it._current == _head || it._current == _tail)
			return end();
		iterator retIt(it._current->_next);
		it._current->_prev->_next = it._current->_next;
		it._current->_next->_prev = it._current->_prev;
		  
		it._current->_prev = nullptr;
		it._current->_next = nullptr;

		delete it._current;

		return retIt;
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
};

