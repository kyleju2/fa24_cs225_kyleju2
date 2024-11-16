/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.empty())
        return (T());
    T res = s.top();
    T tmp = s.top();
    s.pop();
    res += sum(s);
    s.push(tmp);
    return res; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of parentheses, curly/square brackets and other
 * characters. This function will return true if and only if the bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello=](){}" is balanced, "{()[{a}]}" is
 * balanced, "[})" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * unbalanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    std::stack<char> past;
    
    while (!input.empty()) {
        char current = input.front();
        input.pop(); // Remove the front element from the queue
        
        // Push opening brackets to the stack
        if (current == '(' || current == '[' || current == '{') {
            past.push(current);
        }
        // For closing brackets, check if the stack is not empty and matches the corresponding opening bracket
        else if (current == ')' || current == ']' || current == '}') {
            if (past.empty()) {
                return false; // Closing bracket with no corresponding opening bracket
            }
            char top = past.top();
            if ((current == ')' && top == '(') || 
                (current == ']' && top == '[') || 
                (current == '}' && top == '{')) {
                past.pop(); // Matched, pop the top of the stack
            } else {
                return false; // Mismatched brackets
            }
        }
    }

    // If the stack is empty at the end, all brackets are matched
    return past.empty();
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{   
    stack<T> s;
    queue<T> q2;
    int block_size = 1;
    while (!q.empty()) {
        if (block_size % 2 == 1) {
            for (int i = 0; i < block_size; i++) {
                if (!q.empty()) {
                    q2.push(q.front());
                    q.pop();
                }
            }
        } else if (block_size % 2 == 0) {
            for (int i = 0; i < block_size; i++) {
                if (!q.empty()) {
                    s.push(q.front());
                    q.pop();
                }
            }                
            for (int i = 0; i < block_size; i++) {
                if (!s.empty()) {
                    q2.push(s.top());
                    s.pop();
                }
            } 
        }    
        block_size++;
    }

    while (!q2.empty()) {
        q.push(q2.front());
        q2.pop();
    }
}

}
