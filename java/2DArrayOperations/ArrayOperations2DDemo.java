public class ArrayOperations2DDemo
{
   public static void main(String[] args)
   {
      // Some 2D arrays of various types.
      int[][] iarray = { { 2, 1, 9},
                         { 7, 3, 4 } };
                           
      float[][] farray = { { 3.5F, 4.6F, 1.7F },
                           { 8.9F, 2.1F, 6.2F } };
                             
      double[][] darray = { { 98.7, 89.2, 55.1 },
                            { 77.6, 99.9, 62.2 } };
                              
      long[][] larray = { { 100, 500, 200 },
                          { 300, 400, 900 } };
      
      // Process the int array.
      System.out.println("Processing the int array.");
      System.out.println("Total : " +
                         ArrayOperations2D.getTotal(iarray));
      System.out.println("Average : " +
                         ArrayOperations2D.getAverage(iarray));
      System.out.println("Total of row 0 : " +
                         ArrayOperations2D.getRowTotal(iarray, 0));
      System.out.println("Total of row 1 : " +
                         ArrayOperations2D.getRowTotal(iarray, 1));
      System.out.println("Total of col 0 : " +
                         ArrayOperations2D.getColumnTotal(iarray, 0));
      System.out.println("Total of col 2 : " +
                         ArrayOperations2D.getColumnTotal(iarray, 2));
      System.out.println("Highest in row 0 : " +
                         ArrayOperations2D.getHighestInRow(iarray, 0));
      System.out.println("Highest in row 1 : " +
                         ArrayOperations2D.getHighestInRow(iarray, 1));
      System.out.println("Lowest in row 0 : " +
                         ArrayOperations2D.getLowestInRow(iarray, 0));
      System.out.println("Lowest in row 1 : " +
                         ArrayOperations2D.getLowestInRow(iarray, 1));

      // Process the float array.
      System.out.println("\nProcessing the float array.");
      System.out.println("Total : " +
                         ArrayOperations2D.getTotal(farray));
      System.out.println("Average : " +
                         ArrayOperations2D.getAverage(farray));
      System.out.println("Total of row 0 : " +
                         ArrayOperations2D.getRowTotal(farray, 0));
      System.out.println("Total of row 1 : " +
                         ArrayOperations2D.getRowTotal(farray, 1));
      System.out.println("Total of col 0 : " +
                         ArrayOperations2D.getColumnTotal(farray, 0));
      System.out.println("Total of col 2 : " +
                         ArrayOperations2D.getColumnTotal(farray, 2));
      System.out.println("Highest in row 0 : " +
                         ArrayOperations2D.getHighestInRow(farray, 0));
      System.out.println("Highest in row 1 : " +
                         ArrayOperations2D.getHighestInRow(farray, 1));
      System.out.println("Lowest in row 0 : " +
                         ArrayOperations2D.getLowestInRow(farray, 0));
      System.out.println("Lowest in row 1 : " +
                         ArrayOperations2D.getLowestInRow(farray, 1));

      // Process the double array.
      System.out.println("\nProcessing the double array.");
      System.out.println("Total : " +
                         ArrayOperations2D.getTotal(darray));
      System.out.println("Average : " +
                         ArrayOperations2D.getAverage(darray));
      System.out.println("Total of row 0 : " +
                         ArrayOperations2D.getRowTotal(darray, 0));
      System.out.println("Total of row 1 : " +
                         ArrayOperations2D.getRowTotal(darray, 1));
      System.out.println("Total of col 0 : " +
                         ArrayOperations2D.getColumnTotal(darray, 0));
      System.out.println("Total of col 2 : " +
                         ArrayOperations2D.getColumnTotal(darray, 2));
      System.out.println("Highest in row 0 : " +
                         ArrayOperations2D.getHighestInRow(darray, 0));
      System.out.println("Highest in row 1 : " +
                         ArrayOperations2D.getHighestInRow(darray, 1));
      System.out.println("Lowest in row 0 : " +
                         ArrayOperations2D.getLowestInRow(darray, 0));
      System.out.println("Lowest in row 1 : " +
                         ArrayOperations2D.getLowestInRow(darray, 1));

      // Process the long array.
      System.out.println("\nProcessing the long array.");
      System.out.println("Total : " +
                         ArrayOperations2D.getTotal(larray));
      System.out.println("Average : " +
                         ArrayOperations2D.getAverage(larray));
      System.out.println("Total of row 0 : " +
                         ArrayOperations2D.getRowTotal(larray, 0));
      System.out.println("Total of row 1 : " +
                         ArrayOperations2D.getRowTotal(larray, 1));
      System.out.println("Total of col 0 : " +
                         ArrayOperations2D.getColumnTotal(larray, 0));
      System.out.println("Total of col 2 : " +
                         ArrayOperations2D.getColumnTotal(larray, 2));
      System.out.println("Highest in row 0 : " +
                         ArrayOperations2D.getHighestInRow(larray, 0));
      System.out.println("Highest in row 1 : " +
                         ArrayOperations2D.getHighestInRow(larray, 1));
      System.out.println("Lowest in row 0 : " +
                         ArrayOperations2D.getLowestInRow(larray, 0));
      System.out.println("Lowest in row 1 : " +
                         ArrayOperations2D.getLowestInRow(larray, 1));
   }
}
