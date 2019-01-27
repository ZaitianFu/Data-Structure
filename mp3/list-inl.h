/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
 

template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
   while (head_)
    {
        tail_= head_->next;
        delete head_;
        head_ = tail_;
	head_ =NULL;
    }
    length_=0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
 
  //Graded in MP3.1list-inl.h]
    length_++;

  	if (head_ == NULL)
	{
		head_ = new ListNode(ndata);
		head_->prev = NULL;
		head_->next = NULL;
		tail_ = head_;
		tail_->prev = NULL;
		tail_->next = NULL;
	}
	else
	{
		head_->prev = new ListNode(ndata);
		ListNode * temp = head_;
		head_ = head_->prev;
		head_->prev = NULL;
		head_->next = temp;
	}	
    }
    



/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
   length_++;

	if (tail_ == NULL)
	{
		tail_ = new ListNode(ndata);
		tail_->prev = NULL;
		tail_->next = NULL;
		head_ = tail_;
		head_->next = NULL;
		head_->prev = NULL;
	}
	else
	{
		tail_->next = new ListNode(ndata);
		ListNode * temp = tail_;
		tail_ = tail_->next;
		tail_->next = NULL;
		tail_->prev = temp;
	}
   
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {

if (head_ == NULL || tail_ == NULL)
		return;
		
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
    ListNode *  temp = NULL;
	ListNode *  curr = startPoint;
	ListNode *  nextEnd = endPoint->next;
	ListNode *  prevStart = startPoint->prev;
	
	
	while (curr != nextEnd)
	{
		temp = curr->prev;				
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}

	if (temp != NULL)  
	{
		temp = startPoint;				
		startPoint = endPoint;
		endPoint = temp;
	}
    
	endPoint->next = nextEnd;			

	if (nextEnd != NULL)				
	{
		nextEnd->prev = endPoint;
	}

	startPoint->prev = prevStart;

	if (prevStart != NULL)
	{
		prevStart->next = startPoint;
	} 
}

 /**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (head_ == NULL || tail_ == NULL || n<=0)
		return;

    ListNode * startPoint = head_;
	ListNode * endPoint = head_;

	if (n >= size())
	{
		reverse();
		return;
	}

	for (int i=1; i<n; i++)
	{	
		if (endPoint->next != NULL)
		endPoint = endPoint->next;
	}
	reverse(head_,endPoint);      				

	while (endPoint->next != NULL)
	{
		startPoint = endPoint->next;

		for (int i=1; i<=n; i++)
		{	
			if (endPoint->next != NULL)
			endPoint = endPoint->next;
		}

		reverse(startPoint,endPoint);  
	
	}
	
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(length_ <= 1)
	return;
   ListNode* track = head_;
   ListNode* hold = track->next;
   while(track->next->next != NULL && track->next != NULL )
   {
	track = track->next;
	track->prev->next = track->next;
	track->next->prev = track->prev;
	hold = track->next;
	tail_->next = track;
	track->prev = tail_;
	track->next = NULL;
	tail_ = track;
	track = hold;
   }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    
    ListNode * curr= start;
    for (int i=0; i<splitPoint; i++)
     { 
        if (curr->next != NULL)
    		curr= curr->next;   
	 }	
	 
	 if (curr->prev != NULL)
		(curr->prev)->next = NULL;
	 
	 curr->prev = NULL;
	
	return curr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  
  	if(first == NULL||second == NULL)
	return NULL;
	
	if(first == second)
	return first;
	
	ListNode * newFirst = first;
	ListNode * newSecond = second;
	ListNode * newHead = first;
	if(first->data < second->data)
	{
		newFirst = first->next;
	}	
	else
	{
		newHead = second;
		newSecond = second->next;
	}
	ListNode * result = newHead;
	
	while(newFirst != NULL && newSecond != NULL)
	{
		if(newFirst->data < newSecond->data || newSecond == NULL)
		{
			result->next = newFirst;
			newFirst->prev =result;
			result = newFirst;
			newFirst = newFirst->next;
		}
		else
		{
			result->next = newSecond;
			newSecond->prev = result;
			result = newSecond;
			newSecond = newSecond->next;
		}
	}
	if (newFirst == NULL)
	{
		result->next = newSecond;
		newSecond->prev = result; 
	}
	else
	{
		result->next = newFirst;
		newFirst->prev = result; 
	}
	
	
	return newHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength <= 1)
		return start;

	int mid = chainLength/2;
	ListNode * left = start;
	ListNode * right = split(start,mid);

	left = mergesort(left,mid);
	right = mergesort(right,chainLength - mid);
	
    return merge(left,right); 
}
