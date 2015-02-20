import java.math.BigInteger;  
import java.util.Scanner;

public class Main {
  public static void main(String args[]) {
    BigInteger p[] = new BigInteger[100];
    BigInteger one = new BigInteger("1");
    BigInteger two = new BigInteger("2");
    p[0] = one;
    for (int i = 1; i < 100; ++ i) {
      p[i] = p[i-1].multiply(two);
    }

    Scanner in = new Scanner(System.in);
    int t = in.nextInt();
    in.nextLine();
    for (int c = 0; c < t; ++ c) {
      String s = in.nextLine().trim();
      BigInteger n = new BigInteger(s);
      int win = 0;
      while (n.compareTo(one) > 0) {
        //System.out.println(n);
        int i;
        for (i = 99; i >= 0; -- i) {
          if (p[i].compareTo(n) <= 0) {
            break;
          }
        }

        if (p[i].compareTo(n) == 0) {
          n = p[i-1];
        } else {
          n = n.subtract(p[i]);
        }

        if (win == 1) {
          win = 0;
        } else {
          win = 1;
        }

      }

      if (win == 1) {
        System.out.println("Raju Won!");
      } else {
        System.out.println("Friend Won!");
      }
    }

  }
}
