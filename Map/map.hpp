#ifndef MY_MAP_HPP
#define MY_MAP_HPP

#include<iostream>
#include<utility>
#include<string.h>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<stdexcept>

constexpr int _LEVELS = 100;
namespace cppshizoid::tools::map{

	template <typename K, typename M>
	class Map;

	template <typename K, typename M>
	class Node{
		public:
			friend class Map<K, M>;
			typedef std::pair<const K, M> ValueType;

			Node(std::size_t _level){
				int _temp_level = _level+1;
				_forward_links = new Node*[_temp_level];
				size_t _total_size = sizeof(Node*)*(_temp_level);
				memset(_forward_links, '\0', _total_size);
				_value = nullptr;
				_prev = nullptr;
			}

			Node(std::size_t _level, const ValueType& _val){
				int _temp_level = _level+1;
				_forward_links = new Node*[_temp_level];
				size_t _total_size = sizeof(Node*)*(_temp_level);
				memset(_forward_links, '\0', _total_size);
				_value = new std::pair<const K, M>(_val);
				_prev = nullptr;
			}

			~Node(){
				delete [] _forward_links;
				delete _value;
			}

		private:
			Node** _forward_links;
			Node* _prev;
			ValueType *_value;
	};

	template <typename K, typename M>
	class Map{
		public:

			typedef std::pair<const K, M> ValueType;

