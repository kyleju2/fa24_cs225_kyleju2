template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/*
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
	while (head_ != NULL) {
		ListNode* curr = head_;
		head_ = curr->next;
		delete curr;
	}

	length_ = 0;
	tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  // empty list conditions
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  // empty list conditions
  if (head_ == NULL) {
    head_ = newNode;
  }
  
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode* start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
	ListNode* curr = start;
	
	for (int i = 0; i < splitPoint && curr != NULL; i++) {
		curr = curr->next;
	}

	if (curr != NULL && curr->prev != NULL) {
		curr->prev->next = NULL;
		curr->prev = NULL;
	}

	return curr;
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
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode* curr = head_;

  while (curr != NULL) {
	curr = curr->next; // skipping first node

	if (curr == NULL || curr->next == NULL) break; // bounds check

	ListNode* tmp = curr->next; // store ref to next node

	tail_->next = curr; // updating tail_ pointer
	curr->next = NULL; // new tail points to NULL
	curr->prev->next = tmp;
	curr->prev = tail_; // new tail_ points to old tail_ 
	tail_ = curr; // update list class tail_ 
	curr = tmp;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

  if(startPoint == NULL || endPoint == NULL || startPoint == endPoint) return;
  
  ListNode* startNode = startPoint;
  ListNode* startPrev = startPoint->prev;
  ListNode* endNext = endPoint->next;

  while (startPoint != endPoint) {
    ListNode* curr = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = curr;
    startPoint = startPoint->prev;
  }
  
  ListNode* tmp = startPoint->prev;
  startPoint->prev = startPrev;
  startPoint->next = tmp;
  endPoint = startNode;
  endPoint->next = endNext;

  if(startPrev == NULL)
    head_ = startPoint;
  else
    startPrev->next = startPoint;
  if(endNext == NULL)
    tail_ = endPoint;
  else
    endNext->prev = endPoint;
}

 


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */

template <typename T>
void List<T>::reverseNth(int n) {
  // edge cases
  if (n <= 1 || head_ == nullptr) return;  // No reversal needed for n <= 1 or an empty list
  if (n >= length_) {
    reverse();
    return;
  }
  // variables for traversal 
  ListNode* start = head_;
  ListNode* end = head_;
  

  while (start != nullptr) {
      // Move the end pointer n-1 steps forward, or until the end of the list
      for (int i = 1; i < n && end->next != nullptr; ++i) {
          end = end->next;
      }

      // Reverse the block from start to end
      reverse(start, end);

      // Move start and end to the next block
      start = end->next;  // Move to the next block
      end = start;  // Reset end to the new start
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
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

template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  if (first == NULL) return second;
  if (second == NULL) return first;

  ListNode* mergedHead = NULL;
  ListNode* curr = NULL;

  if (first->data < second->data) {
    mergedHead = first;
    first = first->next;
  } 
  else {
    mergedHead = second;
    second = second->next;
  }

  curr = mergedHead;

  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      curr->next = first;
      first->prev = curr;
      first = first->next;
    } 
    else {
      curr->next = second;
      second->prev = curr;
      second = second->next;
    }
    curr = curr->next;
  }

  if (first != NULL) {
    curr->next = first;
    first->prev = curr;
  } 
  else if (second != NULL) {
    curr->next = second;
    second->prev = curr;
  }

  return mergedHead;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (chainLength <= 1) return start;

  int midpt = chainLength / 2;

  ListNode* middle = split(start, midpt); // split list using split()
  start = mergesort(start, midpt); // recursive call on mergesort from the split point
  middle = mergesort(middle, chainLength - midpt);

  return merge(start, middle);
}
