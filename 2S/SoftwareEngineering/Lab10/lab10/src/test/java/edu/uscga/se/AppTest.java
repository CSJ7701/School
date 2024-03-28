package edu.uscga.se;

import static org.junit.Assert.assertEquals;
import org.junit.Test;
import java.util.NoSuchElementException;
import java.util.LinkedList;

public class AppTest {

    @Test
    public void testAdd  () {
        // Create an empty LinkedList of Strings
        LinkedList<String> staff = new LinkedList<String>();

        // Add four names to the beginning of the LinkedList
        staff.addFirst("Tom");
        staff.addFirst("Romeo");
        staff.addFirst("Harry");
        staff.addFirst("Diana");

        assertEquals(staff.getFirst(), "Diana");
    }

    @Test
    public void testRemove  () {
	// Remove the first element from a LinkedList of Strings
	LinkedList<String> fruit = new LinkedList<String>();

	fruit.addFirst("Apples");
	fruit.add("Bananas");
	fruit.add("Oranges");
	fruit.removeFirst();

	assertEquals(fruit.getFirst(), "Bananas");
    }

    @Test(expected = NoSuchElementException.class)
    public void testEmpty  () {
	// Test the initial state of a LinkedList
	LinkedList<String> empty = new LinkedList<String>();
	empty.getFirst();
    }
    
}
