public class GradeBook {
    private final int numStudents = 5;
    private final int numTests = 4;

    private String[] names = new String[numStudents];
    private char[] letterGrade = new char[numStudents];

    private double[] score1 = new double[numTests];
    private double[] score2 = new double[numTests];
    private double[] score3 = new double[numTests];
    private double[] score4 = new double[numTests];
    private double[] score5 = new double[numTests];

//methods
    //mutators

    //sets student name, correlating with student number
    public void setStudentName(int studentNumber, String name) {
        names[studentNumber - 1] = name;
    }

    //copies array of test scores to a students array of scores
    public void setScores(int studentNumber, double[] scores) {

        if (studentNumber == 1)
            copyArray(score1, scores);
        else if (studentNumber == 2)
            copyArray(score2, scores); 
        else if (studentNumber == 3)
            copyArray(score3, scores);
        else if (studentNumber == 4)
            copyArray(score4, scores);
        else if (studentNumber == 5)
            copyArray(score5, scores);
        assignGrade(studentNumber);
    }

    //private method copies contents of one array to another
    private void copyArray(double[] to, double[] from) {
        for (int i = 0; i < to.length; i++)
            to[i] = from[i];
    }
    //private method determines and assigns letter grade to specifc student
    private void assignGrade(int studentNumber) {
        double average = getAverage(studentNumber);
        letterGrade[studentNumber - 1] = determineGrade(average);
    }

    //accessors

    //returns a student's name
    public String getName(int studentNumber) {
        return names[studentNumber - 1];
    }

    //returns a student's average test score
    public double getAverage(int studentNumber) {
        double average;

        if (studentNumber == 1)
            average = calcAverage(score1);
        else if (studentNumber == 2)
            average = calcAverage(score2);
        else if (studentNumber == 3)
            average = calcAverage(score3);
        else if (studentNumber == 4)
            average = calcAverage(score4);
        else if (studentNumber == 5)
            average = calcAverage(score5);
        else
            average = 0.0;

        return average;
    }

    //returns a student's letter grade
    public char getLetterGrade(int studentNumber) {
         return letterGrade[studentNumber - 1];
    }

    //private method calculates average of values in an array of testscores
    private double calcAverage(double[] scores) {
        double total = 0.0, average;

        for (int i = 0; i < scores.length; i++) {
            total += scores[i];
        }

        average = total / (scores.length);
        return average;
    }

    //private method determines a letter grade for a test average
    private char determineGrade(double average) {
        char grade;

        if (average >= 90 && average <= 100)
            grade = 'A';
        else if (average >= 80 && average < 90)
            grade = 'B';
        else if (average >= 70 && average < 80)
            grade = 'C';
        else if (average >= 60 && average < 70)
            grade = 'D';
        else if (average >= 0 && average < 60)
            grade = 'F';
        else
            grade = '?';

        return grade;
    }
}
