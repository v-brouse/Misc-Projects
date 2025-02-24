package edu.bloomu.chap10.sect5;

import java.util.Scanner;

/**
 * Demonstrates assertion in Java.
 *
 * @author
 */
public class AssertDemo {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter a positive integer: ");
        int x = in.nextInt();

        assert x != 0: "ZERO WAS ENTERED";

        System.out.println(1.0 / x);
    }
}
