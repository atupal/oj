import java.math.BigInteger;  
import java.util.Scanner;

class Main {

  public static void main(String args[]) {
    BigInteger one = new BigInteger("1");

    Scanner in = new Scanner(System.in);
    int t = in.nextInt();
    in.nextLine();
    for (int c = 0; c < t; ++ c) {
      String s = in.nextLine().trim();
      String fact[] = s.split(" ");
      String a[] = fact[0].split("/");
      String b[] = fact[1].split("/");
      BigInteger p1 = new BigInteger(a[0]);
      BigInteger q1 = new BigInteger("1");
      if (a.length == 2) {
        q1 = new BigInteger(a[1]);
      }

      BigInteger p2 = new BigInteger(b[0]);
      BigInteger q2 = new BigInteger("1");
      if (b.length == 2) {
        q2 = new BigInteger(b[1]);
      }

      BigInteger p = (p1.multiply(q2) ).add(p2.multiply(q1));
      BigInteger q = q1.multiply(q2);
      BigInteger gcd = p.gcd(q);
      p = p.divide(gcd);
      q = q.divide(gcd);
      System.out.print(p);
      if (q.compareTo(one) != 0) {
        System.out.print("/");
        System.out.println(q);
      } else {
        System.out.println();
      }
    }
  }
}
