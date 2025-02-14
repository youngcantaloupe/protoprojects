public class FizzBuzz {
    public static void main(String[] args) {

        for (int i = 1; i <= 100; i++) {
            System.out.print("\n " + 1);
            if (i % 3 == 0 && i % 5 == 0) {
                System.out.print(" FizzBuzz");
                System.out.print(" (" + i + " / 3 = " + i / 3 + ")");
                System.out.print(" (" + i + " / 5 = " + i / 5 + ")");
            }
            if (i % 3 == 0 && ! i % 5 == 0) {
                System.out.print(" Fizz");
                System.out.print(" (" + i + " / 3 = " + i / 3 + ")");
            }
            if (i % 5 == 0 && ! i % 3 == 0) {
                System.out.print(" Buzz");
                System.out.print(" (" + i + " / 5 = " + i / 5 + ")");
            }
        }
        System.out.println();
    }
}
