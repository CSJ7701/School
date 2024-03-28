package edu.uscga.se;

import java.util.NoSuchElementException;

public class LinkedList<T> {

    // Inner class for a node in the linked list
    class Node {

        // Data stored in the node
        public T data;

        // Reference to the next node in the linked list
        public Node next;
    }

    // Reference to the first node in the linked list
    private Node first;

    // Constructor for an empty linked list
    public LinkedList() {
        first = null;
    }

    // Get the first element in the linked list
    public T getFirst() {
        if (first == null) {
            throw new NoSuchElementException();
        }
        return first.data;
    }

    // Remove the first element from the linked list
    public T removeFirst() {
        if (first == null) {
            throw new NoSuchElementException();
        }
        T element = first.data;
        first = first.next;
        return element;
    }

    // Add an element to the beginning of the linked list
    public void addFirst(T element) {
        Node newNode = new Node();
        newNode.data = element;
        newNode.next = first;
        first = newNode;
    }

    // Return an iterator for the linked list
    public ListIterator<T> listIterator() {
        return new LinkedListIterator();
    }

    // Inner class for an iterator over the linked list
    class LinkedListIterator implements ListIterator<T> {

        // Reference to the current node in the linked list
        private Node position;

        // Reference to the previous node in the linked list
        private Node previous;

        // Flag to indicate if the next element has been accessed
        private boolean isAfterNext;

        // Constructor for the iterator
        public LinkedListIterator() {
            position = null;
            previous = null;
            isAfterNext = false;
        }

        // Check if there is a next element in the linked list
        public boolean hasNext() {
            if (position == null) {
                return first != null;
            } else {
                return position.next != null;
            }
        }

        // Get the next element in the linked list
        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            previous = position; // Remember for remove
            isAfterNext = true;

            if (position == null) {
                position = first;
            } else {
                position = position.next;
            }

            return position.data;
        }

        // Add an element to the linked list before the current position
        public void add(T element) {
            if (position == null) {
                addFirst(element);
                position = first;
            } else {
                Node newNode = new Node();
                newNode.data = element;
                newNode.next = position.next;
                position.next = newNode;
                position = newNode;
            }

            isAfterNext = false;
        }

        // Remove the current element from the linked list
        public void remove() {
            if (!isAfterNext) {
                throw new IllegalStateException();
            }

            if (position == first) {
                removeFirst();
            } else {
                previous.next = position.next;
            }
            position = previous;
            isAfterNext = false;
        }

        // Replace the current element in the linked list with a new element
        public void set(T element) {
            if (!isAfterNext) {
                throw new IllegalStateException();
            }
            position.data = element;
        }
    }
}