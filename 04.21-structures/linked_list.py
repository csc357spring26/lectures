# Implements a linked list.
# CSC 202, code from lecture 
# See also: github.com/csc202winter25/lectures

class List:
    """ An ordered collection of elements """

    def __init__(self):
        # The head of the backing linked list:
        self.head = None
        # The number of elements in this list:
        self.size = 0


class Node:
    """ A single node in a linked list """

    def __init__(self, value, next):
        # The value contained in this node:
        self.value = value
        # The next node in the linked list:
        self.next = next


def get(lst, idx):
    # Start with a current node being the given lst's head.
    # For i from 0 to the given idx:
    #     Set the current node to the current node's next.
    # Return the current node's value.
    pass


def set(lst, idx, value):
    # Start with a current node being the given lst's head.
    # For i from 0 to the given idx:
    #     Set the current node to the current node's next.
    # Set the current node's value to the given value.
    pass


def add(lst, idx, value):
    # Create a new node containing the given value.
    # If the given idx is 0, then:
    #     Set the new node's next to the given lst's head.
    #     Set the given lst's head to the new node.
    # Else, do:
    #     Start with a current node being the head of the given lst.
    #     For i from 0 to the given idx - 1, do:
    #         Set the current node to the current node's next.
    #     Set the new node's next to the current node's next.
    #     Set the current node's next to the new node.
    # Increment the given lst's size.
    pass


def remove(lst, idx):
    # If the given idx is 0, then:
    #     Set the given lst's head to the given lst's head's next.
    # Else, do:
    #     Start with a current node being the head of the given lst.
    #     For i from 0 to the given idx - 1, do:
    #         Set the current node to the current node's next.
    #     Set the current node's next to the current node's next's next.
    # Decrement the given lst's size.
    pass
