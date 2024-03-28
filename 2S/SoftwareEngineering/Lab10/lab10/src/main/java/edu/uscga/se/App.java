package edu.uscga.se;

public class App {

    public static void main(String[] args) {
        // Create an empty LinkedList of Strings
        LinkedList<String> staff = new LinkedList<String>();

        // Add four names to the beginning of the LinkedList
        staff.addFirst("Tom");
        staff.addFirst("Romeo");
        staff.addFirst("Harry");
        staff.addFirst("Diana");

        // Create an iterator to traverse the LinkedList
        ListIterator<String> iterator = staff.listIterator();

        // Declare a variable to hold the next element in the LinkedList
        String Str;

        // Get the first element in the LinkedList and print it
        Str = (String) iterator.next();
        System.out.println("next returned:" + Str);

        // Get the second element in the LinkedList and print it
        Str = (String) iterator.next();
        System.out.println("next returned:" + Str);

        // Add two names to the LinkedList at the current position of the iterator
        iterator.add("Juliet");
        iterator.add("Nina");

        // Get the third element in the LinkedList and print it
        Str = (String) iterator.next();
        System.out.println("next returned:" + Str);

        // Remove the current element from the LinkedList
        iterator.remove();

        // Reset the iterator to the beginning of the LinkedList
        iterator = staff.listIterator();

        // Print all the elements in the LinkedList
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();
    }
}