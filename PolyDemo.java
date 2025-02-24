package edu.bloomu.chap10.sect5;

import javax.swing.*;
import java.util.Comparator;
import java.util.Scanner;

/**
 * Prompts the user for two words and orders them by length and according to colexical
 * order. Illustrates runtime polymorphism with interfaces.
 *
 * @author
 */
public class PolyDemo {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter two words: ");
        String w1 = in.next();
        String w2 = in.next();

        class LengthComparator implements Comparator<String> {
            @Override
            public int compare(String s1, String s2) {
                return s1.length() - s2.length();
            }
        }

        class ColexComparator implements Comparator<String> {
            @Override
            public int compare(String s1, String s2) {
                StringBuilder sb1 = new StringBuilder(s1);
                StringBuilder sb2 = new StringBuilder(s2);
                sb1.reverse();
                sb2.reverse();
                return sb1.compareTo(sb2);
            }
        }
        System.out.println("Length order: " + order(w1, w2, new LengthComparator()));
        System.out.println("Colex order: " + order(w1, w2, new ColexComparator()));
    }

    /**
     * Returns a string expressing the order of two given strings x and y as determined
     * by a given comparator.
     */
    private static String order(String x, String y, Comparator<String> c) {
        int result = c.compare(x, y);
        if (result < 0) {
            return x + " < " + y;
        }
        if (result > 0) {
            return x + " > " + y;
        }
        return x + " = " + y;
    }
}
