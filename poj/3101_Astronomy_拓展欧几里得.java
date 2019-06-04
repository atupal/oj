import java.math.BigInteger;
import java.io.*;
import java.util.StringTokenizer;

// Rename to "Main" when submit to POJ
public class _3101_Astronomy {
    private static BigInteger Zero = new BigInteger("0");
    private static BigInteger One = new BigInteger("1");
    private static BigInteger Two = new BigInteger("2");

    public static void main(String[] args) throws IOException {
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        StringTokenizer st = new StringTokenizer(f.readLine());
        int n = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(f.readLine());

        BigInteger a = new BigInteger(st.nextToken());
        BigInteger b = new BigInteger(st.nextToken());

        BigInteger ans1 = a.multiply(b);
        BigInteger ans2 = a.subtract(b).abs();//.multiply(Two);
        BigInteger g = ans1.gcd(ans2);
        if (!ans2.equals(Zero)) {
            ans1 = ans1.divide(g);
            ans2 = ans2.divide(g);
        } else {
            ans1 = Zero;
            ans2 = One;
        }

        for (int i = 2; i < n; ++ i) {
            b = new BigInteger(st.nextToken());

            BigInteger newans1 = a.multiply(b);
            BigInteger newans2 = a.subtract(b).abs();//.multiply(Two);
            g = newans1.gcd(newans2);
            if (!newans2.equals(Zero)) {
                newans1 = newans1.divide(g);
                newans2 = newans2.divide(g);
            } else {
                continue;
            }

            if (ans1.equals(Zero)) {
                ans1 = newans1;
                ans2 = newans2;
                continue;
            }

            g = ans1.multiply(newans2).gcd(newans1.multiply(ans2));
            ans1 = ans1.multiply(newans1).multiply(ans2).divide(g);
            g = ans1.gcd(ans2);
            ans1 = ans1.divide(g);
            ans2 = ans2.divide(g);
        }
        // Optimize: See the commented //.multiply(Two) in above lines.
        if (ans1.mod(Two).equals(Zero)) {
            ans1 = ans1.divide(Two);
        } else {
            ans2 = ans2.multiply(Two);
        }

        System.out.print(ans1);
        System.out.print(" ");
        System.out.println(ans2);

        f.close();
        out.close(); // close the output file
        System.exit(0); // don't omit this!
    }
}

