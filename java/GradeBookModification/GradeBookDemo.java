import java.util.Scanner;

public class GradeBookDemo {
    public static void main(String[] args) {
        GradeBook gb = new GradeBook();

        getData(gb);

        System.out.println("STUDENT DATA");
        for (int i = 1; i <= 5; i++) {
            System.out.printf("Name: %s \t" +
                              "Average score: %.2f \t" +
                              "Grade: %s \n", gb.getName(i),
                              gb.getAverage(i), gb.getLetterGrade(i));
        }
    }
    public static void getData(GradeBook gb) {
        String name;
        double[] scores = new double[4];

        Scanner keyboard = new Scanner(System.in);

        for (int student = 1; student <= 5; student++) {
            System.out.print("Enter student " + student +
                             "'s name: ");
            name = keyboard.nextLine();
            gb.setStudentName(student, name);

            System.out.println("Now enter student " + student +
                               "'s four test scores.");
            for (int i = 0; i < 4; i++) {
                System.out.print("Test score #" + (i + 1) + ": ");
                scores[i] = keyboard.nextDouble();
                gb.setScores(student, scores);
            }
            keyboard.nextLine();
        }
        keyboard.close();
        System.out.println();
    }
}