			class Iterator{
				public:
					Iterator(const Iterator& _iter) : _cur(_iter.get_cur()){}
					Iterator(Node<K, M>* _node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					Iterator& operator=(const Iterator& _iter){
						_cur = _iter.get_cur();
						return *this;
					}
					Iterator& operator++(){
						if(_cur == NULL) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					Iterator operator++(int){
						Map<K, M>::Iterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_forward_links[0];
						return _this;
					}
					Iterator& operator--(){
						if(_cur == nullptr) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					Iterator operator--(int){
						 Map<K, M>::Iterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ValueType& operator*() const{
						return *_cur->_value;
					}
					ValueType* operator->() const{
						return _cur->_value;
					}

					~Iterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;

			};

			class ConstIterator{
				public:
					ConstIterator(const ConstIterator& _citer) : _cur(_citer.get_cur()){}
					ConstIterator(const Iterator& _iter) : _cur(_iter.get_cur()){}
					ConstIterator(Node<K, M> *_node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					ConstIterator& operator=(const ConstIterator& _citer){
						_cur = _citer.get_cur();
						return *this;
					}
					ConstIterator& operator++(){
						if(_cur == nullptr) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					ConstIterator operator++(int){
						Map<K, M>::ConstIterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_forward_links[0];
						return _this;
					}
					ConstIterator& operator--(){
						if(_cur == nullptr) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					ConstIterator operator--(int){
						Map<K, M>::ConstIterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					const ValueType& operator*() const{
						return *_cur->_value;
					}
					const ValueType* operator->() const{
						return _cur->_value;
					}

					~ConstIterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;
			};

			class ReverseIterator{
				public:
					ReverseIterator(const ReverseIterator& _riter) : _cur(_riter.get_cur()){}
					ReverseIterator(Node<K, M> *_node) : _cur(_node){}
					Node<K, M>* get_cur() const{return _cur;}

					ReverseIterator& operator=(const ReverseIterator& _riter){
						_cur = _riter.get_cur();
						return *this;
					}
					ReverseIterator& operator++(){
						if(_cur == nullptr) return *this;
						_cur = _cur->_prev;
						return *this;
					}
					ReverseIterator operator++(int){
						 Map<K, M>::ReverseIterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ReverseIterator& operator--(){
						if(_cur == nullptr) return *this;
						_cur = _cur->_forward_links[0];
						return *this;
					}
					ReverseIterator operator--(int){
						Map<K, M>::ReverseIterator _this = *this;
						if(_cur == nullptr) return _this;
						_cur = _cur->_prev;
						return _this;
					}
					ValueType& operator*() const{
						return *_cur->_value;
					}
					ValueType* operator->() const{
						return _cur->_value;
					}

					~ReverseIterator(){
						_cur = nullptr;
					}

				private:
					Node<K, M> *_cur;
			};

			Map(){
				map_ctor();
			}

			Map(const Map& _map){
				map_ctor();
				Node<K, M> *_temp = _map.get_head()->_forward_links[0];
				while(_temp != _map.get_tail()){
					ValueType& _val = *(_temp->_value);
					insert(_val);
					_temp = _temp->_forward_links[0];
				}
			}

			Map(std::initializer_list<std::pair<const K, M>> _l){
				map_ctor();
				auto _iter = _l.begin();
				while(_iter != _l.end()){
					insert(*_iter);
					_iter++;
				}
			}

			~Map(){
				Node<K, M> *_temp_head = _head;
				Node<K, M> *_temp;
				while(_temp_head != nullptr){
					_temp = _temp_head->_forward_links[0];
					delete _temp_head;
					_temp_head = _temp;
				}
			}

			Node<K, M>* get_head() const{
				return _head;
			}
			Node<K, M>* get_tail() const{
				return _tail;
			}

			void map_ctor(){
				init_head_tail();
				init_assign_head_tail();
				init_size();
			}

			void init_head_tail(){
				_head = new Node<K, M>(_LEVELS);
				_tail = new Node<K, M>(_LEVELS);
			}
			void init_assign_head_tail(){
				_head->_forward_links[0] = _tail;
				_tail->_prev = _head;
				_head->_prev = nullptr;
				_tail->_forward_links[0] = nullptr;
			}
			void init_size(){
				 _max = 0;
				_size = 0;
			}

			void reset_head_tail(){
				_head = nullptr;
				_tail = nullptr;
			}
			void reset_size(){
				_max = 0;
				_size = 0;
			}

			Iterator find(const K& _key){
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == nullptr){
					return Map<K, M>::Iterator(_tail);
				}
				return Map<K, M>::Iterator(_temp_head);
			}

			ConstIterator find(const K& _key) const{
				 Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == nullptr){
					return Map<K, M>::ConstIterator(_tail);
				}
				return Map<K, M>::ConstIterator(_temp_head);
			}

			Iterator begin(){return Map<K, M>::Iterator(_head->_forward_links[0]);}
			Iterator end(){return Map<K, M>::Iterator(_tail);}
			ConstIterator begin() const{return ConstIterator(_head->_forward_links[0]);}
			ConstIterator end() const{return ConstIterator(_tail);}
			ReverseIterator rbegin(){return ReverseIterator(_tail->_prev);}
			ReverseIterator rend(){return ReverseIterator(_head);}

			std::size_t size() const{return _size;}
			bool empty() const{return (_size == 0)? true : false;}

			M& at(const K& _key){
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == nullptr){
					throw std::out_of_range("out of range");
				}
				else return _temp_head->_value->second;

			}

			const M& at(const K& _key) const{
				Node<K, M> *_temp_head = find_at_bottom(_key);
				if(_temp_head == nullptr){
					throw std::out_of_range("out of range");
				}
				else return _temp_head->_value->second;
			}

			friend bool operator==(const Iterator& _iter1, const Iterator& _iter2){
				return (_iter1.get_cur() == _iter2.get_cur())? true : false;
			}
			friend bool operator!=(const Iterator& _iter1, const Iterator& _iter2){
				return (_iter1.get_cur() != _iter2.get_cur())? true : false;
			}
			friend bool operator==(const ConstIterator& _citer1, const ConstIterator& _citer2){
				return (_citer1.get_cur() == _citer2.get_cur())? true : false;
			}
			friend bool operator!=(const ConstIterator& _citer1, const ConstIterator& _citer2){
				return (_citer1.get_cur() != _citer2.get_cur())? true : false;
			}
			friend bool operator==(const ReverseIterator& _riter1, const ReverseIterator& _riter2){
				return (_riter1.get_cur() == _riter2.get_cur())? true : false;
			}
			friend bool operator!=(const ReverseIterator& _riter1, const ReverseIterator& _riter2){
				return (_riter1.get_cur() != _riter2.get_cur())? true : false;
			}
			friend bool operator==(const Iterator& _iter, const ConstIterator& _citer){
				return (_iter.get_cur() == _citer.get_cur())? true : false;
			}
			friend bool operator==(const ConstIterator& _citer, const Iterator& _iter){
				return (_citer.get_cur() == _iter.get_cur())? true : false;
			}
			friend bool operator!=(const Iterator& _iter, const ConstIterator& _citer){
				return (_iter.get_cur() != _citer.get_cur())? true : false;
			}
			friend bool operator!=(const ConstIterator& _citer, const Iterator& _iter){
				return (_citer.get_cur() != _iter.get_cur())? true : false;
			}

			void clear();

			M& operator[](const K&);

			size_t random_level(Node<K, M>**);

			Node<K, M>* find_at_bottom(const K& _key) const;

			std::pair<Iterator, bool> insert(const ValueType&);

			template <typename IT_T>
			void insert(IT_T range_beg, IT_T range_end);

			void erase(Iterator);

			void erase(const K&);

			Map& operator=(const Map&);

			bool operator!=(const Map&) const;
			template <typename Key, typename Mapped>
			friend bool operator==(const Map<Key, Mapped>&, const Map<Key, Mapped>&);
			template <typename Key, typename Mapped>
			friend bool operator<(const Map<Key, Mapped>&, const Map<Key, Mapped>&);
			template <typename Key, typename Mapped>
			friend bool operator!=(const Map<Key, Mapped>&, const Map<Key, Mapped>&);

		private:
			Node<K, M>* _head;
			Node<K, M>* _tail;
			std::size_t _max;
			std::size_t _size;
	};

	template <typename K, typename M>
	M& Map<K, M>::operator[](const K& _key){
		Node<K, M> *_temp_head = find_at_bottom(_key);
		if(_temp_head == nullptr){
			Map<K, M>::Iterator _iter = insert(std::make_pair(_key, M())).first;
			return _iter.get_cur()->_value->second;
		}
		return _temp_head->_value->second;
	}

	template <typename K, typename M>
	size_t Map<K, M>::random_level(Node<K, M>** _nodes){
		size_t _level = 0;
		while(_level < _LEVELS && rand() < RAND_MAX*0.5){
			++_level;
		}
		if(_level > _max){
			size_t _temp = _max+1;
			while(_temp <= _level){
				_nodes[_temp] = _head;
				++_temp;
			}
			_max = _level;
		}
		return _level;
	}

	template <typename K, typename M>
	Map<K, M>& Map<K, M>::operator=(const Map<K, M>& _map){
		if(this == &_map){
			return *this;
		}
		Node<K, M> *_temp_head = _head;
		Node<K, M> *_temp;
		while(_temp_head != nullptr){
			_temp = _temp_head->_forward_links[0];
			delete _temp_head;
			_temp_head = nullptr;
			_temp_head = _temp;
		}

		map_ctor();
		Node<K, M> *_first = _map.get_head()->_forward_links[0];
		if(_first == _map.get_tail()) return *this;
		while(_first != _map.get_tail()){
			insert(*(_first->_value));
			_first = _first->_forward_links[0];
		}
		return *this;
	}

	template <typename K, typename M>
	std::pair<typename Map<K, M>::Iterator, bool> Map<K, M>::insert(const std::pair<const K, M>& _val){
		const K& _key = _val.first;
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != nullptr && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
		Node<K, M> *_first_updated = _updated[0];
		_first_updated = _first_updated->_forward_links[0];
		if(_first_updated->_value != nullptr && _first_updated->_value->first == _val.first){
			delete [] _updated;
			return std::make_pair(Map<K, M>::Iterator(_first_updated), false);
		}

		size_t _level = random_level(_updated);
		_first_updated = nullptr;
		_first_updated = new Node<K, M>(_level, _val);
		i = 0;
		while(i <= _level){
			_first_updated->_forward_links[i] = _updated[i]->_forward_links[i];
			_updated[i]->_forward_links[i] = _first_updated;
			++i;
		}
		_first_updated->_prev = _updated[0];
		if(_first_updated->_forward_links[0] != _tail){
			_first_updated->_forward_links[0]->_prev = _first_updated;
		}
		else{
			_tail->_prev = _first_updated;
		}
		++_size;
		delete [] _updated;
		return std::make_pair(Map<K, M>::Iterator(_first_updated), true);
	}

	template <typename K, typename M>
	template <typename IT_T>
	void Map<K, M>::insert(IT_T range_beg, IT_T range_end){
		auto _iter = range_beg;
		while(_iter != range_end){
			insert(*_iter);
			++_iter;
		}
	}

	template <typename K, typename M>
	void Map<K, M>::erase(const K& _key){
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != nullptr && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
                Node<K, M> *_first_updated = _updated[0];
                _first_updated = _first_updated->_forward_links[0];
                if(_first_updated->_value->first == _key){
                        i = 0;
                        while(i <= _max && _updated[i]->_forward_links[i] == _first_updated){
                                _updated[i]->_forward_links[i] = _first_updated->_forward_links[i];
                                ++i;
                        }

                        if(_first_updated->_forward_links[0] != _tail){
                                _first_updated->_forward_links[0]->_prev = _first_updated->_prev;
                        }
                        else{
                                _tail->_prev = _first_updated->_prev;
                                _first_updated->_prev->_forward_links[0] = _tail;
                        }

                        delete _first_updated;
                        while(_max > 0 && _head->_forward_links[_max] == nullptr){
                                --_max;
                        }
                        --_size;
                        delete [] _updated;
                }
                else{
                        throw std::out_of_range("out of range");
                }
	}

	template <typename K, typename M>
	void Map<K, M>::erase(Map<K, M>::Iterator _iter){
		const K& _key = _iter.get_cur()->_value->first;
		Node<K, M> *_temp = _head;
		Node<K, M> **_updated = new Node<K, M>* [_LEVELS+1];
		memset(_updated, '\0', sizeof(Node<K, M>*)*(_LEVELS+1));
		size_t i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != nullptr && _temp->_forward_links[i]->_value->first < _key){
				_temp = _temp->_forward_links[i];
			}
			_updated[i] = _temp;
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_updated[0] = _temp;
                Node<K, M> *_first_updated = _updated[0];
                _first_updated = _first_updated->_forward_links[0];
                if(_first_updated->_value->first == _key){
                        i = 0;
                        while(i <= _max && _updated[i]->_forward_links[i] == _first_updated){
                                _updated[i]->_forward_links[i] = _first_updated->_forward_links[i];
                                ++i;
                        }

                        if(_first_updated->_forward_links[0] != _tail){
                                _first_updated->_forward_links[0]->_prev = _first_updated->_prev;
                        }
                        else{
                                _tail->_prev = _first_updated->_prev;
                                _first_updated->_prev->_forward_links[0] = _tail;
                        }

                        delete _first_updated;
                        while(_max > 0 && _head->_forward_links[_max] == nullptr){
                                --_max;
                        }
                        --_size;
                        delete [] _updated;
                }
                else{
                        throw std::out_of_range("out of range");
                }
	}

	template <typename K, typename M>
	void Map<K, M>::clear(){
		Node<K, M> *_temp_head = _head;
		Node<K, M> *_temp;
		while(_temp != nullptr){
			_temp = _temp_head->_forward_links[0];
			delete _temp_head;
			_temp_head = _temp;
		}
		reset_size();
		reset_head_tail();
		map_ctor();
	}

	template <typename K, typename M>
	Node<K, M>* Map<K, M>::find_at_bottom(const K& _key) const{
		Node<K, M> *_temp = _head;
		int i = _max;
		while(i >= 1){
			while(_temp->_forward_links[i] != nullptr && _temp->_forward_links[i]->_value->first < _key){
                                _temp = _temp->_forward_links[i];
                        }
			i--;
		}

		while(_temp->_forward_links[0] != _tail && _temp->_forward_links[0]->_value->first < _key){
			_temp = _temp->_forward_links[0];
		}
		_temp = _temp->_forward_links[0];
		if(_temp == _tail) return nullptr;
		if(_temp != nullptr){
			if(_temp->_value->first == _key)
				return _temp;
		}
		return nullptr;
	}

	template <typename K, typename M>
	bool Map<K, M>::operator!=(const Map<K, M>& _map) const{
		if(*this == _map) return false;
		return true;
	}

	template <typename K, typename M>
	bool operator==(const Map<K, M>& _map1, const Map<K, M>& _map2){
		if(_map1.size() != _map2.size()) return false;
		auto _iter1 = _map1.begin();
		auto _iter2 = _map2.begin();
		while(_iter1 != _map1.end() && _iter2 != _map2.end()){
			if(*_iter1 != *_iter2){
				return false;
			}
			++_iter1;
			++_iter2;
		}
		return true;
	}

	template <typename K, typename M>
	bool operator!=(const Map<K, M>& _map1, const Map<K, M>& _map2){
		return !(_map1 == _map2);
	}

	template <typename K, typename M>
	bool operator<(const Map<K, M>& _map1, const Map<K, M>& _map2){
		size_t _size1 = _map1.size();
		size_t _size2 = _map2.size();
		if(_size1 < _size2) return true;
		if(_size2 < _size1) return false;

		auto _iter1 = _map1.begin();
		auto _iter2 = _map2.begin();
		while(_iter1 != _map1.end() && _iter2 != _map2.end()){
			bool _less = (*_iter1).first < (*_iter2).first;
			bool _less2 = (*_iter2).first < (*_iter1).first;
			if(_less) return true;
			if(_less2) return false;
			++_iter1;
			++_iter2;
		}

		return false;
	}
}
#endif //MY_MAP_HPP
