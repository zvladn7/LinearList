#include <iostream>
#include <algorithm>


struct ElementOfList {
	ElementOfList(int num, ElementOfList *prev)
		: number_(num), next_(0), prev_(prev)
	{
	}

	int number_;
	ElementOfList * next_;
	ElementOfList * prev_;
};

class LinearList {
public:
LinearList()
	: head_(new  ElementOfList(0,0)), size_(0)
{
	tail_ = head_;
}

~LinearList()
{
	ElementOfList * time = head_;
	for (; head_ != 0;) {
		head_ = head_->next_;
		delete time;
		time = head_;
	}
	std::cout << "---------------------" << std::endl;
	std::cout << "---Destruct object---" << std::endl;
	std::cout << "---------------------" << std::endl;
}

LinearList(LinearList const & copy)
	: head_(new ElementOfList(0,0)), size_(0)
{
	tail_ = head_;
	size_ = copy.size();
	for (int i = 0; i != size_; ++i) {
		this->add(copy.get(i));
	}
}

LinearList &operator= (LinearList const & copy)
{
	if (&copy != this)
	{
		LinearList(copy).swap(*this);
	}
	return *this;
}

ElementOfList * front()
{
	return head_->next_;
}

ElementOfList * back()
{
	return tail_;
}

void swap(LinearList  & copy)
{
	std::swap(copy.size_,size_);
	std::swap(copy.head_,head_);
	std::swap(copy.tail_,tail_);
}

void add(int num)
{
	ElementOfList * tmp = new ElementOfList(num, tail_);
	tail_->next_ = tmp;
	tmp->prev_= tail_;
	tail_ = tmp;
	size_++;
}

void insert(int num, int index)
{
	ElementOfList * tmp = new ElementOfList(num,0);
	ElementOfList * running = head_;
	for (int i = 0; i != size_; ++i)
	{
		if (index == i) {
			if (running->next_ != 0)
				running->prev_ = tmp;
			tmp->next_ = running->next_;
			tmp->prev_ = running;
			running->next_ = tmp;
			size_++;
			break;
		}
		running = running->next_;
	}
}

int getLast() const
{
	return tail_->number_;
}

int get(int index) const
{
	ElementOfList * tmp = this->head_->next_;
	for (int i = 0; i < size_; ++i) {
		if (i == index)
			return tmp->number_;
		tmp = tmp->next_;
	}
	return -1;
}

void print() const
{
	for (int i = 0; i != size_; ++i)
	{
		std::cout << get(i) << " ";
	}
	std::cout << std::endl;
}

bool erase(int index)
{
	ElementOfList * prev = this->head_;
	ElementOfList * curr = this->head_->next_;
	for (int i = 0; i < size_; ++i) {
		if (i == index) {
			curr->next_->prev_ = prev;
			prev->next_ = curr->next_;
			delete curr;
		}
		prev = curr;
		curr = curr->next_;
	}
	size_--;
	return false;
}

int size() const
{
	return size_;
}

bool empty()
{
	return (size_ == 0) ? true : false;
}

private:
ElementOfList * head_;
ElementOfList * tail_;
int size_;
};

int main() {
	LinearList * checkwork = new LinearList();
	std::cout << "first" << std::endl;
	for (int i = 0; i < 5; ++i) {
		int time = 0;
		std::cin >> time;
		checkwork->add(time);
	}
	std::cout << "second" << std::endl;
	checkwork->print();
	std::cout << "----erase----" << std::endl;
	checkwork->erase(2);
	checkwork->print();
	std::cout << "third" << std::endl;
	checkwork->insert(11,2);
	checkwork->print();
	checkwork->~LinearList();
	return 0;
}
